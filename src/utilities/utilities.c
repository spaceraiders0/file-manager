/*
 * A collection of commonly used operations.
*/

#include <stdio.h>
#include <stdlib.h>

void check_null(char* err, void* ptr) {
    /*
     * A guard to make sure the given pointer is not NULL, aborting if it is.
    */

    if (ptr == NULL) {
        fprintf(stderr, "%s\n", err);
        abort();
    }
}
