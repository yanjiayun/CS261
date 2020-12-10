/* CS261- HW1 - Program4.c*/
/* Name:Jiayun Yan
 * Date:01/20/2020
 * Solution description:generate the student srtuct, and then sorting students initials.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student{
	char initials[2];
	int score;
};

void sort(struct student* students, int n){
     /*Sort n students based on their initials*/  
	struct student temp;
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-i-1;j++){
			if(((students+j)->initials[0]>(students+(j+1))->initials[0]) || (((students+j)->initials[0] == (students+(j+1))->initials[0])&&((students+j)->initials[1]>(students+(j+1))->initials[1]))){
				temp = *(students+j);
				*(students+j) = *(students+(j+1));
				*(students+(j+1)) = temp;
			}
		}
	}
}

int main(){
	srand(time(0));
    /*Declare an integer n and assign it a value.*/
	int n = 10;
	if (n == 0){
		n = 10;
	}	
    /*Allocate memory for n students using malloc.*/
	struct student *students = (struct student*)malloc(n*sizeof (struct student));
    /*Generate random IDs and scores for the n students, using rand().*/
	int i;
	for(i=0; i<n; i++){
		char c1 = rand()%26 + 'A';
		char c2 = rand()%26 + 'A';
		(students+i)->score = rand()%101;
		(students+i)->initials[0] = c1;
		(students+i)->initials[1] = c2;
	}
    /*Print the contents of the array of n students.*/
	int a;
	for(a=0; a<n; a++){
		printf("Initials: %c%c, score: %d\n", (students+a)->initials[0], (students+a)->initials[1], (students+a)->score);
	}
    /*Pass this array along with n to the sort() function*/
	sort(students,n);
    /*Print the contents of the array of n students.*/
	int b;
	printf("After sorting: \n");
	for(b=0; b<n; b++){
		printf("Initials: %c%c, score: %d\n", (students+b)->initials[0], (students+b)->initials[1], (students+b)->score);
	}
   return 0;
}
