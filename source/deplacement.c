#include "../include/deplacement.h"

void deplaceJoueur()
{
  GLint fin = tailleY*2+20;; //determine la profondeur a laquelle on meurt
  if(camy<-fin) //permet de mourir
    {
      tailleJoueur=1.0;
      rechargeMonde();
    }
  collisionJoueur();
  if((scamy == camy) && !collBas)
    {
      camy-=0.5;
      haut=0;
    }
  scamy=camy;
  if((haut || sautF) && !collHaut)
    camy+=.5;
  if(droite && !collDroite)
    camx+=.5;
  if(gauche && !collGauche)
    camx-=.5;
  if(((collDroite==1 && collGauche==1) || (collHaut==1 && collBas==1)) && tailleJoueur==1.5)
    tailleJoueur=1.0;
  else if(collDroite==1 && collGauche==1 && collHaut==1 && collBas==1 && tailleJoueur==1.0)
    exit(0);
  collDroite=collGauche=collHaut=collBas=0;
}

void deplaceObjet()
{
  GLint i;
  GLint fin =  tailleY*2+30;
  for(i=0;i<nbObjet;i++)
    {
      if (objet[i].obj && !objet[i].use)
	{
	  if((objet[i].y+objet[i].yd)<-fin) //permet de ne plus afficher la boule a partir d'une profondeur
	    {
	      objet[i].obj=0;
	      objet[i].use=1;
	      break;
	    }
	  collisionObjetMonstre(objet[i].xd + objet[i].x , objet[i].yd + objet[i].y);
	  if(!collBas)
	    objet[i].y-=0.5;	  
	  if(!objet[i].id && !collDroite)
	    objet[i].x+=.1;
	  else if(!objet[i].id && collDroite)
	    objet[i].id=1;
	  if(objet[i].id && !collGauche)
	    objet[i].x-=.1;
	  else if(objet[i].id && collGauche)
	    objet[i].id=0;
	  collDroite=collGauche=collHaut=collBas=0;
	}
    }
}

void deplaceMob()
{
  GLint i;
  GLint fin =  tailleY*2+30;
  for(i=0;i<nbMob;i++)
    {
      if(sqrt((camx-(mob[i].x+mob[i].xd))*(camx-(mob[i].x+mob[i].xd)) + ((camy+2)-(mob[i].y+mob[i].yd))*((camy+2)-(mob[i].y+mob[i].yd)))<=40)
	mob[i].obj = 1;
      else
	mob[i].obj = 0;
      if(!mob[i].use && mob[i].obj)
	{
	  if((mob[i].y+mob[i].yd)<-fin) //permet de ne plus afficher la boule a partir d'une profondeur
	    {
	      mob[i].obj=0;
	      mob[i].use=1;
	      break;
	    }
	  collisionObjetMonstre(mob[i].xd + mob[i].x , mob[i].yd + mob[i].y);
	  if(!collBas)
	    mob[i].y-=0.5;
	  if(!mob[i].id && !collDroite)
	    mob[i].x+=.1;
	  else if(!mob[i].id && collDroite)
	    mob[i].id=1;
	  if(mob[i].id && !collGauche)
	    mob[i].x-=.1;
	  else if(mob[i].id && collGauche)
	    mob[i].id=0;
	  collDroite=collGauche=collHaut=collBas=0;
	}
    }
}
