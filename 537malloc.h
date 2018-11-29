#ifndef MALLOC_H_537
#define MALLOC_H_537

#include <stdlib.h>
#include <stdio.h>

/*
In addition to actually allocating the memory by calling malloc(), this function will record a tuple (addr, len), 
for the memory that you allocate in the heap. (If the allocated memory was previously freed, this will be a bit more complicated.) 
You will get the starting address, addr, from the return value of malloc() and the length, len, from the size parameter. 
Will report but not abort for a size parameter of zero length (this is unusual enough that it is worth reporting). 
*/
void* malloc537(size_t size);

/*
This function will first check to make sure that freeing the memory specified by ptr makes sense, then will call free() to do the actual free. 
Some of the error conditions that it checks for include:

    1. Freeing memory that has not be allocated with malloc537().
    2. Freeing memory that is not the first byte of the range of memory that was allocated.
    3. Freeing memory that was previously freed (double free). 

When an error is detected, this function prints out a detailed and informative error message and exits the program (with a -1 status). 
If all checks pass,then this function indicates that the tuple for addr = ptr is no longer allocated, and then calls free()
*/
void free537(void *ptr);

/*
If ptr is NULL,then this follows the specification of malloc537() above. If size is zero and ptr is not NULL,then this follows the specification of free537() above. 
Otherwise, in addition to changing the memory allocation by calling realloc(), this function will first check to see if there was a tuple for the (addr = ptr, and removes that tuple, 
then adds a new one where addr is the return value from realloc() and len is size
*/
void *realloc(void *ptr, size_t size);

/*
This function checks to see the address range specified by address ptr and length size are fully within a range allocated by malloc537() and memory not yet freed by free537(). 
When an error is detected, then print out a detailed and informative error message and exit the program (with a -1 status). 
*/
void memcheck537(void *ptr, size_t size);



#endif 