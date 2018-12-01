#ifndef RANGE_TREE_H
#define RANGE_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct interval interval;
typedef struct tree_node tree_node;



/*
This structure will hold intervals of address ranges.
The low will represent the lower addr and high will represent higher addr
This will be used with as a data field for interval tree structure nodes.
*/
struct interval
{
    void* low;
    int len;
    //bool freed;

};

/*
This will be used as the main data structure for implementing ranged queuries
Each tree_node will store an interval, a max value for the highest addr in its right subtree,
and pointers to its left and right subtree. The struct and idea for this structure and its properties were
inspired by this implementation of an interval tree: https://www.geeksforgeeks.org/interval-tree/
*/
struct tree_node
{
    interval *i;
    void* max;
    tree_node *left,*parent,*right;
    char color;
    bool freed;
};

/*
This function will construct a new interval for use in a tree_node for the interval tree.
*/
interval* new_interval(void* ptr, size_t size);

/*
This function will construct a new tree node and return the addr of it, the required parameter
will be the interval of addresses that this tree node will store.  Its max will be the value of its high addr.
Both children will be set to NULL
*/
tree_node* new_tree_node(interval* i);

/*
This function initializes the root node of the tree
*/
void init_root(tree_node** root);

/*
This function will insert a node in the tree based on the lower value of interval passed in.  The implementation
of this tree is currently that of a Red Black Tree.  This guarentees insertions in O(logn) time as the RBT
always remains "balanced"

The algorithm for this function is drawn heavily from "Introduction to Algorithms, Third Edition
3rd" by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein Chapter 13: Red Black Trees
Additionally, https://stackoverflow.com/questions/42800462/trying-to-implement-a-red-black-tree-in-c and
https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/ were used as resources for implementation
*/
void insert_node(tree_node **root, interval* i);

/*
This function, checks, for the given node, if either child's max is greater than it's own.  If so, adjusts its own max
*/
void insert_adjust(tree_node* node);

/*
This function will delete a tree node in the current interval tree.  Has potential to change the max for interval nodes.
https://stackoverflow.com/questions/28012126/trouble-deleting-a-node-in-red-black-tree-c-code
*/
void delete_node(tree_node** root, tree_node *node);

/*
Simple function that checks if two intervals overlap with each other.  Used in functions throughout this header file.
Returns 1 if intervals overlap, 0 if they do not
*/
int does_overlap(interval i, interval j);


/*
This function will check the interval tree to see if the interval passed in overlaps with
any of the intervals currently in the tree.  It will return 1 if an overlapping interval is found
and 0 if no overlapping intervals are found.
Complexity: O(logn) time for check
*/
tree_node* search_range(tree_node **root, void* ptr, size_t size);




/*
This function will print the tree in level order
*/
void print_inorder(tree_node* root, int level);

void print_lvlorder(tree_node* root);

/*
This function will search for the node that contains this ptr address, if not found return NULL
*/
tree_node* search_ptr(tree_node **root, void* ptr);


void print_node(tree_node* node);

void print_lvl(struct tree_node* root);



#endif
