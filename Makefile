all: exec

main.o: main.c fonction.h
  gcc -c main.c -o main.o

piece.o: piece.c fonction.h
  gcc -c piece.c -o piece.o

jeu.o: jeu.c fonction.h
  gcc -c jeu.c -o jeu.o

score.o: score.c fonction.h
  gcc -c score.c -o score.o

exec: main.o piece.o jeu.o score.o
  gcc main.o piece.o jeu.o score.o -o

clean:
  rm -f *.o
  rm exec
