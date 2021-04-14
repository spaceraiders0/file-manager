#ifndef WORKSPACE_H_
#define WORKSPACE_H_

#include <curses.h>
#include "../array/array.h"

typedef struct Range {
    int start;
    int stop;
} Range;

typedef struct Workspace {
    char*        directory;
    char*        label;
    Range*       draw;
    Range*       selection;
    ArrayString contents;
} Workspace;

Workspace* workspace_new(char* initial_path, char* label);
void workspace_dump(Workspace* workspace, WINDOW* display);

#endif
