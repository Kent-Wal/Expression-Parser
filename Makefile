CC = clang
CFLAGS = -Wall -std=c99 -pedantic

#compiles all executable files
all: bin/preorder bin/inorder bin/postorder bin/calculate bin/heap

#creates the obj and bin directories if they have not yet been created
directories:			
	mkdir -p obj bin

bin/preorder: directories obj/utils.o obj/preorder.o
	$(CC) obj/utils.o obj/preorder.o -o bin/preorder
	
bin/inorder: directories obj/utils.o obj/inorder.o
	$(CC) obj/utils.o obj/inorder.o -o bin/inorder
	
bin/postorder: directories obj/utils.o obj/postorder.o
	$(CC) obj/utils.o obj/postorder.o -o bin/postorder
	
bin/calculate: directories obj/utils.o obj/calculate.o
	$(CC) obj/utils.o obj/calculate.o -o bin/calculate
bin/heap: directories obj/heap.o
	$(CC) obj/heap.o -o bin/heap

obj/utils.o: src/utils.c src/header.h
	$(CC) $(CFLAGS) -c src/utils.c -o obj/utils.o
obj/preorder.o: src/preorder.c src/header.h
	$(CC) $(CFLAGS) -c src/preorder.c -o obj/preorder.o
obj/postorder.o: src/postorder.c src/header.h
	$(CC) $(CFLAGS) -c src/postorder.c -o obj/postorder.o
obj/inorder.o: src/inorder.c src/header.h
	$(CC) $(CFLAGS) -c src/inorder.c -o obj/inorder.o
obj/calculate.o: src/calculate.c src/header.h
	$(CC) $(CFLAGS) -c src/calculate.c -o obj/calculate.o
obj/heap.o: src/heap.c src/header.h
	$(CC) $(CFLAGS) -c src/heap.c -o obj/heap.o
	
clean:
	rm -f obj/*.o
cleaner:
	rm -f obj/*.o
	rm -f bin/*