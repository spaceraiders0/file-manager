"""Uses Curses to detect non-blocking input while the terminal is
focused,

Lots of help from this StackOverflow post, modified by me.:
https://stackoverflow.com/questions/2408560/python-nonblocking-console-input
"""

import string
import curses

# Important keys
ENTER = chr(10)
ESCAPE = chr(27)
BACKSPACE = chr(127)

class KeyboardManager():
    """Manages the keyboard, and commands bound to it.
    Also handles mode switching.
    """

    def __init__(self):
        self.modes = {}
        self.keybinds = {}

    
