#ifndef PATH_H_
#define PATH_H_

#include "../array/array.h"

char* path_type(char* path);
char* path_join(char* src, char* dst);
char* path_makedir(char* path);
void path_dump(char* path, ArrayString dump);

#endif
