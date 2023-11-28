all: 
	gcc ./sources/criptografia.c ./headers/criptografia.h ./headers/analise.h ./sources/analise.c ./main.c -o exec
	./exec

clean:
	rm -rf *.o ./exec
	clear
