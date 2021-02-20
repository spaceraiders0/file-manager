"""The executable part of the file manager.
"""

import widgets
import settings

manager_settings = settings.load_settings()
print(widgets.workspace_list(1, manager_settings))
