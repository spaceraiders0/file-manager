"""Workspaces are classes that contain information about a directory
opened. New workspaces are only initialized when a workspace that has
not already been opened is entered.
"""

import definitions
from pathlib import Path


class Workspace():
    selection = slice(0, 1)

    def __init__(self, name: str, directory: Path = Path("~").expanduser()):
        self.name = name
        self.opened_directory = Path(directory).expanduser()


    def open_directory(self, dir_index: int):
        """Opens a directory from the current working directory.

        :param dir_index: the index of the directory to open
        :type dir_index: int
        :raises: IndexError
        """

        for index, path in enumerate(self.opened_directory.iterdir()):
            if index == dir_index:
                self.opened_directory = path
            
                self.selection = range(0, 1)
                return

        raise IndexError(f"{dir_index} is not a valid index.")


    def list_contents(self, max_name_width: int = 20, truncate: bool = True,
            show_indices: bool = False, highlight: bool = True):

        """Returns a list containing the contents of a directory, with optional
        truncation of the files.

        :param max_name_width: the maximum length of a file name
                    before it is truncated
        :type max_name_width: int, defaults to 20
        :param truncate: whether or not to truncate the file name
        :type truncate: bool, defaults to True
        :param show_indices: whether or not to show the indices
                before the filename.
        :type show_indices: bool, defaults to False
        :param highlight: whether or not to highlight selected
                directories.
        :type highlight: bool, defaults to True.
        :return: the dict of all files or folders in this directory,
                where each key is the name, and the value is the path.
        :rtype: dict
        """

        contents = {}

        for index, path in enumerate(self.opened_directory.iterdir()):
            path_name = path.name

            if show_indices is True:
                path_name = f"{index} {path_name}"

            if truncate is True:
                path_name = definitions.truncate(path_name, max_name_width)

            if highlight is True:
                path_name = definitions.highlight(path_name, index,
                                                  self.selection)

            contents[path_name] = path

        return contents


    def selection_shift(self, direction: int, count: int = 1):
        """Shifts the selected up or down by a specific amount.

        :param count: how many times to shift
        :type count: int, defaults to 1
        :param direction: to shift up or down
        :type direction: int
        """

        new_step = abs((self.selection.start + step) % len(self.wallpaper_cache))


my_workspace = Workspace("a", "~")
print(*my_workspace.list_contents(20, show_indices=True), sep="\n")
my_workspace.open_directory(3)
print("\n")
print(*my_workspace.list_contents(20, show_indices=True), sep="\n")
