#include "range_tree.h"


tree_node* new_tree_node(interval* i){
    
    tree_node* node = malloc(sizeof(tree_node));
    node->i = i;
    node->max = i->high;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
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

tree_node* insert_node(tree_node *root, interval *i){
    
    if(root == NULL){
	    return new_tree_node(i);
    }

    void* l = root->i->low;

    /*
        if current node's low is lower than the root's low, add it somewhere in the left subtree
        else, add it somewhere in the right subtree
    */

    if(i->low < l){
        root->left = insert_node(root->left,i);
    }else{
        root->right = insert_node(root->right,i);
    }

    //update the max value of the node
    insert_adjust(root);

    return root;


}


//bellow is the printing tree function
void print_inorder(tree_node* root, int level){

    if(root == NULL){
        return;
    }

    print_inorder(root->left, level + 1);

    printf("The current tree_node has low: %p, high: %p, max: %p, and level: %d\n", root->i->low, root->i->high, root->max,level);

    print_inorder(root->right, level + 1);
}


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

void print_t(tree_node *tree)
{
    char s[50][255];
    for (int i = 0; i < 50; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 50; i++)
        printf("%s\n", s[i]);
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
