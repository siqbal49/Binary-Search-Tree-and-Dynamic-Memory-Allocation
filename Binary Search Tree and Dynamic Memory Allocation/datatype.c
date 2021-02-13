﻿#include <stdio.h>
#include <stdlib.h>
#include "datatype.h"

// Input:	’key1’ and ’key2’ are two Keys
// Output: if return value < 0, then key1 < key2,
// 		if return value = 0, then key1 = key2,
//		if return value > 0, then key1 > key2,
int key_comp(Key key1, Key key2) {
	int result = key1-key2;
	return result;
}

// Input:	’data1’ and ’data2’ are two Data
// Output: if return value < 0, then data1 < data2,
// 		if return value = 0, then data1 = data2,
//		if return value > 0, then data1 > data2,
int data_comp(Data data1, Data data2) {
	int result = data1-data2;
	return result;
}

//	Input: ’key’: a Key
//	Effect: key is printed
void key_print(Key key) {
	printf("%-15i", key);
}

//	Input: ’data’: a Data
//	Effect: data is printed
void data_print(Data data) {
	printf("%5i\n", data);
}

//	Input: ’node’: a Node
//	Effect: node.key is printed and then the node.data is printed
void print_node(Node node) {
	key_print(node.key);
	data_print(node.data);
}

//	Input: ’node’: a pointer to List_node
//	Effect: node->key is printed and then the node->data is printed
void print_list_node(List_node *node) {
	key_print(node->key);
	data_print(node->data);
}
