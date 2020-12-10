/* CS261- HW1 - Program2.c*/
/* Name:Jiayun Yan
 * Date:01/20/2020
 * Solution description: generate random scores and initials to student stuct, and then count the average, min and max score.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

struct student{
	char initials[2];
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student *s = (struct student *) malloc(10*sizeof (struct student));
     /*return the pointer*/
	return s;
}

void generate(struct student* students){
     /*Generate random initials and scores for ten students.
	The two initial letters must be capital and must be between A and Z. 
	The scores must be between 0 and 100*/
	int i;
	for(i=0; i<10; i++){
		char c1 = rand()%26 +'A';
		char c2 = rand()%26 +'A';
		(students+i)->initials[0] = c1;
		(students+i)->initials[1] = c2;
		(students+i)->score = rand()%101;
	}    
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              1. Initials  Score
              2. Initials  Score
              ...
              10. Initials Score*/
	int i;
	for(i=0; i<10; i++){
		printf("Initials: %c%c, score: %d\n", (students+i)->initials[0], (students+i)->initials[1], (students+i)->score);
	}	
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int min = 100;
	int max = 0;
	int total = 0;
	int i;
	float average = 0.00;
	for(i=0; i<10; i++){
		if((students+i)->score < min){
			min = (students+i)->score;
		}
		if((students+i)->score > max){
			max = (students+i)->score;
		}
		total += (students+i)->score;
	}
	average = total/10.00;
	printf("Minimum score:%d\nMaximun score:%d\nAverage score:%f\n", min, max, average);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	if (stud !=0){
		free (stud);
		stud = 0;
	}
}

int main(){
	srand(time(0));
	struct student* stud = NULL;
    
    /*call allocate*/
	stud = allocate();
    /*call generate*/
	generate(stud);
    /*call output*/
	output(stud);
    /*call summary*/
	summary(stud);
    /*call deallocate*/
	deallocate(stud);
    return 0;
}
