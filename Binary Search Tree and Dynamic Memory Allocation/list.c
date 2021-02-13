#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "memory.h"

// Input: 	void
// Effect:	return a null pointer to a dynamically allocated and 
//		initialized List
List list_ini(void) {
	List_node *head= (List_node *) simu_malloc( sizeof(List_node) ); 
	head->next = NULL;
	return head;
}

// Input:	'list': a List
//		'key': a Key
// Effect:	if key is in list, then return the address of 
//		key's associated data. If key is not in list, 
//		then return NULL
Data *list_search(List list, Key key) {
	// get the first value in list
	List_node *current = list->next;
	int *result;
	// iterate through the list and compare each node's key 
	// to the input key. If a match is found, then return
	// the address of the key in the list, otherwise return NULL
	while (current != NULL) { 
		if (current->key == key){
			result = &(current->data);
			return result;
		}
		current = current->next;
	}
	return NULL;
}

// Input:	'list': a List
//		'key': a Key
//		'data': a Data
// Effect:	add key with data into the front of list
//		if key is in list already, then do nothing
void list_add(List list, Key key, Data data) {
	// check to see if the key is in list
	// if it is not, then check == NULL
	// if it is, the check != NULL and no code is executed
	Data *check = list_search(list, key);
	if(check == NULL) {
		List_node *newNode = (List_node *) simu_malloc(sizeof(List_node));
		// if newNode == NULL, then that means there is not enough 
		//memory as determined by simu_malloc
		if (newNode == NULL)
			return;
		//otherwise, add key and data to list
		else {
			newNode->key = key;
			newNode->data = data;
			newNode->next = list->next;
			list->next = newNode;
		}
	}
}

// Input:	'list': a list
//		'key': a key
// Effect:	delete the node in list with its key equal to the 
//		input key. If no such node is in the list, do nothing

void list_delete(List list, Key key) {
	//check if the key is in the list
	//if not, then print prompt and return
	Data *check = list_search(list, key);
	if(check == NULL) {
		printf("key not found in List");
		return;
	}
	// otherwise remove the node and set pointers accordingly
	else {
		List_node *current = list->next;
		List_node *previous = list;
		while (current->key != key) {
			previous = current; 
			current = current->next;
		}
		previous->next = current->next;
		simu_free(current);		
	}
}

// Input:	'list': a list
// Effect:	linearly traverse the list and print each node's 
//		key and data

void list_print(List list) {
	List_node *current = list->next;
	while(current != NULL) {
		print_list_node(current);
		current = current->next;
	}
}

// Input:	'list': a list
// Effect:	free all the dynamically allocated memory of list

void list_free(List list) {
	List_node *current = list;
	List_node *nextNode = current;
	while (current != NULL) {
		nextNode = nextNode->next;
		simu_free(current);
		current = nextNode;
	}
}
