/*
 * A library of commonly used Path operations.
*/

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "../array/array.h"
#include "../utilities//utilities.h"

char* path_type(char* path) {
    /*
     * Determines the type of object the given path points to.
     * @param path: the Path to check
     * @return: the type of Path
    */

    struct stat stat_buffer;
    stat(path, &stat_buffer);

    if (S_ISREG(stat_buffer.st_mode) == 1) {
        return "file";
    }
    else if (S_ISDIR(stat_buffer.st_mode) == 1) {
        return "directory";
    }
    else if (S_ISFIFO(stat_buffer.st_mode) == 1) {
        return "pipe";
    }
    else if (S_ISCHR(stat_buffer.st_mode) == 1) {
        return "character";
    }
    else if (S_ISSOCK(stat_buffer.st_mode) == 1) {
        return "socket";
    }
    else if (S_ISLNK(stat_buffer.st_mode) == 1) {
        return "symbolic-link";
    }
    else if (S_ISBLK(stat_buffer.st_mode) == 1) {
        return "block";
    }

    return "none";
}

char* path_join(char* src, char* dst) {
    /*
     * Joins two paths.
     * @param src: the first path
     * @param dst: the second path
     * @return: the result of the two paths joined.
    */

    int total_space = strlen(src) + strlen(dst) + 1;
    int offset = 0;
    char* string_space = malloc(total_space);
    check_null(string_space, "Ran out of memory!");

    string_space[total_space - 1] = '\0';

    // Append the first string
    for (int i = 0; i < strlen(src); i++) {
        string_space[offset] = src[i];
        offset++;
    }

    // Append the last string
    for (int i = 0; i < strlen(dst); i++) {
        string_space[offset] = dst[i];
        offset++;
    }

    return string_space;
}

char* path_makedir(char* path) {
    /*
     * Appends a forward slash onto the given path if it is a directory and it does
     * not already have one.
     * 
     * @param path: the path to make into a directory
     * @return: the created path
    */

    // Only directories can be passed through
    if (strcmp(path_type(path), "directory") != 0) {
        fprintf(stderr, "%s\n", path_join(path, " is not a directory!"));
        abort();
    }

    if (path[strlen(path) - 1] == '/') {
        return path;
    }

    // Make the new path with a forward slash
    char* new_path = malloc(strlen(path));
    check_null("Ran out of memory!", new_path);

    new_path[strlen(path) + 1] = '\0';
    new_path[strlen(path)] = '/';

    // Add the new path
    for (int i = 0; i < strlen(path); i ++) {
        new_path[i] = path[i];
    }

    return new_path;
}

void path_dump(char* path, ArrayString dump) {
    /*
     * Dumps the contents of a path to an array.
     * @param path: the path to load
     * @param dump: the array to dump to
    */

    // You can only dump the contents of a directory
    if (strcmp(path_type(path), "directory") != 0) {
        fprintf(stderr, "%s\n", path_join("Attempted to dump the contents of a non-directory: ", path));
        abort();
    }

    DIR* dir_stream = opendir(path);

    while (1) {
        struct dirent* entry = readdir(dir_stream);
        // fprintf(stderr, "%s\n", entry->d_name);
        // abort();

        // End of stream, or an error.
        if (entry == NULL) {
            break;
        }

        // Append a copy to the array
        char* name_copy = malloc(strlen(entry->d_name) + 1);
        check_null("Ran out of memory!", name_copy);
        strcpy(name_copy, entry->d_name);
        array_append(dump, name_copy);
    }

    closedir(dir_stream);
}
