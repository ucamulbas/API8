CC=gcc
FLAGS= -g -lglut -lGL -lGLU -Wall -lm
SRC= source/main.c source/LoadBMP.c source/clavier.c source/collision.c source/affichage.c source/chargeMonde.c source/deplacement.c source/scene.c
OBJ=$(SRC:%.c=objet/%.o)

Mario:	$(OBJ)
		$(CC) $^ -o $@ $(FLAGS)

objet/%.o:	%.c
	$(CC) -c -o $@ $^ $(FLAGS)

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f *#
	rm -f Mario
