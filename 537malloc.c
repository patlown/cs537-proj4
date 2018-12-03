/*Authors: Ge Xu, Patrick Lown 
*/
#include "537malloc.h"
static tree_node **root = NULL;

void malloccheck(void *ptr);

/*
this function will all malloc and record a tuple (addr, len), 
throw warning for a size parameter of zero length but continue executing. 
*/
void *malloc537(size_t size)
{

    if (size == 0)
    {
        fprintf(stderr, "Malloc size of 0!\n");
    }
    void *p = malloc(size);
    malloccheck(p);
    interval *in = new_interval(p, size);

    //to-do first malloc: initialize the tree
    if (root == NULL)
    {
        root = init_root();
        //assert(root!=NULL);
        in = new_interval(p, size);
        insert_node(root, in);
        return p;
    }

    tree_node *n;
    //if there is a node in the range that we see and it isn't freed, delete it
    while ((n = search_range(root, p, size)))
    {
        if (!n->freed)
        {
            fprintf(stderr, "Overlapping malloc of unfreed memory!\n");
            exit(-1);
        }
        /*
        check for case where free node, is before malloc'd range
        integer example: if n's tuple is (5,5) and new tuple is (7,8), we want to keep a tuple 5,1 and add new (7,8)
        */
        if (n->i->low < p)
        {
            n->i->len = (size_t)((char *)p - (char *)(n->i->low));
            continue;
        }
        delete_node(root, n);
    }

    //insert our new node into the tree.
    insert_node(root, in);
    return p;
}

/*
This function will first check to make sure that freeing the memory specified by ptr makes sense, then will call free() to do the actual free. 
Some of the error conditions that it checks for include:

    1. Freeing memory that has not be allocated with malloc537().
    2. Freeing memory that is not the first byte of the range of memory that was allocated.
    3. Freeing memory that was previously freed (double free). 

When an error is detected, this function prints out a detailed and informative error message and exits the program (with a -1 status). 
If all checks pass,then this function indicates that the tuple for addr = ptr is no longer allocated, and then calls free()
*/
void free537(void *ptr)
{
    if (root == NULL)
    {
        root = init_root();
    }
    tree_node *n = search_ptr(root, ptr);

    //check for issue 1.
    if (n == NULL || (n->freed && ptr != n->i->low))
    {
        fprintf(stderr, "Failed!! Trying to free memory that has not be allocated!\n");
        exit(-1);
    }
    //issue3: double free
    else if (n->freed && n->freed && ptr == n->i->low)
    {
        fprintf(stderr, "Failed!! Double Free!\n");
        exit(-1);
    }
    //issue2
    else if (ptr != n->i->low)
    {
        fprintf(stderr, "Failed!! Given ptr is not the first byte of allocated memory!\n");
        exit(-1);
    }
    else
    {
        n->freed = true;
    }
    return;
}

/*
If ptr is NULL,then this follows the specification of malloc537() above. If size is zero and ptr is not NULL,then this follows the specification of free537() above. 
Otherwise, in addition to changing the memory allocation by calling realloc(), this function will first check to see if there was a tuple for the (addr = ptr, and removes that tuple, 
then adds a new one where addr is the return value from realloc() and len is size
*/
void *realloc537(void *ptr, size_t size)
{
    if (root == NULL)
    {
        root = init_root();
    }
    //case1: given ptr is null
    if (ptr == NULL)
    {
        return malloc537(size);
    }
    //case2: given size is 0
    else if (size == 0)
    {
        fprintf(stderr, "Trying to realloc of size 0, freeing the ptr!\n");
        free537(ptr);
        return ptr;
    }
    //case 3: do regular realloc
    else
    {
        tree_node *n = search_ptr(root, ptr);
        if (n != NULL)
        {
            delete_node(root, n);
        }
        void *p = realloc(ptr, size);
        malloccheck(p);
        interval *in = new_interval(p, size);
        insert_node(root, in);
        return p;
    }
}

/*
This function checks to see the address range specified by address ptr and length size are fully within a range allocated by malloc537() and memory not yet freed by free537(). 
When an error is detected, then print out a detailed and informative error message and exit the program (with a -1 status). 
*/
void memcheck537(void *ptr, size_t size)
{
    if (root == NULL)
    {
        root = init_root();
    }
    tree_node *n = search_range(root, ptr, size);
    //case1: totaly missed i.e. the given memory doesn't overlap with any allocated
    if (n == NULL)
    {
        fprintf(stderr, "Address range specified by ptr and size are not allocated!\n");
        exit(-1);
    }
    //case2: find match interval
    if (ptr >= n->i->low && (ptr + size - 1) <= (n->i->low + n->i->len - 1))
    {
        if (n->freed)
        {
            fprintf(stderr, "Address range specified by ptr and size has been freed!\n");
            exit(-1);
        }
        return;
    }
    //case3: invalid address
    else
    {
        fprintf(stderr, "Address range specified by ptr and size spans out of a memory range that is currently allocated or freed\n");
        exit(-1);
    }
}
