#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "avl.h"


int FindMinPath(struct AVLTree *tree, TYPE *path);
void printBreadthFirstTree(struct AVLTree *tree);
void _FindMinPath(struct AVLnode *node, TYPE *temp, TYPE * path, int position, int* total, int* count);


/* -----------------------
The main function
  param: argv = pointer to the name (and path) of a file that the program reads for adding elements to the AVL tree
*/
int main(int argc, char** argv) {

	FILE *file;
	int len, i;
	TYPE num; /* value to add to the tree from a file */
	struct timeval stop, start; /* variables for measuring execution time */
	int pathArray[50];  /* static array with values of nodes along the min-cost path of the AVL tree -- as can be seen, the tree cannot have the depth greater than 50 which is fairly sufficient for out purposes*/

	struct AVLTree *tree;
	
	tree = newAVLTree(); /*initialize and return an empty tree */
	
	file = fopen(argv[1], "r"); 	/* filename is passed in argv[1] */
	assert(file != 0);

	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){

		addAVLTree(tree, num);		
	}
	/* Close the file  */
	fclose(file);
	
	printf("\nPrinting the tree breadth-first : \n");
	printBreadthFirstTree(tree);

	gettimeofday(&start, NULL);

	/* Find the minimum-cost path in the AVL tree*/
	len = FindMinPath(tree, pathArray);
	
	gettimeofday(&stop, NULL);

	/* Print out all numbers on the minimum-cost path */
	printf("\nThe minimum-cost path is: \n");
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");

	printf("\nYour execution time to find the mincost path is %f microseconds\n", (double) (stop.tv_usec - start.tv_usec));

        /* Free memory allocated to the tree */
	deleteAVLTree(tree); 
	
	return 0;
}


  
/* --------------------
Finds the minimum-cost path in an AVL tree
   Input arguments: 
        tree = pointer to the tree,
        path = pointer to array that stores values of nodes along the min-cost path, 
   Output: return the min-cost path length 

   pre: assume that
       path is already allocated sufficient memory space 
       tree exists and is not NULL
*/
int FindMinPath(struct AVLTree *tree, TYPE *path)
{
	int count = 0;
	int total = 100000000;
   int temp[50];
	_FindMinPath(tree->root, temp, path, 0, &total, &count);
	
	return count;
}

void _FindMinPath(struct AVLnode *node, TYPE *temp, TYPE * path, int position, int* total, int* count)
{
	int i = 0;
	int sum = 0;
	if(node == NULL){
		return;
	}
	temp[position] = node->val;
	if(node->left == NULL && node->right == NULL){
		sum = 0;
		for(i = 0; i < position; i++){
			sum += abs(temp[i] - temp[i + 1]);
		}
		if(sum < *total){
			for(i = 0; i <= position; i++){
				path[i] = temp[i];
			}
			*total = sum;
			*count = position + 1;
		}
	}
	else{
		if(node->left != NULL){
			_FindMinPath(node->left, temp, path, position + 1, total, count);
		}
		if(node->right != NULL){
			_FindMinPath(node->right, temp, path, position + 1, total, count);
		}
	}
}

/* -----------------------
Printing the contents of an AVL tree in breadth-first fashion
  param: pointer to a tree
  pre: assume that tree was initialized well before calling this function
*/
void printBreadthFirstTree(struct AVLTree *tree)
{
	int index = 0;
	int last = 0;
	int a = tree->cnt;
	struct AVLnode** array = NULL;
	array = (struct AVLnode**)malloc(a*sizeof(struct AVLnode*));
	array[last] = tree->root;
	last++;
	
	while(index < last){
		struct AVLnode* node = array[index];
		index++;
		printf("%d \n", node->val);
		if(node->left != NULL){
			array[last] = node->left;
			last++;
		}
		if(node->right != NULL){
			array[last] = node->right;
			last++;
		}
	}
}



