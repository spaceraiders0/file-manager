/*
 * A workspace is the base object that the file manager used to retrieve
 * information about, and operate upon, the file system. Each workspace has a
 * variety of components associated with it, including:
 * - The current path
 *   The files contained in the folder.
 * - The name of the workspace (label)
*/

#include <string.h>
#include "workspace.h"
#include "../array/array.h"
#include "../utilities/utilities.h"
#include "../path/path.h"
#include <ncurses.h>

Range* range_new(int start, int stop) {
    /*
     * Creates a new range object.
     * @param start: the start of the range
     * @param stop: the end of the range
     * @return: pointer to the new range
    */

    Range* new_range = malloc(sizeof(Range));
    check_null("Ran out of memory!", new_range);

    new_range->start = start;
    new_range->stop = stop;

    return new_range;
}

Workspace* workspace_new(char* initial_path, char* label) {
    /*
     * Creates a new workspace with some base settings. It also loads the
     * directory's contents.
     * @param initial_path: the path to load in by default
     * @param label: the name of the workspace
     * @return: pointer to the new workspace
    */

    // Verify that the initial_path is a directory
    if (strcmp(path_type(initial_path), "directory") != 0) {
        fprintf(stderr, "%s\n", path_join(initial_path, " is not a directory!"));
        abort();
    }

    // Create a new workspace
    Workspace* new_workspace = malloc(sizeof(Workspace));
    check_null("Ran out of memory!", new_workspace);

    new_workspace->draw = range_new(0, 0);
    new_workspace->selection = range_new(0, 0);
    new_workspace->label = label;
    new_workspace->directory = initial_path;
    new_workspace->draw->stop = LINES - 2;
    new_workspace->contents = array_allocate(ArrayString);
    array_init(new_workspace->contents, 0.75, 2, 5);

    // Load the directory
    path_dump(initial_path, new_workspace->contents);

    return new_workspace;
}

void workspace_dump(Workspace* workspace, WINDOW* display) {
    /*
     * Dumps the contents of the given workspace to the display based off the
     * range to draw from. This also assumes that the contents of the workspace
     * have been loaded into it.
     *
     * @param workspace: the workspace to dump the contents of
     * @param display: the display to dump to
    */

    for (int line = 0; line < workspace->contents->length; line++) {
        int contents_index = workspace->draw->start + line;

        // No going past the number of items in the directory
        if (contents_index == workspace->draw->stop) {
            return;
        }

        mvwaddstr(display, line + 1, 1, workspace->contents->data[contents_index]);
    }
}
