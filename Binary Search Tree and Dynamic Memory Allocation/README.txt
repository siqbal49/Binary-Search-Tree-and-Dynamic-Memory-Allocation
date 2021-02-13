Use makefile command 'make' to compile. Use 'make clean' and then 'make' to recompile if needed. Use ./mymemory to run program after compiling. 

This program  prompts the user for an integer that determines the amount of memory that is allocated for the list.
the list will hold integers that are input by the user. Once the list is at max capacity, then any input by the user will prompt an error message.
On exit, the program displays a table of each integer and their amount of occurences in the list. 

main.c:
Initializes all relevant data structures. Prompts and checks for correct user input. Frees memory at the end of program run time. 

bst.c:
Implementation of binary search tree. Used in memory.c

memory.c:
Handles the memory allocation and deallocation of the binary search tree, which is dynamically created on runtime with the size determined by the user.

datatype.c:
Implementation of the data types used in the program. There are 2, one for the nodes of the binary search tree, and one for the entries of the list.

list.c:
Implementation of list data structure, which holds datatype objects. The list is populated with the users' integer inputs. 