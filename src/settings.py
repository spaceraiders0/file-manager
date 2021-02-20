"""The settings manager for the file manager. This performs extraction,
and validation of the settings for the program. It also stores defaults,
and what qualifies as an "invalid" setting.
"""

import re
from pathlib import Path
from configparser import ConfigParser
from collections import namedtuple

setting = namedtuple("setting", "default validators")

ROOT_DIR = Path(__file__).parent.parent
SETTINGS = ROOT_DIR / Path("settings.ini")
DELIMITER_PATTERN = ", ?"
settings_parser = ConfigParser()
settings_information = {
    "workspaces": setting(["1", "2", "3", "4"], ([""], "")),
    "workspace_seperator": setting("-", ("",)),
}


def strip_delimiters(value: str, left_delim: str, right_delim: str) -> str:
    """Strips a value of it's delimiters. A list will have [], a str "",
    and etc.

    :param value: the value to strip of delimiters
    :type value: str
    :param left_delim: the left delimiter
    :type left_delim: str
    :param right_delim: the right delimiter
    :type right_delim: str
    :return: the stripped value
    :rtype: str
    """

    return value.lstrip(left_delim).rstrip(right_delim)


def is_valid_setting(key: str, cmp: any) -> bool:
    """Returns whether or not a given setting is valid.
    A valid setting is defined as a setting who's value
    does not equal the validator field of the setting.

    :param key: the name of the setting
    :type key: str
    :param cmp: the value to compare the setting's
            validators to
    :type cmp: any
    :raises: ValueError
    """

    try:
        validators = settings_information[key].validators
    except KeyError:
        raise ValueError(f"'{key}' is not a setting.")

    # Compares the value to every invalid option for a given
    # datatype.
    return not any(validator == cmp for validator in validators)


def typecast_setting(setting_name: str, value: str) -> [None, list, str, int]:
    """Returns a typecasted version of the provided value.

    :param setting_name: the name of the setting
    :type setting_name: str
    :param value: the value to typecast
    :type value: str
    :returns: the typecasted setting. returns None if the setting
        could not be casted for whatever reason.
    :rtype: None, list, str, int
    """

    try:
        default_value = settings_information[setting_name].default
    except KeyError:
        return None

    if isinstance(default_value, list):
        return re.split(DELIMITER_PATTERN,
                        strip_delimiters(value, "[", "]"))
    elif isinstance(default_value, int):
        return int(value)
    elif isinstance(default_value, str):
        return strip_delimiters(value, "\"'", "\"'")


def load_settings() -> dict:
    """Loads the settings, assigning defaults when needed.

    :returns: the loaded settings
    :rtype: dict
    :raises: ValueError
    """

    settings_parser.read(SETTINGS)
    loaded_settings = {setting_name: setting_data.default for setting_name, \
                       setting_data in settings_information.items()}

    for setting_name, setting_value in settings_parser["file_manager"].items():
        casted_value = typecast_setting(setting_name, setting_value)

        if is_valid_setting(setting_name, casted_value):
            loaded_settings[setting_name] = casted_value
        else:
            raise ValueError(f"Incorrect value for {setting_name}")

    return loaded_settings
