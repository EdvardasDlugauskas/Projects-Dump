import pygame

def catch(quitting=False):
    """
    :param: quit - will autoquit if True, returns False if else
    :return: returns true if caught quit event
    """

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            if quitting:
                pygame.quit()
                quit()
            else:
                return True
    return False


if __name__ == '__main__':
    pygame.init()
    display_width = 800
    display_height = 600
    gameDisplay = pygame.display.set_mode((display_width, display_height))\

    while True:
        quitting = catch(True)
    pygame.time.Clock.tick(10)
