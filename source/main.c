/*
  Pagny Jérémie
  12311178
  API8
*/

#include "../include/main.h"
#include "../include/clavier.h"
#include "../include/collision.h"
#include "../include/affichage.h"
#include "../include/deplacement.h"
#include "../include/chargeMonde.h"
#include "../include/scene.h"

GLfloat camx = 0.0, camy = 0.0, scamy, hauteur, tailleJoueur = 1.0, posFinNivX, posFinNivY; // position de la camera, variable pour le saut , taille du joueur et position de la fin du niveau
//GLfloat departX, departY; //position d'apparition du joueur
GLuint id[6], idTexture[11], beau = 0; //les differents id pour VBO et texture
GLuint tailleX = 0, tailleY = 0; //taille reel du monde
GLuint nbObjet, nbMob, invincible = 0, sautF = 0;  //variable pour le nombre d'objet, de monstre , d'invincibilite et de saut force
GLuint droite = 0, haut = 0, gauche = 0, vue = 0, collHaut = 0, collBas = 0, collDroite = 0, collGauche = 0, droiteO = 0, gaucheO = 0; //Variable booleenne de deplacement
terrain monde[TAILLEMONDEY][TAILLEMONDEX], *objet, *mob;// declaration du monde , d'un tableau d'objet et d'un tableau de monstre
GLuint ligneMonde = 0, next = 0;
GLuint suivant = 0, action = 0, transi = 0; //suivant et action sont des variables pour API8, suivant sert pour les scenes et action pour des effets autre genre rotation du monde
GLUquadricObj *quadAtmosphere;
 

void init()
{
  static GLfloat position[]={0.0,1.0,1.0,0.0};
  static GLfloat cBlanc[]={1.0,1.0,1.0,1.0};
  static GLfloat cNoir[]={0.0,0.0,0.0,1.0};
  static GLfloat mat_shininess[]={100.0};//taille du reflet
  glClearColor(0.0,0.0,0.0,0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_BLEND);
  glLightfv(GL_LIGHT0, GL_AMBIENT, cBlanc);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, cBlanc);// active le reflet
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,cNoir);
  glShadeModel(GL_SMOOTH);
  static GLfloat cubeSpe[]={1,-1,1,//devant en bas a droite FACE AVANT
			    1,1,1,//devant en haut a droite
			    -1,1,1,//devant en haut a gauche
			    -1,-1,1,//devant en bas a gauche
			    1,1,1,//devant en haut a droite FACE DROITE
			    1,1,-1,//derriere en haut a droite
			    1,-1,-1,//derriere en bas a droite
			    1,-1,1,//devant en bas a droite
			    -1,-1,1,//devant en bas a gauche FACE GAUCHE
			    -1,1,1,//devant en haut a gauche
			    -1,1,-1,//derriere en haut a gauche
			    -1,-1,-1,//derriere en bas a gauche
			    1,1,-1,//derriere en haut a droite FACE ARRIERE
			    -1,1,-1,//derriere en haut a gauche
			    -1,-1,-1,//derriere en bas a gauche
			    1,-1,-1,//derriere en bas a droite 
			    1,0, //FACE AVANT coordonnes des textures
			    1,1,
			    0,1,
			    0,0,
			    0,1, //FACE DROITE
			    1,1,
			    1,0,
			    0,0,
			    1,0, //FACE GAUCHE
			    1,1,
			    0,1,
			    0,0,
			    0,1, //FACE ARRIERE
			    1,1,
			    1,0,
			    0,0,
			    0,0,1,//La declaration des normales
			    0,0,1,
			    0,0,1,
			    0,0,1,
			    1,0,0,
			    1,0,0,
			    1,0,0,
			    1,0,0,
			    -1,0,0,
			    -1,0,0,
			    -1,0,0,
			    -1,0,0,
			    0,0,-1,
			    0,0,-1,
			    0,0,-1,
			    0,0,-1};

  static GLfloat faceSupBlock[]={1,1,1,//devant en haut a droite FACE SUPERIEUR
				 -1,1,1,//devant en haut a gauche
				 -1,1,-1,//derriere en haut a gauche
				 1,1,-1,//derriere en haut a droite
				 1,0, //FACE SUPERIEUR
				 0,0,
				 0,1,
				 1,1,
				 0,1,0,
				 0,1,0,
				 0,1,0,
				 0,1,0};
  
  static GLfloat faceInfBlock[]={-1,-1,1,//devant en bas a gauche FACE INFERIEUR
				 1,-1,1,//devant en bas a droite
				 1,-1,-1,//derriere en bas a droite
				 -1,-1,-1,//derriere en bas a gauche
				 0,0, //FACE INFERIEUR
				 1,0,
				 1,1,
				 0,1,
				 0,-1,0,
				 0,-1,0,
				 0,-1,0,
				 0,-1,0};
  
  static GLfloat fond[]={2*TAILLEMONDEX,TAILLEMONDEY,-(CAMZ+45),//derriere en haut a droite FACE ARRIERE
			 -2*TAILLEMONDEX,TAILLEMONDEY,-(CAMZ+45),//derriere en haut a gauche
			 -2*TAILLEMONDEX,-TAILLEMONDEY,-(CAMZ+45),//derriere en bas a gauche
			 2*TAILLEMONDEX,-TAILLEMONDEY,-(CAMZ+45),//derriere en bas a droite 
			 5,1, //FACE ARRIERE
			 0,1,
			 0,0,
			 5,0,
			 0.0,0.0,1.0,
			 0.0,0.0,1.0,
			 0.0,0.0,1.0,
			 0.0,0.0,1.0};
  
  static GLfloat sol[]={-2*TAILLEMONDEX,-TAILLEMONDEY,CAMZ+45,//devant en bas a gauche FACE INFERIEUR
			2*TAILLEMONDEX,-TAILLEMONDEY,CAMZ+45,//devant en bas a droite
			2*TAILLEMONDEX,-TAILLEMONDEY,-(CAMZ+45),//derriere en bas a droite
			-2*TAILLEMONDEX,-TAILLEMONDEY,-(CAMZ+45),//derriere en bas a gauche
			1,1, //FACE INFERIEUR
			0,1,
			0,0,
			1,0,
			0,1,0,
			0,1,0,
			0,1,0,
			0,1,0};

  static GLfloat drapeau[]={0,0,0,
			    0,-2,0,
			    5,-1,0};
  
  // je met en VBO mes formes
  glGenBuffers(6, id);
  glBindBuffer(GL_ARRAY_BUFFER, id[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(sol), sol, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, id[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeSpe), cubeSpe, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, id[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fond), fond, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, id[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(faceSupBlock), faceSupBlock, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, id[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(faceInfBlock), faceInfBlock, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, id[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(drapeau), drapeau, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  //je charge ma texture
  texture=malloc(sizeof(texture));
  if (ImageLoad("image/solCote.bmp", texture)==-1) 
    return;
  glGenTextures(11, idTexture);
  glBindTexture(GL_TEXTURE_2D, idTexture[0]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);
  
  if (ImageLoad("image/block.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[1]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);

  if (ImageLoad("image/blockUse.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[2]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);

  if (ImageLoad("image/fond.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[3]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);

  if (ImageLoad("image/chomp.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[4]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);

  if (ImageLoad("image/solFond.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[5]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);

  if (ImageLoad("image/sol.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[6]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);

  if (ImageLoad("image/blockCassable.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[7]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);
  
  if (ImageLoad("image/herbe.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[8]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);
  
  if (ImageLoad("image/Champi.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[9]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);

  if (ImageLoad("image/Gumba.bmp", texture)==-1) 
    return;
  glBindTexture(GL_TEXTURE_2D, idTexture[10]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data); 
  glBindTexture(GL_TEXTURE_2D,0);

  free(texture->data); 
  free(texture);

  quadAtmosphere=gluNewQuadric();
  gluQuadricNormals(quadAtmosphere, GLU_SMOOTH);
  gluQuadricTexture(quadAtmosphere, GL_TRUE);
  
}

void idle()
{
  if((camx<=posFinNivX+1 && camx>=posFinNivX-1) && (camy+3<=posFinNivY+10 && camy+3 >=posFinNivY))
    {
      if(!next)
	{
	  free(objet);
	  free(mob);
	  exit(0);
	}
      else
	transi=1;
      droite=gauche=haut=0;
    }
  if(invincible)
    invincible--;
  if(sautF)
    sautF--;
  //je charge les scenes
  if(!transi)
    switch(suivant)
      {
      case 0:suivant=scene0();
	break;
      case 1:suivant=scene1();
	break;
      case 2:suivant=scene2();
	break;
      case 3: suivant=scene3();
	break;
      }
  glutPostRedisplay();
}

void reshape (int w, int h)
{  
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode (GL_PROJECTION); 
  glLoadIdentity (); 
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.01, 500.0); 
  glMatrixMode(GL_MODELVIEW);  
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv); 
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
  glutInitWindowSize (800, 400); 
  glutInitWindowPosition (0, 0); 
  glutCreateWindow (argv[0]);
  srand(time(0));
  init (); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(clavier);
  glutKeyboardUpFunc(clavierUp);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  chargeMonde();
  glutMainLoop();
  return 0; 
}
