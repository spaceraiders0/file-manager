"""Workspaces are classes that contain information about a directory
opened. New workspaces are only initialized when a workspace that has
not already been opened is entered.
"""

from pathlib import Path


class Workspace():
    def __init__(self, name: str, directory: Path = Path("~").expanduser()j):
        self.name = name
        self.opened_directory = directory

my_workspace = Workspace("a", "~")
