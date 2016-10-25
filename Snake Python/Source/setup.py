# WORKING!!!

from cx_Freeze import setup,Executable
from glob import glob
import sys

includefiles = [('sounds', glob('.sounds/*')), ('images',glob('.images/*.')), 'highscore.txt']
includes = []
excludes = []
packages = []#'filegetter','pygame'

base = None
if sys.platform == "win32":
    base = "Win32GUI"

setup(
    name = 'EDos Snake',
    version = '0.5',
    description = 'Snake game',
    author = 'EDos',
    author_email = 'edvard.zoo@gmail.com',
    options = {'build_exe': {'excludes':excludes,'packages':packages,'include_files':includefiles}},    # Do not edit
    executables = [Executable(script='first.py', base=base, icon='pygame.ico')]  # Edit with main filename
)
