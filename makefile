all: 
	gcc ./sources/criptografia.c ./headers/criptografia.h ./main.c -o exec
	./exec

clean:
	rm -rf *.o ./exec
	clear
