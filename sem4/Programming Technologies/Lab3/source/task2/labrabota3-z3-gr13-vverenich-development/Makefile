# Makefile for task3

bin/product: build/main.o build/product.o
    gcc -o build/product build/main.o build/product.o
    
build/main.o: src/main.c
    gcc -c src/main.c -build/main.o
    
build/product.o: src/product.c
    gcc -c src/product.c -o build/product.o
    
clean:
    rm -f build/*.o bin/product
