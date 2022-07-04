# Makefile for task3
 
bin/book: build/main.o build/book.o
    gcc -o build/book build/main.o build/book.o
 
build/main.o: src/main.c
    gcc -c src/main.c -build/main.o
 
build/book.o: src/book.c
    gcc -c src/book.c -o build/book.o
 
clean:
    rm -f build/*.o bin/book
