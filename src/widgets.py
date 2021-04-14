"""Contains the code for all the widgets.
"""

import definitions


def workspace_list(settings: dict, selection: int) -> str:
    """Creates and formats a string that contains the list of
    workspaces, and highlights the currently selected workspace.

    :param settings: the settings that contains the list of
            workspaces to use.
    :type settings: dict
    :param selection: the selected workspace. defaults to the first
    :type selection: int
    :return: the formatted string of workspaces.
    :rtype: str
    """

    built_widget = ""
    seperator = settings["workspace_seperator"]
    workspaces = settings["workspaces"]

    for index, workspace in enumerate(workspaces):
        # Prevents the seperator from being appended on the last
        # workspace in the list.
        if index == len(workspaces) - 1:
            seperator = ""

        if index == selection:
            built_widget += definitions.HIGHLIGHT_COLOR + workspace \
                            + definitions.RESET + seperator
        else:
            built_widget += workspace + seperator

    return built_widget
