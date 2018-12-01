#include <stdlib.h>
#include <stdio.h>
#include "range_tree.h"

void basic_tree_test();
void test2();


int main(){

    //addr_arithmetic();
    //basic_tree_test();
    //test2();
    malloc_check();
    return 1;

    
}

void malloc_check(){
    tree_node* x = malloc537(sizeof(tree_node));
    assert(x != NULL);

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
    tree_node** root = NULL;
    
    
    // root = insert_node(root,xi);
    // //printf("root's low: %p, root's high: %p, root's max: %p\n",root->i->low, root->i->high,root->max);
    // root = insert_node(root,yi);
    // //printf("root's low: %p, root's high: %p, root's max: %p\n",root->i->low, root->i->high,root->max);
    // root = insert_node(root,zi);
    // root = insert_node(root,wi);
    root= init_root();
    insert_node(root,xi);
    insert_node(root, yi);
    insert_node(root,zi);
    insert_node(root, wi);


    print_inorder(*root,0);
    print_lvlorder(*root);
    void *ptr = (void*)z;
    tree_node *p = search_ptr(root,ptr);
    //printf("%p",p);
    if(p == NULL){
        printf("\ncase 1: ptr:%p doest found\n",ptr);
    }else if(ptr!= p->i->low){
        printf("\ncase 2: ptr:%p\n",ptr);
        print_node(p);
    }else{
        printf("\nfound:\n");
        print_node(p);
        delete_node(root,p);
        print_inorder(*root,0);
        print_lvlorder(*root);
    }
   
    //delete_node(root,p);
    //print_inorder(*root,0);
    //print_lvlorder(*root);
  
    //print_t(*root);

}

void test2(){
    int tsize = 20;
    int **ptrs = malloc(sizeof(*ptrs)*tsize);
    tree_node** root = NULL;
    root= init_root();
    for(int i = 0; i < tsize; i++){
        ptrs[i] = malloc(sizeof(**ptrs));
        interval *temp = new_interval((void*)ptrs[i],sizeof(**ptrs));
        insert_node(root, temp);

    }
    print_inorder(*root,0);
    print_lvl(*root);
    int arr[] = {3,9,2,1,5,8,4,7,6,11,15,18,13};
    for(int i = 0; i<12; i++){
        printf("\n\n-----------------------------%d---------------------------\n\n",i);
        void* p = search_ptr(root,ptrs[arr[i]]);

        printf("\n\n\n\n%p   :     %p\n",p,((tree_node*)p)->i->low);
        delete_node(root,(tree_node*)p);
        print_lvl(*root);
        print_inorder(*root,0);
    }
    //print_inorder(*root,0);
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
