/* CS261- HW1 - Program1.c*/
/* Name: Jiayun Yan
 * Date: 1/20/2020
 * Solution description:passing x and y by reference, and passing z by value. Compare the return value as z.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
	(*a)++;
	(*b)--;
	c = (*a) - (*b);		
	return c; 
}

int main(){
	srand(time(0));
    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
	int x,y,z,a;
	x = rand()%11;
	y = rand()%11;
	z = rand()%11;
    /* Print the values of x, y and z */
	printf("x = %d, y = %d, z = %d\n", x, y, z);
    /* Call foo() appropriately, passing x,y,z as parameters */
	a = foo(&x,&y,z);
    /* Print the values of x, y and z */ 
	printf("x = %d, y = %d, z = %d\n", x, y, z);
    /* Print the value returned by foo */
	printf("The value returned by foo is %d\n", a);
    /* Is the return value different than the value of z?  Why? */
	if(z != a){
		printf("The return value different than the value of z, becasue the z is passing by value, and call the function will not change the value of z; however, the return value is c, so it will be the value a - b. \n");
	}
	else{
		printf("The return value is the same as the valuse z, but that is just coincidence!");
	}
    return 0;
}
    
    
