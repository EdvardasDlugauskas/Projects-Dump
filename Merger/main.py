from classes import *
from sys import exit

pygame.init()

Surf = pygame.display.set_mode((800, 800))
Surf.fill(WHITE)
pygame.display.update()
# Note: Coordinates in x, y

pygame.display.update()
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
            pygame.quit()
            exit()


""" Chain testing:
center = (400, 400)
chain1 = [ center, (380,400), (380, 340), (400, 280), (420, 340), (420, 400), center ]
chain2 = [ center, (360,400), (400, 320), (440, 400), center ]
mergedChain = chain1 + chain2
graph(mergedChain, coord=center, center=True, color = RED)
graph(chain1, coord=center, center=True) # [(20, 120), (0, 120), (0, 60), (20, 0), (40, 60), (40, 120), (20, 120)]
graph(chain2, coord=center, center=True) # [(40, 80), (0, 80), (40, 0), (80, 80), (40, 80)]
SUCCESS"""

""" Hilt Weapon testing:
hilt1 = Chain([(450, 520), (440, 520), (440, 480), (450, 480), (450, 480), (460, 480), (460, 520), (450, 520)], normalize=True)
blade1 = Chain([(480, 550), (430, 550), (430, 420), (530, 200), (530, 550), (480, 550)])
my_weapon1= HiltWeapon(blade1,hilt1)
my_weapon1.graph( (100,600), center=True )
hilt2 = [(480, 550), (470, 550), (470, 520), (490, 520), (490, 550), (480, 550)]
blade2 = [(450, 540), (430, 540), (430, 450), (450, 110), (470, 450), (470, 540), (450, 540)]
my_weapon2 = HiltWeapon(blade2, hilt2)
my_weapon2.graph( (300,600), center=True)
merged_weapon = my_weapon1 + my_weapon2
merged_weapon.graph( (500,600), center=True, color=RED)
SUCCESS"""

""" Helmet testing:
helmet1 = Helmet([(410, 470), (390, 450), (370, 470), (370, 420),
                        (410, 420), (410, 420), (450, 420), (450, 470.0), (430, 450), (410, 470)])
helmet1.graph((200,400), center=False)
helmet2 = Helmet([(480, 390), (470, 390), (470, 370), (450, 370), (450, 390), (440, 390), (440, 360), (450, 350),
    (480, 350), (510, 350), (520, 360), (520, 390), (510, 390), (510, 370), (490, 370), (490, 390), (480, 390)])
helmet2.graph(coord=(400,400), center=False)
helmet3 = helmet1+helmet2
helmet3.graph((600,400), color=RED)
SUCCESS"""

"""Breastplate testing:
breast1 = Breastplate([(490, 300), (470, 300), (460, 330), (430, 330), (390, 400), (390, 500), (490, 510), (590, 500),
                       (590, 400), (550, 330), (520, 330), (510, 300), (490, 300)])
breast2 = Breastplate([(520, 320), (500, 320), (500, 340), (470, 340), (450, 370), (480, 430), (460, 460), (520, 470),
                       (580, 460), (560, 430), (590, 370), (570, 340), (540, 340), (540, 320), (520, 320)])

breast1.graph((100, 300))
breast2.graph((300, 300))
breast3 = breast1 + breast2
breast3.graph((500, 300), color=RED)
SUCCESS"""