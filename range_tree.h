#ifndef RANGE_TREE_H
#define RANGE_TREE_H


/*
This structure will hold intervals of address ranges.
The low will represent the lower addr and high will represent higher addr
This will be used with as a data field for interval tree structure nodes.
*/
typedef struct interval
{
    size_t low;
    size_t high;
} interval;

typedef struct tree_node
{
    interval *i;
    size_t max;
    tree_node *left;
    tree_node *right;
} tree_node;

#endif RANGE_TREE_H