#include "../include/chargeMonde.h"

GLint my_rand (GLint n)
{
  return (GLint)(n*(rand()/(RAND_MAX+1.0)));
}

void chargeMonde()
{
  char ligne[TAILLEMONDEX];
  FILE *fichier;
  GLuint  x, y=0, ch, attribObj;
  GLfloat positionObjX = 0.0, positionObjY = 0.0;
  GLint LM = -1;
  nbObjet = 0, nbMob = 0;
  if((fichier=fopen("monde.txt","r"))==NULL)
    {
      fprintf(stderr,"erreur de chargement du monde\n");
      exit(1);
    }
  //je recupere le monde
  while(LM!=(int)ligneMonde)
    {
      fgets(ligne,TAILLEMONDEX-1,fichier);
      LM++;
    }
  tailleY=0;
  tailleX=0;
  next=0;
  posFinNivX=-50;
  posFinNivY=-50;
  do
    {
      x=strlen(ligne)-1;
      if(tailleX<x)
	tailleX=x;
      x=0;
      while(ligne[x]!='\n' && x<TAILLEMONDEX)
	{
	  if(ligne[x]=='/')
	    {
	      next=1;
	      break;
	    }
	  ch=ligne[x]-'0';
	  if(isdigit(ligne[x]))
	    {
	      //pour les blocks
	      positionObjX+=2.0;
	      monde[y][x].id=ch;
	      monde[y][x].x=positionObjX;
	      monde[y][x].y=positionObjY;
	      monde[y][x].use = 0;
	      monde[y][x].numObjet=-1;
	      //si c'est un block mystere
	      if(ch==2)
		{
		  attribObj=my_rand(101);
		  if(attribObj>10)
		    {
		      monde[y][x].obj = 0;
		      monde[y][x].numObjet=-1;
		    }
		  else
		    {
		      monde[y][x].numObjet=nbObjet;
		      monde[y][x].obj = 1;
		      nbObjet++;
		    }
		}
	      //pour le point d'apparition
	      if(ch==3)
		{
		  monde[y][x].id=ch;
		  monde[y][x].x=positionObjX;
		  monde[y][x].y=positionObjY;
		  monde[y][x].use = 0;
		  monde[y][x].obj = 0;
		  monde[y][x].numObjet=-1;
		  camy=positionObjY-2;
		  camx=positionObjX;
		}
	      //pour les monstres
	      if(ch==5)
		{
		  monde[y][x].id=ch;
		  monde[y][x].x=positionObjX;
		  monde[y][x].y=positionObjY;
		  monde[y][x].use = 0;
		  monde[y][x].obj = 0;
		  monde[y][x].numObjet=nbMob;
		  nbMob++;
		}
	      //pour la fin du niveau
	      if(ch==6)
		{
		  monde[y][x].id=ch;
		  monde[y][x].x=positionObjX;
		  monde[y][x].y=positionObjY;
		  monde[y][x].use = 0;
		  monde[y][x].obj = 0;
		  monde[y][x].numObjet=-1;
		  posFinNivX=positionObjX;
		  posFinNivY=positionObjY;
		}
	    }
	  else
	    {
	      //pour le vide
	      monde[y][x].id=0;
	      monde[y][x].x=0;
	      monde[y][x].y=0;
	      monde[y][x].use = 0;
	      monde[y][x].obj = 0;
	      monde[y][x].numObjet=-1;
	      positionObjX+=2.0;
	    }
	  x++;
	}
      y++;
      ligneMonde++;
      positionObjY-=2.0;
      positionObjX=0.0;
    }while(fgets(ligne,TAILLEMONDEX-1,fichier) && !next);
  tailleY=y;
  objet = calloc(nbObjet,sizeof*objet);//allocation du tableau d'objet
  mob = calloc(nbMob, sizeof*mob); //allocation du tableau de monstre
  //initialisation des objets
  for(y=0;y<tailleY;y++)
    for(x=0;x<tailleX;x++)
      if(monde[y][x].id==2 && monde[y][x].numObjet!=-1 )
  	{
  	  objet[monde[y][x].numObjet].x=0.0;
  	  objet[monde[y][x].numObjet].y=2.0;
  	  objet[monde[y][x].numObjet].use=0;
  	  objet[monde[y][x].numObjet].obj=0;
  	  objet[monde[y][x].numObjet].id=0;
  	  objet[monde[y][x].numObjet].xd=monde[y][x].x;
  	  objet[monde[y][x].numObjet].yd=monde[y][x].y;
  	}
  /* //initialisation des monstres */
  for(y=0;y<tailleY;y++)
    for(x=0;x<tailleX;x++)
      if(monde[y][x].id==5)
  	{
  	  mob[monde[y][x].numObjet].x=0.0;
  	  mob[monde[y][x].numObjet].y=0.0;
  	  mob[monde[y][x].numObjet].use=0;
  	  mob[monde[y][x].numObjet].obj=0;
  	  mob[monde[y][x].numObjet].id=1;
  	  mob[monde[y][x].numObjet].xd=monde[y][x].x;
  	  mob[monde[y][x].numObjet].yd=monde[y][x].y;
  	}
  fclose(fichier);
}

void rechargeMonde ()
{
  GLuint x,y;
  for(y=0;y<tailleY;y++)
    for(x=0;x<tailleX;x++)
      {
	monde[y][x].use=0;
	if(monde[y][x].id==2 && monde[y][x].numObjet!=-1)
	  {
	    objet[monde[y][x].numObjet].x=0.0;
	    objet[monde[y][x].numObjet].y=2.0;
	    objet[monde[y][x].numObjet].use=0;
	    objet[monde[y][x].numObjet].obj=0;
	    objet[monde[y][x].numObjet].id=0;
	    objet[monde[y][x].numObjet].xd=monde[y][x].x;
	    objet[monde[y][x].numObjet].yd=monde[y][x].y;
	  }

	if(monde[y][x].id==3)
	  {
	    camx=monde[y][x].x;
	    camy=monde[y][x].y-2;
	  }

	if(monde[y][x].id==5)
	  {
	    mob[monde[y][x].numObjet].x=0.0;
	    mob[monde[y][x].numObjet].y=0.0;
	    mob[monde[y][x].numObjet].use=0;
	    mob[monde[y][x].numObjet].obj=0;
	    mob[monde[y][x].numObjet].id=1;
	    mob[monde[y][x].numObjet].xd=monde[y][x].x;
	    mob[monde[y][x].numObjet].yd=monde[y][x].y;
	  }
      }
}

void reinitMonde ()
{
  GLuint x,y;
  for(y=0;y<tailleY;y++)
    for(x=0;x<tailleX;x++)
      {
	if(monde[y][x].id==2 && monde[y][x].numObjet!=-1)
	  {
	    objet[monde[y][x].numObjet].x=0.0;
	    objet[monde[y][x].numObjet].y=2.0;
	    objet[monde[y][x].numObjet].use=0;
	    objet[monde[y][x].numObjet].obj=0;
	    objet[monde[y][x].numObjet].id=0;
	    objet[monde[y][x].numObjet].xd=0;
	    objet[monde[y][x].numObjet].yd=0;
	  }
	if(monde[y][x].id==5)
	  {
	    mob[monde[y][x].numObjet].x=0.0;
	    mob[monde[y][x].numObjet].y=0.0;
	    mob[monde[y][x].numObjet].use=0;
	    mob[monde[y][x].numObjet].obj=0;
	    mob[monde[y][x].numObjet].id=1;
	    mob[monde[y][x].numObjet].xd=0;
	    mob[monde[y][x].numObjet].yd=0;
	  }
	monde[y][x].id=0;
	monde[y][x].x=0;
	monde[y][x].y=0;
	monde[y][x].use = 0;
	monde[y][x].obj = 0;
	monde[y][x].numObjet=-1;
      }
}
