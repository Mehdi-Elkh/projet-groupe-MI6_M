all: exec

main.o: main.c piece.h jeu.h score.h
	gcc -c main.c -o main.o

piece.o: piece.c piece.h
	gcc -c piece.c -o piece.o

jeu.o: jeu.c jeu.h
	gcc -c jeu.c -o jeu.o

score.o: score.c score.h
	gcc -c score.c -o score.o

exec: main.o piece.o jeu.o score.o
	gcc main.o piece.o jeu.o score.o -o exec

clean:
	rm -f *.o
	rm -f exec
