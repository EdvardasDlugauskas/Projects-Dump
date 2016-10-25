"""
Contains geometrical and graphical functions.
"""
import math
from base import *

def distance(p1, p2):
    return round(math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2), 3)

def middle(p1, p2, proportion = 0.5):
    '''
    proportion -> bigger is closer to the second point
    '''
    k1,k2 = 1 - proportion, proportion
    x = round((p1[0]*k1 + k2*p2[0]), 3)
    y = round((p1[1]*k1 + k2*p2[1]), 3)
    return (x, y)

def middles(chain1, chain2):
    points = []
    for index in range(len(chain1)):  # Assume both chains equal in size
        points.append(middle(chain1[index],chain2[index]))
    return points

def divideProp(chain, props):
    """
    Divide chain by proportions
    """
    length, lines = lengthAndDists(chain)
    dists = [ round(length*x, 2) for x in props]      # Distances needed
    points = [chain[0]]
    line = 0
    for index in range(len(dists) - 1): # SOMEFING WONG?
        dist = dists[index]
        found = False
        while not found:
            if dist > lines[line]:
                dist -= lines[line]
                line+=1
            elif  dist == lines[line]:
                point = chain[line+1]
                points.append(point)
                line+=1
                found = True
            else:
                #Find proportion to the line
                prop = dist / lines[line]
                point = middle(chain[line], chain[line+1], prop)
                points.append(point)
                #Change for future
                chain[line] = point
                lines[line] -= dist
                found = True
    points.append(chain[-1])
    return points

def proportions(chain):
    """
    Returns proportions of each in chain
    """
    length, dists = lengthAndDists(chain)
    props = []
    for each in dists:
        props.append(round(each/length, 3))
    return props

def lengthAndDists(chain):
    """
    Return length of chain and each of lines
    """
    dists = [ ]
    length = 0
    for index in range(len(chain)-1):
        dist = distance(chain[index], chain[index+1])
        length += dist
        dists.append(dist)
    return length, dists

def pointToLine(point, linep1, linep2, return_points=False):
    """
    Return minimum distance from points to line (linep1, linep2)
    :param point:   Point from which distance is calculated --> Tuple(x,y)
    :param linep1:  First point of line     --> Tuple(x,y)
    :param linep2:  Second point of line    --> Tuple(x,y)
    :return:
    """
    #http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline/source.vba
    length = distance(linep1, linep2)

    if length < 0.000001:
        return 0
    #***Dark magic***
    u1 = (((point[0] - linep1[0]) * (linep2[0] - linep1[0])) + ((point[1] - linep1[1]) * (linep2[1] - linep1[1])))
    u = u1 / (length*length)

    if return_points:
        x = linep1[0] + u * (linep2[0] - linep1[0])
        y = linep1[1] + u * (linep2[1] - linep1[1])
        return x, y

    if (u < 0.00001) or (u > 1):
        # closest point does not fall within the line segment, take the shorter distance
        # to an endpoint
        x = distance(point, linep1)
        y = distance(point, linep2)
        if x > y:
            return y
        else:
            return x
    else:
        # Intersecting point is on the line, use the formula
        x = linep1[0] + u * (linep2[0] - linep1[0])
        y = linep1[1] + u * (linep2[1] - linep1[1])
        return distance(point, (x,y))


def graph(chain, coord, center=False, color=BLACK, surface=None):   # Center is not None for now...
    """
    Graphs a normalized chain on point, or centered around point (takes first coord for center)
    !!! Centers around first point in chain!!!
    Returns rect for easy updating
    :param chain: Chain obj or list
    """
    assert(len(coord) == 2), "Coord isn't length of 2"
    if surface is None:
        surface = pygame.display.get_surface()
    points = list(chain.points)
    width, height = chain.width, chain.height
    newPoints = []

    if not center:
        for point in points:
            newPoints.append( (coord[0] + point[0] + 1, coord[1] + point[1] + 1) )
    else:
        # Centers first point on coord
        #newCenter = (coord[0] - points[0][0], coord[1] - points[0][1])
        #for point in points:
        #    newPoints.append( (newCenter[0] + point[0] + 1, newCenter[1] + point[1]  + 1) )
        temp = vectorize(points)
        for point in temp:
            newPoints.append(adduple(point, coord))

    try:
        #import pdb; pdb.set_trace()
        return pygame.draw.aalines(surface, color, False, newPoints)
        #return pygame.draw.lines(surface, color, False, newPoints, 2)
    except TypeError as e:
        print("TYPE ERROR IN graph FUNCTION: ", e)
        pass

def straighten(chain):
    """
    Return a straigthened chain
    """
    for index in range(len(chain)-2):
        straightened = False
        while not straightened:
            try:
                if pointToLine(chain[index+1], chain[index], chain[index+2]) / distance(chain[index], chain[index+2]) < 0.005\
                        or distance(chain[index], chain[index+1]) == 0:                     # Where 0.005 is a const deviation
                    del chain[index+1]
                else:
                    straightened = True
            except ZeroDivisionError:
                del chain[index]
                del chain[index]
            except IndexError:
                break

    return chain

def mirror(chain):
    """
    Returns new chain with mirrored points (of Ycoord of first element)
    """
    x = chain[0][0]
    points = chain
    for point in reversed(chain):
        points.append((x+x-point[0], point[1]))
    points = straighten(points)
    return points

def normalize(chain):
    """
    Returns the normalized version of chain (only actual coordinates left)
    """
    chain = straighten(chain)
    newChain = []
    minX, minY = None, None
    maxX, maxY = 0, 0
    for point in chain:
        # Min check
        if minX is None or point[0] < minX:     minX = point[0]
        if minY is None or point[1] < minY:     minY = point[1]
        # Max check
        if point[0] > maxX:     maxX = point[0]
        if point[1] > maxY:     maxY = point[1]
    width = maxX - minX; height = maxY - minY
        # Normalization
    for point in chain:
        newChain.append(( point[0] - minX , point[1] - minY))

    return newChain, width, height


def adduple(tuple1, tuple2):
    """ Vector addition """
    return tuple(x1+x2 for x1,x2 in zip(tuple1, tuple2))

def subuple(tuple1, tuple2):
    """ Vector substraction """
    return tuple(x1-x2 for x1,x2 in zip(tuple1, tuple2))

def vectorize(chain):
    new_chain = []
    if not isinstance(chain, list):
        chain = list(chain.points)
    coord0 = chain[0]
    for coord in chain:
        new_chain.append(subuple(coord, coord0))
    return new_chain

if __name__ == '__main__':
    #print (distance((0, 0), (3, 4)) )
    #print (middle((1,3),(26,3)) )
    chain = [(400, 400), (400,400), (500,400), (500,400), (500,400)]
    #props = [0.5, 0.5]
    #print (divideProp(chain, props))
    #print (middle ((1,0),(4,0), 1))
    #print(mirror([(1,1), (0,0)]))
    #print (pointToLine(chain[1], chain[0], chain[2]))
    print (straighten(chain))
    #print (pointToLine((0,100),(1,0),(3,0),True))
    #print(adduple((1,2),(-1,4)))
    #print(subuple((1,2),(-1,4)))
    #print (vectorize([(460, 300), (460, 320),(410, 320), (385, 345), (560, 345), (532, 318), (480, 317.5), (480, 300)]))
    pass
