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
    "workspace_seperator": setting("-", ("",))
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
    """

    validators = settings_information[key].validators

    return not any(validator == cmp for validator in validators)


def typecast_setting(setting_name: str, value: str) -> [None, list, str, int]:
    """Returns a typecasted version of the provided value.
    It will return the default value if it could not be casted.

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
    elif isinstance(default_value, str):
        return value
    else:
        return default_value


print(typecast_setting("workspaces", "1, 2, 3sssssdddd"))
