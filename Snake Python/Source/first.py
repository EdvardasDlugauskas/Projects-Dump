import sys
import site
import pygame
import random
from filegetter import getfiles

pygame.init()

gameState = 'menu'

white = (255, 255, 255)
black = (0, 0, 0)
red = (255, 0, 0)
green = (0, 155, 0)

display_width = 800
display_height = 600

gameDisplay = pygame.display.set_mode((display_width, display_height))
pygame.display.set_caption('Snakinator')

snakeHead_img = pygame.image.load('images/snakeHead.png')
snakeBody_img = pygame.image.load('images/snakeBody.png')
snakeTail_img = pygame.image.load('images/snakeTail.png')
snakeBodyCurve_img = pygame.image.load('images/snakeBodyCurve.png')

# Get eatable objects
eatables = [pygame.image.load(file) for file in getfiles('images/eatables')]
currentApple = eatables[random.randrange(len(eatables))]
# Get backgrounds
backgrounds = [pygame.image.load(file) for file in getfiles('images/back')]
# Get sounds
moving_sound = pygame.mixer.Sound('sounds/moving.wav')
death_sound = pygame.mixer.Sound('sounds/dead.wav')
eat_sound = pygame.mixer.Sound('sounds/eat.wav')

FPS = 15
block_size = 20 # Snake block size as well
change_step = 20

highscores = open('highscore.txt', 'r+')
highscore = int(highscores.read())


# Set background
background = []
dirs = [0, 90, 180, 270]
for y in range(0, display_height, block_size):
    line = []
    for x in range(0, display_width, block_size):
        if random.randrange(0, len(backgrounds)*2) < len(backgrounds)/50:   # Probabilities and Backgrounds!
            line.append(backgrounds[random.randrange(1, 10)])
        else:
            curImage = backgrounds[0]
            line.append(pygame.transform.rotate(curImage, dirs[random.randrange(0, len(dirs) ) ] ) )
    background.append(line)

# Print background
def back():
    for liney, y in enumerate(range(0, display_height, block_size)):
        for column, x in enumerate(range(0, display_width, block_size)):
            gameDisplay.blit(background[liney][column], (x, y))

clock = pygame.time.Clock()
pygame.display.update()

smallfont = pygame.font.SysFont('comicsansms', 25)
medfont = pygame.font.SysFont('comicsansms', 50)
largefont = pygame.font.SysFont('comicsansms', 80)

def directions(startxy, endxy):
    """ Returns 0, 90, 180 or 270
    :rtype : integer
    :return: degrees !!counter clockwise!!
    """
    startX, startY = startxy[0], startxy[1]
    endX, endY = endxy[0], endxy[1]
    if startX < endX:
        return 270
    elif startX > endX:
        return 90
    elif startY < endY:
        return 180
    else:
        return 0


appleThickness = 30
randAppleX = random.randrange(block_size, display_width - appleThickness, change_step)
randAppleY = random.randrange(block_size, display_height - appleThickness, change_step)

def apple():
    """ Gives the apple a new sprite and position, adds 1 to snakeLength
    """

    global randAppleX, randAppleY, snakeLength, currentApple
    currentApple = eatables[random.randrange(len(eatables))]
    snakeLength += 1
    apple_placed = False

    while not apple_placed:
        randAppleX = random.randrange(block_size, display_width - block_size, change_step)
        randAppleY = random.randrange(block_size, display_height - block_size, change_step)
        for every_rect in snakeRectList:
            # Check if the apple is in the snake (bad)
            if every_rect.colliderect(pygame.Rect((randAppleX, randAppleY), (appleThickness, appleThickness))):
                break
        else:
            break


snakeList = []  # list of snake block coordinates
snakeRectList = []
snakeLength = 2


def snake(snakeList):
    """
    Draws the snake block by block
    """
    # Head direction
    head = pygame.transform.rotate(snakeHead_img, direction)

    # Tail direction
    if len(snakeList) > 1:
        tail = pygame.transform.rotate(snakeTail_img, directions(snakeList[0], snakeList[1]))

    # Body draw
    for ind, current_block in enumerate(snakeList[1:-1]):
        prev_block = snakeList[ind+2]
        next_block = snakeList[ind]
        if prev_block[0] == next_block[0] or prev_block[1] == next_block[1]:
            body = pygame.transform.rotate(snakeBody_img, directions(current_block, prev_block))

        elif directions(current_block, prev_block) == 90 or  directions(current_block, next_block) == 90:
            if directions(current_block, next_block) == 0 or directions(current_block, prev_block) == 0:
                body = pygame.transform.rotate(snakeBodyCurve_img, 270)
            else:
                body = snakeBodyCurve_img
        # Assume if statement above never fails to recognize snakeBody
        else:
            if directions(current_block, next_block) == 0 or directions(current_block, prev_block) == 0:
                body = pygame.transform.rotate(snakeBodyCurve_img, 180)
            else:
                body = pygame.transform.rotate(snakeBodyCurve_img, 90)

        gameDisplay.blit(body, (current_block[0], current_block[1]))

    # Head draw
    gameDisplay.blit(head, (snakeList[-1][0], snakeList[-1][1]))  # param: image, X position, Y position

    # Tail draw
    if len(snakeList) > 1:
        gameDisplay.blit(tail, (snakeList[0][0], snakeList[0][1]))


def text_objects(text, color, size):
    """
    :param text: string
    :return: text surface, text rectangle
    """

    if size == 'small':
        textSurface = smallfont.render(text, True, color)
    elif size == 'medium':
        textSurface = medfont.render(text, True, color)
    elif size == 'large':
        textSurface = medfont.render(text, True, color)
    else:
        textSurface = smallfont.render(text, True, color)
    return textSurface, textSurface.get_rect()


def message_to_screen(msg, color, y_displace=0, size='small'):
    """
    Display a message from the center of the display
    :param msg: Text to display
    :param color: Display color (or RGB)
    """
    textSurf, textRect = text_objects(msg, color, size)
    textRect.center = (display_width / 2), (display_height / 2 + y_displace)
    gameDisplay.blit(textSurf, textRect)


def gameLoop():
    global direction, snakeLength, snakeList, snakeRectList
    snakeLength = 1
    snakeList = []
    snakeRectList = []
    gameExit = False
    gameOver = False
    # Starting position
    lead_x = display_width / 2
    lead_y = display_height / 2
    # Default movement
    lead_x_change = change_step
    lead_y_change = 0
    direction = 270     # Direction is counter-clockwise!

    apple() # Place apple

    while not gameExit:
            # GAME OVER
        if gameOver:
            pygame.mixer.Sound.play(death_sound)
            gameDisplay.fill(white)
            message_to_screen("GAME OVER", red, y_displace=-50, size='large')
            message_to_screen("Press R to play again or Q to quit...", black)
            message_to_screen("Your score is {}".format(len(snakeList)-2), color=black, y_displace=50, size='small')
            if len(snakeList)-2 > highscore:
                message_to_screen("NEW HIGHSCORE", color=red, y_displace=150, size='large')
                highscores.seek(0)
                highscores.write("{}".format(len(snakeList)-2))
            pygame.display.update()
            while gameOver:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        gameExit = True
                        gameOver = False
                    elif event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_q:
                            gameExit = True
                            gameOver = False
                        elif event.key == pygame.K_r:
                            gameLoop()

        # Event loop
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                gameExit = True
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT and direction is not 270:
                    direction = 90
                    lead_x_change = - change_step
                    lead_y_change = 0
                elif event.key == pygame.K_RIGHT and direction is not 90 :
                    direction = 270
                    lead_x_change = change_step
                    lead_y_change = 0
                elif event.key == pygame.K_UP and direction is not 180:
                    direction = 0
                    lead_y_change = -change_step
                    lead_x_change = 0
                elif event.key == pygame.K_DOWN and direction is not 0:
                    direction = 180
                    lead_y_change = change_step
                    lead_x_change = 0

        # Boundries
        if lead_x >= display_width - block_size/2 or lead_x <= 0 - block_size/2 or \
                lead_y >= display_height - block_size/2 or lead_y <= 0 - block_size/2:
            pygame.display.update()
            gameOver = True


        lead_x += lead_x_change
        lead_y += lead_y_change
        back()  # Background

        # Apple
        gameDisplay.blit(currentApple, (randAppleX, randAppleY))

        # Snake
        snakeHead = [lead_x, lead_y]
        snakeList.append(snakeHead)     # Add a new block to the snake
        snakeRectList.append(pygame.Rect((lead_x, lead_y,), (block_size, block_size)))

        if len(snakeList) > snakeLength:    # Delete unneeded blocks
            del snakeList[0]
            del snakeRectList[0]

        for each_segment in snakeList[:-1]:
            if each_segment == snakeHead:
                gameOver = True

        snake(snakeList)  # Draw snake
        pygame.display.update()

        # Collision detection:
        if pygame.Rect.colliderect(pygame.Rect(lead_x, lead_y, block_size, block_size),
                                   pygame.Rect(randAppleX, randAppleY, appleThickness, appleThickness)):
            pygame.mixer.Sound.play(eat_sound)
            apple()

        pygame.mixer.Sound.play(moving_sound)
        clock.tick(FPS)  # FPS

    pygame.quit()
    sys.exit()



def menu():
    global gameState
    gameDisplay.fill(white)
    message_to_screen('Welcome to SNAKINATOR', red, -(display_height/4), 'large')
    message_to_screen("Arrow keys to move. Don't eat yourself!", black, size='small')
    pygame.display.update()
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            gameState = 'play'
        elif event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

if __name__ == '__main__':
    while True:
        if gameState == 'menu':
            menu()
        elif gameState == 'play':
            gameLoop()

highscores.close()
