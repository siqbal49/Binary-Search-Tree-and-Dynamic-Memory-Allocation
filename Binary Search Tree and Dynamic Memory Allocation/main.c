#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datatype.h"
#include "bst.h"
#include "memory.h"
#include "list.h"

int main(void) {
	List list;
	// picked arbritrary size of input to be 15
	char inputSize[15], inputInt[15];
	int incorrect, length, inputInteger;
	Data *data;

	unsigned int size = 0;
	
	// boolean variable, if 0, then the input is valid
	// if 1, then the input is incorrect
	incorrect = 0;
	
	//prompt user and read in the size of the dynamic memory 
	//allocation and deallocation system
	printf("Enter size for the dynamic memory allocation and deallocation system. (mimimum size is 20): ");
	fgets(inputSize, sizeof(inputSize), stdin);

	//check for all non-positive integer inputs and 
	//prompt appropriate message
	length = strlen(inputSize);
	for (int i = 0; i < length-1; i++){
		//comparing to ASCII decimal values 
		//ASCII values 48-57 are positive integers 0-9
		if (inputSize[i] < 48 || inputSize[i] > 57)
			incorrect = 1;
	}
	
	if(incorrect == 1) {
		printf("Error: A non-positive integer value was inputted\n");
		return 0;
	}
	// check if the size is big enough to initialize the list
	// need atleast 20 bytes
	size = atoi(inputSize);
	if (size < 20) {
		printf("Error: need to input a size of atleast 20\n");
		return 0;
	}
	//initialize linked list
	mem_ini(size);
	list = list_ini();
	//read integers from stdin and calculate the occurences of each 
	//integer read using the linked list created
	printf("Enter an integer. Press E to exit\n");
	while (fgets(inputInt, sizeof(inputInt), stdin)) {
		// checks for exit input. Case insensitive.
		if (inputInt[0] == 'e' || inputInt[0] == 'E')
			break;
		
		//check for invalid input. Same as before
		length = strlen(inputInt);
		for (int i = 0; i < length-1; i++) {
			if (inputInt[i] < 48 || inputInt[i] > 57)
				incorrect = 1;
		}
		if (incorrect == 1) {
			printf("Error: A non-positive integer value was inputted\n");
			break;
		}
		inputInteger = atoi(inputInt);
		
		//check to see if the integer is already in the linked list
		//if it is, then add to the occurance, otherwise, add the 
		//integer to the list and set occurance to 1. 
		data = list_search(list, inputInteger);
		if (data == NULL) 
			list_add(list, inputInteger, 1);
		else 
			(*data) += 1;
		printf("Enter an integer. Press E to exit\n");
	} 

	// print key and data in the list
	printf("Integer        Occurences \n");
	list_print(list);

	//free memory
	list_free(list);
	mem_free();
	return 0;
}
