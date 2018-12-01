#include "537malloc.h"
static tree_node **root =NULL;


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
    void *ptr = malloc(size);
    malloccheck(ptr);
    interval *in;

    //to-do first malloc: initialize the tree
    if(root == NULL){
        root = init_root(root);
        in = new_interval(ptr,size);
        insert_node(root,in);
    }

    tree_node *n;
    //if there is a node in the range that we see and it isn't freed, delete it
    while ((n = search_range(root, ptr, size)))
    {
        if(!n->freed){
            fprintf(stderr,"Overlapping malloc of unfreed memory!\n");
            exit(1);
        }
        /*
        check for case where free node, is before malloc'd range
        integer example: if n's tuple is (5,5) and new tuple is (7,8), we want to keep a tuple 5,1 and add new (7,8)
        */
        if(n->i->low < ptr){
            n->i->len = (size_t)((char*)ptr - (char*)(n->i->low));
            break;
        }
        delete_node(root,n);
    }

    //print function for testing, REMOVE
    print_inorder(*root,0);

    in = new_interval(ptr,size);
    //insert our new node into the tree.
    insert_node(root,in);
    return ptr;
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
void free537(void *ptr){

    //check for issue 1.


}

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
void memcheck537(void *ptr, size_t size)
{
}


void malloccheck(void *ptr){
    if (ptr == NULL)
    {
        fprintf(stderr, "cannot allocate mem\n");
        exit(1);
    }
}