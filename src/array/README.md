# dynamic-array-macro
This is an implementation of a Dynamic Array in C. It is *entirely* macro based, so all you need to do is put the
header file into your project, and get started. A side effect of it being completely macro based is that allows for
you to write completely type-safe Dynamic Arrays that hold *any* type you want (however, they cannot be mixed datatypes).
</br>
It is inspired by the ``vec`` implementation by ``rxi``.
</br>
https://github.com/rxi/vec

# Adding Custom Types
Adding custom types is quite easy.
```c
typedef array_new(type*)* type_name;
```

Here is an example of a "Person" type:
```c
typedef struct Person {
    int   age;
    char* name;
    float height;
} Person;

...

typedef array_new(Person*)* array_person;
```

It should be noted, that the struct types put into ``array_new`` should be *pointers* to the type. This is so
operations done on them can set the contents to ``0``.

# How To Use
Setup is quite simple, and requires a minimum of two lines. Here is an example of an array that holds integers.
```c
#include "dynamic-array-macro/array.h"

int main() {
	// Array construction
    array_int int_container = array_allocate(array_int);
    array_init(int_container, 0.75, 2, 1);
    
    // Creating array entries
    for (int i = 0; i < 10; i++) {
    	array_append(int_container, i);
    }
    
    // Display the contents
    for (int i = 0; i < int_container->length; i++) {
        printf("Index %i: %i\n", i, int_container->data[i]);
	}
    
    /*
    Output:
	Index 0: 0
	Index 1: 1
	Index 2: 2
	Index 3: 3
	Index 4: 4
	Index 5: 5
	Index 6: 6
	Index 7: 7
	Index 8: 8
	Index 9: 9
   	*/
}
```

# Documentation
``array_allocate(type)``</br>
Allocates a new array with the size of a type. The type must be the same as the one assigned to the variable.</br>

``array_init(array, load_threshold, growth_factor, initial_size)``</br>
A constructor, in essense. Initializes all the values for the array. It must be given the value created with ``array_allocate``. The ``load threshold`` is the maximum load factor of the array before it can be resized. The ``growth_factor`` is how much the array should grow each resize. ``initial_size`` is how many slots should be reserved for the array beforehand.</br>

``array_append(array, value)``</br>
Appends a new value onto the end of the array.</br>

``array_insert(a, index, value)``</br>
Inserts a value at a given index in an array.</br>

``array_pop(a, index)``</br>
Pops a value from a given index in the array, and returns it.</br>

``array_find(a, value, var)``</br>
Finds the index of a value in an array, and assigns it to the variable ``var``.</br>

``array_free(a)``</br>
Frees the data and Struct of the array.

