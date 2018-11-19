#include <stdlib.h>
#include <stdio.h>
#include "range_tree.h"

void basic_tree_test();

int main(){

    //addr_arithmetic();
    basic_tree_test();
    return 1;

    
}

void basic_tree_test(){
    int* x = malloc(sizeof(int));
    int* y = malloc(sizeof(int));
    int* z = malloc(sizeof(int));
    int* w = malloc(sizeof(int));


    interval* xi = new_interval((void*)x,sizeof(int));
    interval* yi = new_interval((void*)y,sizeof(int));
    interval* zi = new_interval((void*)z,sizeof(int));
    interval* wi = new_interval((void*)w,sizeof(int));

    // tree_node* x_node = new_tree_node(xi);
    // tree_node* y_node = new_tree_node(yi);
    // tree_node* z_node = new_tree_node(zi);
    // tree_node* w_node = new_tree_node(wi);

    //printf("x's low: %p, x's high: %p\n", x_node->i->low, x_node->i->high);
    tree_node* root = NULL;
    
    
    root = insert_node(root,xi);
    //printf("root's low: %p, root's high: %p, root's max: %p\n",root->i->low, root->i->high,root->max);
    root = insert_node(root,yi);
    //printf("root's low: %p, root's high: %p, root's max: %p\n",root->i->low, root->i->high,root->max);
    root = insert_node(root,zi);
    root = insert_node(root,wi);

    print_inorder(root);


}


void addr_arithmetic(){
    size_t int_size = sizeof(int);
    void* pointer = malloc(sizeof(int));

    printf("Integers are of size:%zu\n",int_size);	    
    printf("New integer pointer address is:%p\n",(void*)pointer);
    
    void* pointer2 = ((char*)pointer) + int_size;
    
    printf("After adding the size of int to pointer, pointer2 is now pointing to:%p\n",(void*)pointer2);
	
    if(pointer2 > pointer){
	printf("pointer2 is greater/higher than pointer");
    }    
}
