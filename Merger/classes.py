"""
Contains classes used by Merger program.
"""
import func
from base import *


class Chain:
    """
    Main chain class
    """
    def __init__(self, chain, normalize=False):
        """
        :param chain: a list of points (tuples)
        """
        self.points, self.width, self.height = func.normalize(chain)
        if not normalize:
            self.points = chain
        # self.surf = pygame.Surface((self.width, self.height))
        # self.rect = self.surf.get_rect()

    def __getitem__(self, key):
        return self.points[key]

    def __len__(self):
        return len(self.points)

    def __repr__(self):
        return "<Chain> class " + self.points.__repr__()

    def __add__(self, other):  # Add proportion later?
        ch1 = list(self.points)
        ch2 = list(other.points)
        if len(ch1) >= len(ch2):
            longer = ch1
            shorter = ch2
        else:
            longer = ch2
            shorter = ch1
        props = func.proportions(longer)
        dividedShort = func.divide_by_prop(shorter, props)
        # Find middles
        chain = func.middles(longer, dividedShort)
        return Chain(chain, normalize=True)


class HiltWeapon:
    """
    Any hilted weapon. Hass a hilt and a blade.
    """
    def __init__(self, blade, hilt):  # Material, sharpness?
        """
        :param blade: Chain obj for blade
        :param hilt: Chain obj for hilt
        """
        if isinstance(blade, list):
            blade = Chain(blade, normalize=True)
        if isinstance(hilt, list):
            hilt = Chain(hilt, normalize=True)
        self.blade = blade
        self.hilt = hilt
        assert isinstance(blade, Chain)
        assert isinstance(hilt, Chain)
        # CalculateValues/Properties() or whatever()

    def __add__(self, other):
        """
        :param other: HiltWeapon obj
        :return: new HiltWeapon
        """
        if isinstance(other, HiltWeapon):
            blade = self.blade + other.blade
            hilt = self.hilt + other.hilt
            return HiltWeapon(blade, hilt)
            # else ...

    def graph(self, coord, center=False, color=BLACK):
        """
        Calculate the X offset to pass coord+deltaX to func.graph function
        :param coord:   Draw at coord
        :param center:  If True, centers first point on :param coord:
        """
        x, y = coord
        blade_offset, hilt_offset = 0, 0
        if not center:
            if self.blade.width > self.hilt.width:
                hilt_offset = (self.blade.width - self.hilt.width) / 2
            else:
                blade_offset = (self.hilt.width - self.blade.width) / 2
            func.graph(self.blade, (x + blade_offset, y), center=False, color=color)
            func.graph(self.hilt, (x + hilt_offset, y + self.blade.height), center=False, color=color)
        else:
            func.graph(self.hilt, (x, y), center=True, color=color)
            func.graph(self.blade, (x, y - self.hilt.height), center=True, color=color)
            # Fill color...


class Helmet:
    def __init__(self, chain):
        """
        :param chain: Chain object representing helmet points
        """
        if isinstance(chain, list):
            chain = Chain(chain, normalize=True)

        self.chain = chain
        assert (isinstance(chain, Chain))

    def graph(self, coord, center=False, color=BLACK):
        """
        :param center: if True, centers first point on the coord
        """
        func.graph(chain=self.chain, coord=coord, center=center, color=color)

    def __add__(self, other):
        """
        :param other: Helmet object
        :return:
        """
        assert isinstance(other, Helmet)
        chain = self.chain + other.chain
        return Helmet(chain)


class Breastplate:
    def __init__(self, chain):
        """
        :param chain:   Chain object
        """
        if isinstance(chain, list):
            chain = Chain(chain, normalize=True)

        self.chain = chain

    def graph(self, coord, center=False, color=BLACK, surface=None):

        if not surface:
            surface = pygame.display.get_surface()

        func.graph(self.chain, coord=coord, center=center, color=color, surface=surface)

    def __add__(self, other):
        assert isinstance(other, Breastplate)
        new_chain = self.chain + other.chain
        return Breastplate(new_chain)




if __name__ == '__main__':
    # chain = Chain([(300, 400), (400,400), (500,400)], normalize=True)
    pass


""" Old breastplate shoulder drawing:
func.graph(self.chain, coord=coord, center=center, color=color, surface=surface)
        if center: chain = func.vectorize(self.chain)
        else: chain = self.chain
        point1, point2 = chain[self.shoulder_point-1], chain[self.shoulder_point]

        def draw_arc():

            x_incr = True if point1[0] - point2[0] > 0 else False
            y_incr = True if point1[1] - point2[1] > 0 else False
            if x_incr != y_incr:
                angle1, angle2 = (1.5*pi, 2*pi), (0.5*pi, pi)
                left1 = min(point1[0], point2[0]) - abs(point1[0] - point2[0]) + 1
                top1 = min(point1[1], point2[1]) - abs(point1[1] - point2[1]) + 1
                left2 = min(point1[0],point2[0]) + 1
                top2 = min(point1[1], point2[1]) + 1
                width = 2 * abs(point1[0] - point2[0])
                height = 2 * abs(point1[1] - point2[1])
            else:
                angle1, angle2 = ()

            rect1 = pygame.Rect(left1+coord[0], top1+coord[1], width, height)
            rect2 = pygame.Rect(left2+coord[0], top2+coord[1], width, height)
            pygame.draw.arc(surface, color, rect1, *angle1)
            pygame.draw.arc(surface, color, rect2, *angle2)
            pygame.draw.circle(surface, BLACK, func.adduple(point1, coord), 10, 1)
            pygame.draw.circle(surface, BLACK, func.adduple(point2, coord), 10, 1)

        draw_arc()
"""
""" And from main.py:
left1 = min(point1[0],point2[0]) - abs(point1[0]-point2[0])
top1 = min(point1[1], point2[1]) - abs(point1[1] - point2[1])
left2 = min(point1[0],point2[0])
top2 = min(point1[1], point2[1])
width = 2 * abs(point1[0] - point2[0])
height = 2 * abs(point1[1] - point2[1])
rect1 = pygame.Rect(left1, top1, width, height)
rect2 = pygame.Rect(left2, top2, width, height)
pygame.draw.circle(Surf, BLACK, point1, 10, 1)
pygame.draw.circle(Surf, BLACK, point2, 10, 1)
pygame.draw.rect(Surf, BLACK, rect1, 1)
pygame.draw.rect(Surf, BLACK, rect2, 1)
pygame.draw.arc(Surf, RED, rect1, 1.5*pi, 2*pi)
pygame.draw.arc(Surf, RED, rect2, 0.5*pi, pi)
"""