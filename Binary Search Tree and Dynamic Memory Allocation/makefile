mymemory: main.o datatype.o bst.o memory.o list.o 
	cc -o mymemory main.o datatype.o bst.o memory.o list.o 
main.o: main.c list.h
	cc -c main.c
datatype.o: datatype.c datatype.h
	cc -c datatype.c
bst.o: bst.c bst.h
	cc -c bst.c
memory.o: memory.c memory.h
	cc -c memory.c
list.o: list.c list.h memory.h
	cc -c list.c
clean:
	rm -f run *.o core