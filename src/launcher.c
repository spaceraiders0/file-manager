/*
 * The file that controls the file manager.
 *
 * The file manager is built around a loop that refreshes the screen as input
 * is given to it. Each iteration, a section of the currently active workspace
 * is printed out to the file display. Then, control is temporarily handed to a
 * "keyboard" module, which then handles input given to it.
 *
 * Most operations act upon the currently selected workspace. So when, Enter is
 * pressed, for example, the active workspace is passed to the keyboard module.
 * From there, the path is edited, and the loop refreshes, displaying the new
 * contents of the folder.
*/

#include <ncurses.h>
#include <stdlib.h>
#include "workspace/workspace.h"
#include "path/path.h"

#define ADD_BORDER(window) wborder(window, 124, 124, 45, 45, 43, 43, 43, 43)

#define FILE_WIDTH (int) percent_of(30, COLS)
#define TYPE_WIDTH (int) percent_of(10, COLS)

/*
 * An example of the screen.
 * +--------------+--------+----------------------+
 * |folder_a      | <DIR>  |                      |
 * |foobar_b      | <DIR>  |                      |
 * |foobar_c      | <DIR>  |                      |
 * |foobar.txt    | <FILE> |                      |
 * +--------------+--------+----------------------+
*/

float percent_of(int percent, int max) {
    /*
     * Calculates n percent of a maximum value.
     * @param percent: how much of max
     * @param max: the maximum value
     * @return: n percent of max
    */

    return ((max / 100.0f) * percent);
}

int main() {
    // Initialize the screen(s)
    WINDOW* standard_screen = initscr();
    WINDOW* file_display = newwin(LINES, FILE_WIDTH, 0, 0);
    WINDOW* type_display = newwin(LINES, TYPE_WIDTH, 0, FILE_WIDTH - 1);
    Workspace* new_workspace = workspace_new("/home/spaceraiders/.pki/", "workspace");

    ADD_BORDER(standard_screen);
    ADD_BORDER(file_display);
    ADD_BORDER(type_display);

    wrefresh(standard_screen);
    wrefresh(file_display);
    wrefresh(type_display);

    while (1) {
        // Draw the directory
        // Hand control over to the keyboard function
        workspace_dump(new_workspace, file_display);
        wrefresh(file_display);
        getch();
    }

    endwin();

    return 0;
}
