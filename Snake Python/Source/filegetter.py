"""
    Loads files from a directory and saves them
    to a list that it returns.
"""

from fnmatch import fnmatch
from os import listdir
from os.path import isfile, join

def getfiles(filepath):
    """
    filepath : string, filepath from source file
    returns : list of file directions
    """
    file_list = []
    for file in listdir(filepath):
        if isfile(join(filepath, file)):
            file_list.append(join(filepath, file))

    return file_list

if __name__ == '__main__':
    my_list = getfiles('images/back')
    print (my_list)