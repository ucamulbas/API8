#ifndef MAIN
#define MAIN
#define  GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "LoadBMP.h"
#define TAILLEMONDEX 500 //taille maximum du monde en longueur
#define TAILLEMONDEY 100 //taille maximum du monde en largeur
#define CAMZ 5.0
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
/*
  Pour les blocks, la structure est:
  -use: si le block est casse ou utilise
  -obj: si le block contient un objet
  -id: quel type de block
  -numObjet: indice de son objet dans le tableau objet

  Pour les objets, la structure est:
  -use: si l'objet a ete prit
  -obj: si l'objet a ete activer
  -id: son deplacement de droite a gauche
  -numObjet: ne sert a rien

  Pour les monstres, la structure est:
  -use: si le monstre est mort
  -obj: si le monstre est visible
  -id: son deplacement de droite a gauche
  -numObjet: ne sert a rien
*/
struct monde{
  GLfloat x,y, xd, yd;//x,y pour les blocks, xd, xy pour les objets et les monstres
  GLint use, obj, id, numObjet;
};
typedef struct monde terrain;


extern GLfloat camx, camy, scamy, hauteur, tailleJoueur, posFinNivX, posFinNivY;
extern GLuint id[5], idTexture[11],beau;
extern GLuint tailleX, tailleY; 
extern GLuint nbObjet, nbMob, invincible, sautF;
extern GLuint droite, haut, gauche, vue, collHaut, collBas, collDroite, collGauche, droiteO, gaucheO;
extern terrain monde[TAILLEMONDEY][TAILLEMONDEX], *objet, *mob;
extern GLuint ligneMonde, next, suivant, action, transi;
extern GLUquadricObj *quadAtmosphere;



void init();
void idle();
void reshape (int w, int h);
#endif

