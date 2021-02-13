#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

static unsigned char *memory;
static BStree bst;

// Input:	'size': size of the memory
// Effect:	initialize an unsigned char array of size 
//		elements and intialize a binary search tree 
void mem_ini(unsigned int size) {
	memory = (unsigned char *) malloc(size);
	bst = bstree_ini(size/5); // size/5 is large enough
	bstree_insert(bst, 0, size);
}

// Input:	'size': size of the memory
// Effect:	allocate size bytes and return a pointer to the first byte
//		allocated
void *simu_malloc(unsigned int size) {
	void *p;
	int *keyPointer, *dataSize, memIndex;

	// find a block of memory large enough for size bytes
	keyPointer = bstree_data_search(bst, size+4);
	
	//means no memory block is large enough 
	if (keyPointer == NULL){
		printf("No memory blocks large enough\n");
		return NULL;
	}
	
	// get the size of the data for the block of memory 
	// large enough for size bytes
	dataSize = bstree_search(bst, *keyPointer);
	
	// remove the block in the bst and save the key pointer as an index
	bstree_delete(bst, *keyPointer);
	memIndex = *keyPointer;
	bstree_insert(bst, *keyPointer+size+4, (*dataSize)-size-4);
	
	//store the size 
	memory[memIndex] = size;
	//get pointer to the first byte allocatd 
	p = &memory[memIndex + 4];
	return p;
}

// Input:	'ptr': a pointer
// Effect:	put allocated memory pointed at by ptr back 
//		to be free memory
void simu_free(void *ptr) {
	unsigned int size;
	int key, *combine;
	Key **pre, **suc;

	if (ptr == NULL)
		return;
	// get the size value stored at ptr - 4 bytes
	size = *(unsigned int*)(ptr - 4);
	key = (unsigned char *) ptr- 4 - memory;
	
	//find the predecessor and successor to the key
	pre = malloc(sizeof(*pre));
	suc = malloc(sizeof(*suc));
	bstree_pre_suc(bst, key, pre, suc);
	
	// if a successor exists in bst and it is directly after 
	// the memory at key, then combine both nodes
	if (*suc != NULL && **suc == key+4+(int) size){
		combine = bstree_search(bst, **suc);
		size += *((unsigned int*) combine);
		bstree_delete(bst, **suc);
	}
	// same as earlier but for predecessor
	if (*pre !=NULL) {
		combine = bstree_search(bst, **pre);
		if (*combine + **pre == key) {
			bstree_delete(bst, **pre);
			size += *((unsigned int*) combine);
			key = **pre;
		}
	}
	free(pre);
	free(suc);
	
	// put back into free memory
	bstree_insert(bst, key, size+4);
}

// Input:	void
// Effect:	print all the free memory blocks
void mem_print(void) {
	bstree_traversal(bst);
}

// Input:	void
// Effect:	free memory used for the array and the binary search tree
void mem_free(void) {
	free(memory);
	bstree_free(bst);
}
