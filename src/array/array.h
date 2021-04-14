/*
 * Macros that allow for the creation of a Dynamic Array. This is something that
 * will be crucial to basically every other data structure, which will also be
 * implemented using Macros for purposes of generic-ness.
 *
*/

#ifndef DYNAMIC_ARRAY_
#define DYNAMIC_ARRAY_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_ITER(a, var) int var = 0; var < a->length; var++

// Defines struct types.
#define array_new(T)          \
    struct {                  \
        T* data;              \
        int length;           \
        int capacity;         \
        float growth_factor;  \
        float load_threshold; \
    }                         \

// Retrieves the size of the Array's data in bytes
#define array_size(a) \
    sizeof(a->data)

// Calculates the load factor of the Array
#define array_load_factor(a) \
    (double) a->length / (double) a->capacity

// Allocates space for the Array
#define array_allocate(t) \
    malloc(sizeof(t))

// Calculates the next capacity of the array.
#define array_new_capacity(a) \
    (int) (a->capacity * a->growth_factor)

// Initializes all the parts of the Array
#define array_init(a, threshold, growth, inital_size) \
    (a)->data = malloc(array_size(a) * inital_size);  \
    (a)->load_threshold = threshold;                  \
    (a)->growth_factor = growth;                      \
    (a)->capacity = inital_size + 1;                  \
    (a)->length = 0                                   \

// Resizes the array if necessary
#define array_resize(a) \
    if (array_load_factor(a) >= a->load_threshold) {                          \
        a->data = realloc(a->data, sizeof(a->data) * array_new_capacity(a)); \
                                                                              \
        if (a->data == NULL) {                                                \
            fprintf(stderr, "Ran out of memory!\n");                          \
            abort();                                                          \
        }                                                                     \
                                                                              \
        a->capacity = array_new_capacity(a);                                  \
                                                                              \
        for (int __i = a->length; __i < a->capacity; __i++) {                 \
            a->data[__i] = 0;                                                 \
        }                                                                     \
                                                                              \
    }                                                                         \

// Appends an item onto the array
#define array_append(a, value)      \
    array_resize(a);                \
    a->length++;                    \
    a->data[a->length - 1] = value; \

// Pop an index off of an array, shifting all values afterwards back by one.
#define array_pop(a, index)                                               \
    a->data[index];                                                       \
    a->data[index] = 0;                                                   \
                                                                          \
    for (int __a_index = index + 1; __a_index < a->length; __a_index++) { \
        a->data[__a_index - 1] = a->data[__a_index];                      \
        a->data[__a_index] = 0;                                           \
    }                                                                     \
                                                                          \
    if (a->length > 0) {                                                  \
        a->length--;                                                      \
    }                                                                     \

// Insert a value at a specific index in an Array.
#define array_insert(a, index, value)                        \
    if (index < 0 | index > a->length) {                     \
        fprintf(stderr, "Indexed out of bounds!\n");         \
        abort();                                             \
    }                                                        \
                                                             \
    array_resize(a);                                         \
                                                             \
    if (index == 0 && a->length == 0) {                      \
        array_append(a, value);                              \
    }                                                        \
    else {                                                   \
        for (int __i = a->length - 1; __i >= index; __i--) { \
            a->data[__i + 1] = a->data[__i];                 \
            a->data[__i] = 0;                                \
        }                                                    \
                                                             \
        a->length++;                                         \
        a->data[index] = value;                              \
    }                                                        \

// Find a value in an array.
#define array_find(a, value, var)               \
    var = -1;                                   \
                                                \
    for (int __i = 0; __i < a->length; __i++) { \
        if (a->data[__i] == value) {            \
            var = __i;                          \
        }                                       \
    }                                           \

// Free the Array.
#define array_free(a) \
    free(a->data);    \
    free(a)           \

typedef array_new(int)* ArrayInt;
typedef array_new(char)* ArrayChar;
typedef array_new(float)* ArrayFloat;
typedef array_new(double)* ArrayDouble;
typedef array_new(char*)* ArrayString;
typedef array_new(void*)* ArrayVoid;

#endif
