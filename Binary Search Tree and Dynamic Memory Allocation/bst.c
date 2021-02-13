#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

//	Input: ’size’: size of an array
//	Output: a pointer of type BStree,
//				i.e. a pointer to an allocated memory of BStree_struct type
//	Effect: dynamically allocate memory of type BStree_struct
//			allocate memory for a Node array of size+1 for member tree_nodes
//			allocate memory for an unsigned int array of size+1 for member is_free
//			set entry i of is_free to i
//			set member size to ’size’
//			set member top to 1 
//			set member root to 0 
BStree bstree_ini(int size) {
	BStree bst;
	int i;

	bst = (BStree) malloc( sizeof(BStree_struct) );
	bst->tree_nodes = (Node *) malloc( (size+1)*sizeof(Node) );
	bst->free_nodes = (unsigned int *) malloc( (size+1)*sizeof(unsigned int) );
	bst->size = size;
	for (i=0; i<=size; i++) {
		bst->free_nodes[i] = i;
	}
	bst->top = 1;
	bst->root = 0;
	return bst;
}

//	Input: ’bst’: a binary search tree
//					’key’: a Key
//					’data’: a Data
//	Effect: get a free tree_nodes index from free_nodes[top]
//	        ’key’ with ’data’ is assigned into the free tree_nodes
//					left and right are assigned to 0
static int new_node(BStree bst, Key key, Data data) {
	int index;
	if (bst->top > bst->size) {
		return 0;
	}
	index = bst->free_nodes[bst->top];
	bst->top++;
	bst->tree_nodes[index].key = key;
	bst->tree_nodes[index].data = data;
	bst->tree_nodes[index].left = 0;
	bst->tree_nodes[index].right = 0;
	return index;
}

//	Input: ’bst’: a binary search tree
//					’key’:  a Key
//					’data’: a Data
//					'index': pointer to current tree node index
//	Effect: ’key’ with ’data’ is inserted into ’bst’
//					if ’key’ is already in ’bst’, do nothing
static void bst_insert(BStree bst, int *index, Key key, Data data) {
	if (*index == 0 ) {
		*index = new_node(bst, key, data);
		return;
	}
	else {
		int i=*index;
		int comp = key_comp( bst->tree_nodes[i].key, key );
		if ( comp < 0 ) {
			bst_insert(bst, &bst->tree_nodes[i].right, key, data);
		}
		else if ( comp > 0 ) {
			bst_insert(bst, &bst->tree_nodes[i].left, key, data);
		}
		else
			return;
	}
}

//	Input: ’bst’: a binary search tree
//					’key’:  a Key
//					’data’: a Data
//	Effect: ’key’ with ’data’ is inserted into ’bst’
//					if ’key’ is already in ’bst’, do nothing
void bstree_insert(BStree bst, Key key, Data data) {
	bst_insert(bst, &bst->root, key, data);
}

//	Input: ’bst’: a binary search tree
//					’key’:  a Key
//					'index': pointer to current tree node index
//	Effect: delete the tree node who's key is ’key’ from ’bst’
//					if ’key’ is not ’bst’, do nothing
static void bst_delete(BStree bst, int *index, Key key) {
	int ind = *index;
  if (ind == 0) {
    return;
  }
  int comp = key_comp(key, bst->tree_nodes[ind].key);
  if ( comp < 0 )
    bst_delete(bst, &bst->tree_nodes[ind].left, key);
  else if ( comp > 0 )
    bst_delete(bst, &bst->tree_nodes[ind].right, key);
  else { //comp==0
    if (bst->tree_nodes[ind].left == 0) {
      *index = bst->tree_nodes[ind].right;
    }
    else if (bst->tree_nodes[ind].right == 0) {
      *index = bst->tree_nodes[ind].left;
    }
    else {
      int *index1=&bst->tree_nodes[ind].right;
			int ind1 = *index1;
			while ( bst->tree_nodes[ind1].left != 0 ) {
        index1 = &bst->tree_nodes[ind1].left;
        ind1 = *index1;
      }
			*index1 = bst->tree_nodes[ind1].right;
      *index = ind1;
      bst->tree_nodes[ind1].left = bst->tree_nodes[ind].left;
      bst->tree_nodes[ind1].right = bst->tree_nodes[ind].right;
    }
    bst->top--;
		bst->free_nodes[bst->top] = ind;
  }
}

//	Input: ’bst’: a binary search tree
//					’key’:  a Key
//	Effect: delete the tree node who's key is ’key’ from ’bst’
//					if ’key’ is not ’bst’, do nothing
void bstree_delete(BStree bst, Key key) {
	bst_delete(bst, &bst->root, key);
}

// Input: ’bst’: a binary search tree
//        'index': index of current tree node
// Effect: print all the nodes in bst using in order traversal
static void bst_traversal(BStree bst, int index) {
	if ( index == 0 ) {
		return;
	}
	else {
		bst_traversal(bst, bst->tree_nodes[index].left);
		print_node( bst->tree_nodes[index] );
		bst_traversal(bst, bst->tree_nodes[index].right);
	}
}

// Input: ’bst’: a binary search tree
// Effect: print all the nodes in bst using in order traversal
void bstree_traversal(BStree bst) {
  bst_traversal(bst, bst->root);
}

// Input: ’bst’: a binary search tree
// Effect: free all dynamic allocated memory for bst
void bstree_free(BStree bst) {
	free( bst->tree_nodes );
	free( bst->free_nodes );
	free( bst );
}

//	   helper function for bstree_search
// Input: 'bst': a binary search tree
//	  'index': index in the binary search tree
//	  'key': a Key
// Effect: if key is in bst, return the address of key's associated data. 
//	   if key is not in bst, return NULL
//	
static Data *bst_search(BStree bst, int index, Key key) {
	//if index is 0, then the tree is either empty or we have reached a leaf node
	// either way, the key is not in bst
	if (index == 0){
		return NULL;
	}
	else {
		//compare the current indexed key to the input key
		//in the first iteration, the current indexed key is the root of bst
		int comp = key_comp(bst->tree_nodes[index].key, key);
		//if the input key is greater than the indexed key, then go to the right subtree
		if (comp < 0)
			bst_search(bst, bst->tree_nodes[index].right, key);
		//if the input key is less than the indexed key, then go to the left subtree
		else if (comp > 0)
			bst_search(bst, bst->tree_nodes[index].left, key);
		//otherwise, the two keys are equal, so return the address of the data associated with key
		else {
			return &bst->tree_nodes[index].data;
		}

	}
}

// Input: 'bst': a binary search tree
//	  'key': a Key
// Effect: if key is in bst, return the address of key's associated data. 
//	   if key is not in bst, return NULL
Data *bstree_search(BStree bst, Key key) {
	//call helper function with the root as the starting index
	return bst_search(bst, bst->root, key);
}

//	   helper function to implement bstree_data_search
// Input: 'bst': a binary search tree
//	  'index': index in the binary search tree
//	  'key': a Key
// Effect: return the address of the key of the first node in order of keys
//	   in bst, such that the data of the node is greater than or equal 
//	   to data. If no such node exists, then return NULL;
static Key *bst_data_search(BStree bst, int index, Data data) {
	// if index == 0, either the tree is empty or we have reached a leaf node
	// if a leaf node is reached, then a valid node was not found
	if(index == 0)
		return NULL;
	else {
		//do an inorder traversal of the bst to compare the nodes in bst in increasing order
		Key *key;
		key = bst_data_search(bst, bst->tree_nodes[index].left, data);
		if (key != NULL)
			return key;
		//compare the current indexed node to data and if the data
		//is big enough, return the address of the current indexed node's key
		int comp = data_comp(bst->tree_nodes[index].data, data);
		if (comp >= 0)
			return &bst->tree_nodes[index].key;
		key = bst_data_search(bst, bst->tree_nodes[index].right, data);
		if (key!= NULL)
			return key;
		// this occurs when no valid node is found
		return NULL;
		
	}
}

// Input: 'bst': a binary search tree
//	  'key': a Key
// Effect: return the address of the key of the first node in order of keys
//	   in bst, such that the data of the node is greater than or equal 
//	   to data. If no such node exists, then return NULL;
Key *bstree_data_search(BStree bst, Data data) {
	// call helper function with the root being the starting index
	return bst_data_search(bst, bst->root, data);
}

// helper function to implement bstree_pre_suc
// Input: 'bst': a binary search tree
//	  'key': a Key
//	  '**pre': a pointer to a pointer to a key. the predecessor
//	  '**suc': a pointer to a pointer to a key. The successor
//	  'index': an index in the bst
// Effect: sets *pre and *suc to be the predecessor and successor of Key 
//	   respectively. If key does not have a predecessor or successor in 
//         in bst, then set the respective one to be NULL
void bst_pre_suc(BStree bst, Key key, Key **pre, Key **suc, int index) {
	//base case of recursion
	if (index == 0)
		return;
	//recursive case
	else {
		//compare the current node key to the input key
		//if the input key is less than the current node key and the left subtree is not a leaf
		//then check if the current node's key is less than the input successor
		//if it is then the input key < the current node's key < input successor, which 
		//means that the current node's key should be the new successor
		//then recursive call this function with the left subtree as the new index
		int comp = key_comp(bst->tree_nodes[index].key, key);
		if (comp > 0 && bst->tree_nodes[index].left != 0) {
			if (bst->tree_nodes[index].key < **suc && *suc != NULL)
				*suc = &bst->tree_nodes[index].key;
			bst_pre_suc(bst, key, pre, suc, bst->tree_nodes[index].left);
		}
		//compare the current node key to the input key
		//if the input key is greater than the current node key and the right subtree is not a leaf
		//then check if the current node's key is greater than the input predecessor
		//if it is then the input key > the current node's key > input predecessor, which 
		//means that the current node's key should be the new predecessor
		//then recursive call this function with the right subtree as the new index
		else if (comp < 0 && bst->tree_nodes[index].right !=0) {
				if (bst->tree_nodes[index].key > **pre && *pre !=NULL)
					*pre = &bst->tree_nodes[index].key;
				bst_pre_suc(bst, key, pre, suc, bst->tree_nodes[index].right);
		}
		//if the two cases above are false, then check if the left subtree is a leaf
		//and that the input key is less than the current node's key
		//if it is, then that means the current node's key should be the new successor
		else if (comp > 0 && bst->tree_nodes[index].left == 0) {
			if (*suc != NULL) 
				*suc = &bst->tree_nodes[index].key;
		}
		
		//if the 3 cases above are false, then check if the right subtree is a leaf
		//and that the input key is greater than the current node's key
		//if it is, then that means the current node's key should be the new predecessor
		else if (comp < 0 && bst->tree_nodes[index].right == 0){
			if (*pre != NULL)
				*pre = &bst->tree_nodes[index].key;
		}
	}
}

// Input: 'bst': a binary search tree
//	  'key': a Key
//	  '**pre': a pointer to a pointer to a key. the predecessor
//	  '**suc': a pointer to a pointer to a key. The successor
// Effect: sets *pre and *suc to be the predecessor and successor of Key 
//	   respectively. If key does not have a predecessor or successor in 
//         in bst, then set the respective one to be NULL
void bstree_pre_suc(BStree bst, Key key, Key **pre, Key **suc) {
	int index = bst->root;
	//if the tree is empty then return nothing
	if (index == 0)
		return;
	else {
		//find the minimum and maximum values to determine if there is a predecessor and successor 
		//for key in bst
		Key min, max;
		//get the minimum key value in bst
		while (bst->tree_nodes[index].left != 0) 
			index = bst->tree_nodes[index].left;
		min = bst->tree_nodes[index].key;
		//get the maximum key value in bst
		index = bst->root;
		while (bst->tree_nodes[index].right != 0)
			index = bst->tree_nodes[index].right;
		max = bst->tree_nodes[index].key;
		index = bst->root;
		//if the input key is less than the minimum, then the key has no predecessor
		//otherwise set the root as the predecessor
		if (key < min)
			*pre = NULL;
		else 
			*pre = &bst->tree_nodes[index].key;
		//if the input key is greater than the maximum, then the key has no successor
		//otherwise set the root as the successor
		if (key > max)
			*suc = NULL;
		else 
			*suc = &bst->tree_nodes[index].key;
		//call helper function which finds the actual predecessor and successor
		return bst_pre_suc(bst, key, pre, suc, index);
	}
}
