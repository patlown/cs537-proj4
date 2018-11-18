#include <stdlib.h>
#include <stdio.h>

int main(){

    size_t int_size = sizeof(int);
    void* pointer = malloc(sizeof(int));

    printf("Integers are of size:%zu\n",int_size);	    
    printf("This integers address is:%p\n",(void*)pointer);
    
    void* pointer2 = ((char*)pointer) + int_size;
    
    printf("After adding the size of int to x, x is now pointing to:%p\n",(void*)pointer2);
	
    if(pointer2 > pointer){
	printf("works");
    }    
    return 1;

    
}
