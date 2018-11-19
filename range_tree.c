#include "range_tree.h"


tree_node* new_tree_node(interval* i){
    
    tree_node* node = malloc(sizeof(tree_node));
    node->i = i;
    node->max = i->high;
    node->left = NULL;
    node->right = NULL;

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

tree_node* insert_node(tree_node *root, interval *i){
    
    if(root == NULL){
	    return new_tree_node(i);;
    }

    void* l = root->i->low;

    /*
        if current node's low is lower than the root's low, add it somewhere in the left subtree
        else, add it somewhere in the right subtree
    */

    if(i->low < l){
        insert_node(root->left,i);
    }else{
        insert_node(root->right,i);
    }

    //update the max value of the node
    if(root->max < i->high){
        root->max = i->high;
    }

    return root;
    

}

void print_inorder(tree_node* root){

    if(root == NULL){
        return;
    }

    print_inorder(root->left);

    printf("The current tree_node has low: %p, high: %p, and max: %p\n", root->i->low, root->i->high, root->max);

    print_inorder(root->right);
}

