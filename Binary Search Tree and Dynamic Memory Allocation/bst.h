#ifndef Bst_H
#define Bst_H

#include "datatype.h"

typedef struct {
	Node *tree_nodes;
	unsigned int *free_nodes;
	int size, top, root;
} BStree_struct;
typedef BStree_struct* BStree;

BStree bstree_ini(int size);
void bstree_insert(BStree bst, Key key, Data data);
void bstree_traversal(BStree bst);
void bstree_free(BStree bst);
void bstree_delete(BStree bst, Key key);
Data *bstree_search(BStree bst, Key key);
Key *bstree_data_search(BStree bst, Data data);
void bstree_pre_suc(BStree bst, Key key, Key **pre, Key **suc);
//void bstree_traversal_all(BStree bst);
static int new_node(BStree bst, Key key, Data data);
static void bst_insert(BStree bst, int *index, Key key, Data data);
static void bst_delete(BStree bst, int *index, Key key);
static void bst_traversal(BStree bst, int index);
static Data *bst_search(BStree bst, int index, Key key);
static Key *bst_data_search(BStree bst, int index, Data data);
void bst_pre_suc(BStree bst, Key key, Key **pre, Key **suc, int index);
#endif
