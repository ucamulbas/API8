#include "../include/clavier.h"

void clavier(unsigned char key, int x, int y)
{
  switch(key)
    {
    case 27: free(objet); free(mob); exit(0); break;
    case 'v': if(vue) vue = 0; else vue = 1; break;
    case 't': if(tailleJoueur==1.5) tailleJoueur=1.0; else tailleJoueur=1.5; break;
    case 'd': droite = 1; break;
    case 'q': gauche = 1; break;
    case 'z':
      collisionJoueur();
      if(collBas)
	{
	  haut = 1;
	  hauteur=camy;
	}
      else
	haut = 0;
      break;
    default: break;
    }
  glutPostRedisplay();
}

void clavierUp(unsigned char key, int x, int y)
{
  switch(key)
    {
    case 'd': droite = 0; break;
    case 'q': gauche = 0; break;
    case 'z': haut = 0; break;
    } 
  glutPostRedisplay();
}
