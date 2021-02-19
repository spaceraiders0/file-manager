"""Functions and other utilities used by the main executable
file.
"""

import re
from pathlib import Path
from configparser import ConfigParser

ROOT_DIR = Path(__file__).parent.parent
SETTINGS = ROOT_DIR / Path("settings.ini")
DELIMITER_PATTERN = ", ?"
settings_parser = ConfigParser()
base_settings = {
    "workspaces": ['1', '2', '3', '4'],
    "workspace_separator": " ",
}


def strip_surrounds(value: str, surround: list[str, str]) -> str:
    """Strips the surrounding text in a value. Usually
    []'s, ()'s, or ""'s

    :param value: the string to strip
    :type value: str
    :param surround: the surrounding characters to strip.
    :type surround: list[str, str]
    """

    return value.lstrip(surround[0]).rstrip(surround[1])


def load_settings() -> dict:
    """Loads settings from the settings module, making a bare
    skeleton settings file if it does not exist.

    :returns: the settings in form of a dictionary
    :rtype: dict
    """

    loaded_settings = base_settings.copy()
    settings_parser.read(SETTINGS)

    # Load all settings.
    for key, value in settings_parser["file_manager"].items():
        try:
            # Determine how this value should be casted depending
            # on the type of the default value.
            if isinstance(loaded_settings[key], list):
                stripped_value = strip_surrounds(value, ["[", "]"])
                loaded_settings[key] = re.split(DELIMITER_PATTERN,
                                                stripped_value)
            elif isinstance(loaded_settings[key], int):
                loaded_settings[key] = int(value)
            else:
                loaded_settings[key] = strip_surrounds(value, ["'\"", "'\""])
        except KeyError:
            raise ValueError(f"{key} is not a valid setting.")

    return loaded_settings

def validate_settings(settings_dict: dict):
    """Takes in a dictionary of settings and attempts to validate
    them.
    """

    if settings_dict["workspaces"] == ['']:



def truncate_text(text: str, width: int, truncate_char: str = "..."):
    """Truncates text with a given truncation character.

    :param text: the text to truncate
    :type text: str
    :param width: how long the text should be before being
            truncated.
    :type width: int
    :param truncate_char: the text to truncate with
    :type truncate_char: str, defaults to "..."
    """

    min_text = text[:width - len(truncate_char)]
