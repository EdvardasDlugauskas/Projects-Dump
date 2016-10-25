import pygame
import sys

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)

pygame.init()

# Quit event catcher
def quitCatch(quitNow=False):
    """
    :param: quit - will autoquit if True, returns False if else
    :return: returns true if caught quit event
    """

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            if quitNow:
                pygame.quit()
                sys.exit()
            else:
                return True
    return False



"""
Get that text on the screen!
"""
# To get all available fonts, call >>> print(pygame.font.get_fonts())
small_font = pygame.font.SysFont('timesnewroman', 25)
med_font = pygame.font.SysFont('timesnewroman', 50)
large_font = pygame.font.SysFont('timesnewroman', 80)

def text_objects(text, color, size):
    """
    :param text: string
    :return: text surface, text rectangle
    """

    if size == 'small':
        textSurface = small_font.render(text, True, color)
    elif size == 'medium':
        textSurface = med_font.render(text, True, color)
    elif size == 'large':
        textSurface = large_font.render(text, True, color)
    else:
        textSurface = small_font.render(text, True, color)
    return textSurface, textSurface.get_rect()


def message_to_screen(surface, msg, color, y_displace=0, size='small'):
    """
    Display a message from the center of the display
    :param msg: Text to display
    :param color: Color of text (or RGB)
    """
    gameDisplay = surface
    display_width, display_height = gameDisplay.get_width(),gameDisplay.get_height()
    textSurf, textRect = text_objects(msg, color, size)
    textRect.center = ((display_width / 2), (display_height / 2 + y_displace))
    gameDisplay.blit(textSurf, textRect)
    pygame.display.update(textRect)


if __name__ == '__main__':
    pass