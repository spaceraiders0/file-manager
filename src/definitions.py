"""Contains commonly used functions by other parts of this project.
"""

import colorama

HIGHLIGHT_COLOR = colorama.Back.GREEN
RESET = colorama.Back.RESET


def truncate(text: str, width: int, truncate_text: str = "..."):
    """Replaces text in a string past a certain width with a truncated
    string.

    :param text: the text to truncate
    :type text: str
    :param width: how long the string can be until it is truncated.
    :type width: int
    :param truncate_text: the text to truncate with.
    :type truncate_text: str
    :raises ValueError
    """

    if width < 0 or isinstance(width, float):
        raise ValueError("Width must be a positive integer.")

    if width >= len(text):  # No text needs to be truncated
        return text
    else:
        return text[:width] + truncate_text


def highlight(text: str, index: int, highlight_range: range) -> str:
    """Returns a string highlighted by the highlight color if
    is it in the highlight range.

    :param text: the text to highlight
    :type text: str
    :param index: the index of this text in the sequence
    :type index: int
    :param highlight_range: the range of indexes to highlight.
    """

    if index in highlight_range:
        return HIGHLIGHT_COLOR + text + RESET
    else:
        return text
