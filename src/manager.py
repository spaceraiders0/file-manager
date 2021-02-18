"""The executable part of the file manager.
"""

import definitions

settings = definitions.load_settings()
workspace_list = settings["workspace_separator"].join(settings["workspaces"])

print(f"[ {workspace_list} ]")
