#include "range_tree.h"

/*
    Private function headers
*/
void insert_fix(tree_node** root, tree_node* z);
tree_node* find_uncle(tree_node* node);
void rotate_right(tree_node** root, tree_node* x);
void rotate_left(tree_node** root, tree_node* x);

//----------------------------------------------

static tree_node nil_node;

tree_node* root = NULL;
static tree_node* nil = &nil_node;

tree_node** init_root(){
    root = nil;
    //root->i = new_interval(NULL,0);
    root->color = 'b';

    return &root;
}

tree_node* new_tree_node(interval* i){
    
    tree_node* node = malloc(sizeof(tree_node));
    node->i = i;
    node->max = i->high;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = 'r';
    return node;
}

interval* new_interval(void* ptr, size_t size){

    interval* i = malloc(sizeof(interval));
    i->low = ptr;
    /*
        given the size, we want to add that size to the pointer, cast to char so we only increment exactly the number of bytes needed
    */
    i->high = ((char*)ptr) + size;

    return i;
}

void insert_adjust(tree_node* node){

    //checks if left child's max is greater than its own
    if(node->left != NULL){
        if(node->max < node->left->max){
            node->max = node->left->max;
        }
    }
    //checks if right child's max is greater than its own
    if(node->right != NULL){
        if(node->max < node->right->max){
            node->max = node->right->max;
        }
    }
}

void insert_node(tree_node **root, interval *i){
    
    tree_node* new = new_tree_node(i);
    tree_node* y = nil;
    tree_node* x = *root;
    
    //find where new node is to be inserted
    while(x != nil){
        
        y=x;
        if(new->i->low < x->i->low){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    //if y is still nil, then new node is the root
    new->parent = y;
    if(y == nil){
        *root = new;
    }else if(new->i->low < y->i->low){
        y->left = new;
    }else{
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
void insert_fix(tree_node** root, tree_node* z){
    tree_node* y;
    //iterate until z isn't root and z's parent color is red
    while(z->parent->color == 'r'){
        if(z->parent->i->low == z->parent->parent->i->low){
            y = z->parent->parent->right;
            if(y->color == 'r'){
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                z = z->parent->parent;
            }
            else if(z->i->low == z->parent->right->i->low){
                z = z->parent;
                rotate_left(root, z);
            }
            z->parent->color = 'b';
            z->parent->parent->color = 'r';
            rotate_right(root,z->parent->parent);
        }else{
            //this case is the same as the prev. with all right replaced with left
            y = z->parent->parent->left;
            if(y->color == 'r'){
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                z = z->parent->parent;
            }else if(z->i->low == z->parent->left->i->low){
                z = z->parent;
                rotate_right(root,z);
            }
            z->parent->color = 'b';
            z->parent->parent->color = 'r';
            rotate_left(root,z->parent->parent);
        }
    }
    root[0]->color = 'b';

    

}

/*
This function does a right rotate in order to maintain properties of a RBT.

-right_rotate and left_rotate are symmetrical functions
*/
void rotate_right(tree_node** root, tree_node* x){
    tree_node* y = x->left;
    //turn y's right subtree into x's left subtree
    x->left = y->right;
    if(y->right != nil){
        y->right->parent = x;
    }
    y->parent = x->parent;
    
    if(x->parent == nil){
        *root = y;
    }else if(x == x->parent->right){
        x->parent->right = y;
    }else{
        x->parent->left = y;
    }
    //put x on y's right
    y->right = x;
    x->parent = y;
}
/*
This function does a left rotate in order to maintain properties of a RBT.
*/
void rotate_left(tree_node** root, tree_node* x){
    //set y
    tree_node* y = x->right;
    //turn y's left subtree into x's right subtree
    x->right = y->left;
    if(y->left != nil){
        y->left->parent = x;
    }
    y->parent = x->parent;

    if(x->parent == nil){
        *root = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }
    //put x on y's left
    y->left = x;
    x->parent = y;
}

/*
This function takes in a node and returns the uncle of that node
*/
tree_node* find_uncle(tree_node* node){
    if(node->parent == node->parent->parent->left){
        return node->parent->parent->right;
    }
    return node->parent->parent->left;
}



//bellow is the printing tree function
void print_inorder(tree_node* root, int level){

   if(root == nil){
        return;
    }

    print_inorder(root->left, level + 1);

    printf("The current tree_node has low: %p, high: %p, max: %p, and level: %d\n", root->i->low, root->i->high, root->max,level);

    print_inorder(root->right, level + 1);
}

/*
Helper method for printing the tree
*/
int _print_t(tree_node *tree, int is_left, int offset, int depth, char s[50][255])
{
    char b[50];
    int width = 30;

    if (!tree) return 0;

    sprintf(b, "%p==%p", tree->i->low,tree->i->high);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}
/*
This method prints the tree
*/
void print_t(tree_node *tree)
{
    char s[50][255];
    for (int i = 0; i < 50; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 50; i++)
        printf("%s\n", s[i]);
}


int main(){
    root  = nil;

    int* x = malloc(sizeof(int));
    int* y = malloc(sizeof(int));
    int* z = malloc(sizeof(int));
    int* w = malloc(sizeof(int));


    interval* xi = new_interval((void*)x,sizeof(int));
    interval* yi = new_interval((void*)y,sizeof(int));
    interval* zi = new_interval((void*)z,sizeof(int));
    interval* wi = new_interval((void*)w,sizeof(int));

    insert_node(&root,xi);
    insert_node(&root, yi);
    insert_node(&root,zi);
    insert_node(&root, wi);
}
// int main(){
//     tree_node *tree = malloc(sizeof(tree_node));
    
//     interval *i1 = malloc(sizeof(interval));
//     void *ptr = malloc(sizeof(10));
//     i1->low = ptr;
//     i1->high = ptr+10;

//     tree->i = i1;

//     tree_node *l = malloc(sizeof(tree_node));
    
//     interval *i2 = malloc(sizeof(interval));
//     void *ptr1 = malloc(sizeof(10));
//     i2->low = ptr1;
//     i2->high = ptr1+10;

//     l->i = i2;
//     l->right = NULL;
//     l->left = NULL;


//     tree_node *r = malloc(sizeof(tree_node));
    
//     interval *i3 = malloc(sizeof(interval));
//     void *ptr2 = malloc(sizeof(10));
//     i3->low = ptr2;
//     i3->high = ptr2+10;

//     r->i = i3;
//     r->right = NULL;
//     r->left = NULL;
    
//     tree->left = l;
//     tree->right = r;


//     print_t(tree);
// }
