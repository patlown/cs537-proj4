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

void print_inorder(tree_node* root, int level){

    if(root == NULL){
        return;
    }

    print_inorder(root->left, level + 1);

    printf("The current tree_node has low: %p, high: %p, max: %p, and level: %d\n", root->i->low, root->i->high, root->max,level);

    print_inorder(root->right, level + 1);
}

