/* CS261- HW1 - Program3.c*/
/* Name:Jiayun Yan
 * Date:01/20/2020
 * Solution description:fill a size 20 array with random number, and then sorting them from low to high.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int* number, int n){
     /*Sort the array of integeres of length n*/ 
	int temp,i,j;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-i-1;j++){
			if(*(number+j) > *(number+(j+1))){
				temp = *(number+j);
				*(number+j) = *(number+(j+1));
				*(number+(j+1)) = temp;
			}
		}
	}
}

int main(){
	srand(time(0));
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
	if(n == 0){
		n = 20;
	}
    /*Allocate memory for an array of n integers using malloc.*/
	int *array = (int *)malloc(sizeof(int)*n);
    /*Fill this array with random numbers, using rand().*/
	int i,a;
	for(i=0; i<n; i++){
		*(array +i) = rand();
	}
	printf("\n");
    /*Print the contents of the array.*/
	for(a=0; a<n; a++){
		printf("%d ", *(array+a));
	}
	printf("\n");
    /*Pass this array along with n to the sort() function of part a.*/
   sort(array,n); 
    /*Print the contents of the array.*/
	printf("After sorting: \n");
   int b; 
	for(b=0; b<n; b++){
		printf("%d ", *(array+b));
	}
	printf("\n");
   return 0;
}
