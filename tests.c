#include <stdlib.h>
#include <stdio.h>
#include "range_tree.h"

int main(){

    addr_arithmetic();
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

    tree_node* x_node = new_tree_node(xi);
    tree_node* y_node = new_tree_node(yi);
    tree_node* z_node = new_tree_node(zi);
    tree_node* w_node = new_tree_node(wi);

    printf("x's low: %p, x's high: %p\n", x_node->i->low, x_node->i->high);


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
