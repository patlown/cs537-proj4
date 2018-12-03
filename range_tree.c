/*Authors: Ge Xu, Patrick Lown 
*/
#include "range_tree.h"

/*
    Private function headers
*/
void insert_fix(tree_node **root, tree_node *z);
void rotate_right(tree_node **root, tree_node *x);
void rotate_left(tree_node **root, tree_node *x);
void transplant(tree_node **root, tree_node *u, tree_node *v);
void delete_fix(tree_node **root, tree_node *x);
void malloccheck(void *ptr);


static tree_node nil_node;

tree_node *root = NULL;
static tree_node *nil = &nil_node;


tree_node **init_root()
{
    root = nil;
    root->color = 'b';
    return &root;
}

tree_node *new_tree_node(interval *i)
{

    tree_node *node = malloc(sizeof(*node));
    malloccheck(node);
    node->i = i;
    node->left = nil;
    node->right = nil;
    node->parent = nil;
    node->color = 'r';
    return node;
}

interval *new_interval(void *ptr, size_t size)
{

    interval *i = malloc(sizeof(*i));
    malloccheck(i);
    i->low = ptr;
    /*
        given the size, we want to add that size to the pointer, cast to char so we only increment exactly the number of bytes needed
    */
    i->len = size;

    return i;
}



void insert_node(tree_node **root, interval *i)
{

    tree_node *new = new_tree_node(i);
    tree_node *y = nil;
    tree_node *x = *root;

    //find where new node is to be inserted
    while (x != nil)
    {

        y = x;
        if (new->i->low < x->i->low)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    //if y is still nil, then new node is the root
    new->parent = y;
    if (y == nil)
    {
        *root = new;
    }
    else if (new->i->low < y->i->low)
    {
        y->left = new;
    }
    else
    {
        y->right = new;
    }

    //set new node with nil children
    new->right = nil;
    new->left = nil;
    new->color = 'r';
    insert_fix(root, new);
}

/*
This is a helper function for the insert_node function.  insert_node() works as a standard
BST insertion and insert_fix() fixes any violations of the RBT properties caused by the insertion
*/
void insert_fix(tree_node **root, tree_node *z)
{
    tree_node *y;
    //iterate until z isn't root and z's parent color is red
    while (z->parent->color == 'r')
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y->color == 'r')
            {
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rotate_left(root, z);
                }
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                rotate_right(root, z->parent->parent);
            }
        }
        else
        {
            //this case is the same as the prev. with all right replaced with left
            y = z->parent->parent->left;
            if (y->color == 'r')
            {
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rotate_right(root, z);
                }
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                rotate_left(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 'b';
}

/*
This function does a right rotate in order to maintain properties of a RBT.

-right_rotate and left_rotate are symmetrical functions
*/
void rotate_right(tree_node **root, tree_node *x)
{
    tree_node *y = x->left;
    //turn y's right subtree into x's left subtree
    x->left = y->right;
    if (y->right != nil)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == nil)
    {
        *root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    //put x on y's right
    y->right = x;
    x->parent = y;
}

/*
This function does a left rotate in order to maintain properties of a RBT.
*/
void rotate_left(tree_node **root, tree_node *x)
{
    //set y
    tree_node *y = x->right;
    //turn y's left subtree into x's right subtree
    x->right = y->left;
    if (y->left != nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == nil)
    {
        *root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    //put x on y's left
    y->left = x;
    x->parent = y;
}

/*
Used for swapping in order successor of u with v
*/
void transplant(tree_node **root, tree_node *u, tree_node *v)
{
    if (u->parent == nil)
    {
        *root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

/*
 This function will return the in order successor for a node, it assumes z has a
 right child
*/
tree_node *tree_min(tree_node *x)
{
    while (x->left != nil)
    {
        x = x->left;
    }
    return x;
}

void delete_node(tree_node **root, tree_node *z)
{
    tree_node *x;
    tree_node *y;
    y = z;
    char y_orig_color = y->color;
    if (z->left == nil)
    {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == nil)
    {
        x = z->left;
        transplant(root, z, z->left);
    }
    else
    {
        //set y to be successor of z
        y = tree_min(z->right);
        y_orig_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_orig_color == 'b')
    {
        //call delete fixup
        delete_fix(root, x);
    }
}

/*
Helper function for delete_node, this will restore any distrubed properties of the RBT
when deleting a node.
*/
void delete_fix(tree_node **root, tree_node *x)
{
    tree_node *w;
    while (x != *root && x->color == 'b')
    {
        //check if x is the left child
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == 'r')
            {
                w->color = 'b';
                x->parent->color = 'r';
                rotate_left(root, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == 'b' && w->right->color == 'b')
            {
                w->color = 'r';
                x = x->parent;
            }
            else if (w->right->color == 'b')
            {
                w->left->color = 'b';
                w->color = 'r';
                rotate_right(root, w);
                w = x->parent->right;
            }
            else
            {
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->right->color = 'b';
                rotate_left(root, x->parent);
                x = *root;
            }
        }
        else
        {
            //this is the symmetric case, here: x is the right child
            w = x->parent->left;
            if (w->color == 'r')
            {
                w->color = 'b';
                x->parent->color = 'r';
                rotate_right(root, x->parent);
                w = x->parent->left;
            }

            if (w->left->color == 'b' && w->right->color == 'b')
            {
                w->color = 'r';
                x = x->parent;
            }
            else if (w->left->color == 'b')
            {
                w->right->color = 'b';
                w->color = 'r';
                rotate_left(root, w);
                w = x->parent->left;
            }
            else
            {
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->left->color = 'b';
                rotate_right(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = 'b';
}



tree_node *search_ptr(tree_node **root, void *ptr)
{
    tree_node *x = *root;

    //find where new node is to be inserted
    while (x != nil)
    {
        if (ptr >= x->i->low && ptr <= (x->i->low + x->i->len - 1))
        {
            return x;
        }
        else if (ptr < x->i->low)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return NULL;
}

int is_overlap(interval *i1, interval *i2)
{
    if (i1->low <= (i2->low + i2->len - 1) && i2->low <= (i1->low + i1->len - 1))
    {
        return 1;
    }
    return 0;
}


tree_node *search_range(tree_node **root, void *ptr, size_t size)
{
    tree_node *x = *root;
    interval *in = malloc(sizeof(*in));
    malloccheck(in);
    in->low = ptr;
    in->len = size;
    //find where new node is to be inserted
    while (x != nil)
    {
        if (is_overlap(in, x->i))
        {
            free(in);
            return x;
        }
        else if (ptr < x->i->low)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    free(in);
    return NULL;
}

/*this function check the malloc call is successful returned*/
void malloccheck(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "cannot allocate mem\n");
        exit(-1);
    }
}

