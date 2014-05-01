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
      haut = 0;
    }
  scamy=camy;
  if((haut || sautF) && camy < hauteur + 10 && camy<0 && !collHaut)
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

int scene0()
{
  static int i = 0;
  static int ok = 0;
  static int terminer = 0;
  if(i<90 && !ok)
    {
      droite=1;
      i++;
    }
  else if(i>=90 && !ok)
    {
      droite=0;
      ok=1;
      i=0;
    }
  if(i==60 && !ok)
    haut=1;
  if(i==80 && !ok)
    haut=0;
  if(i<=81 && ok)
    {
      gauche=1;
      if(i==2)
	haut=1;
      if(i==20)
	haut=0;
      i++;
    }
  else if(i>=81 && ok)
    {
      gauche=0;
      terminer=1;
    }
  deplaceJoueur();
  deplaceMob();
  deplaceObjet();
  return terminer;
}

int scene1()
{
  static int i = 0;
  static int terminer = 1;
  if(i<120)
    {
      droite=1;
      i++;
    }
  else
    {
      droite=0;
      terminer=2;
    }
  deplaceJoueur();
  deplaceMob();
  deplaceObjet();
  return terminer;
}

int scene2()
{
  static int i = 0;
  static int terminer = 2;
  if(i<27)
    i++;
  if(i<40 && i>=27)
    {
      monde[6][4].y-=0.5;
      i++;
    }
  if(i>=40 && i<117)
    {
      droite=1;
      if(i<80)
	monde[6][4].x+=0.5;
      if(i>50 && i<60)
	{
	  monde[6][15].y-=0.5;
	  monde[6][14].y+=1.;
	  monde[6][16].y-=0.3;
	  monde[6][17].y-=0.1;
	}
      if(i==80)
	haut=1;
      if(i==85)
	haut=0;
      if(i==87)
	haut=1;
      if(i==96)
	haut=0;
      if(i==99)
	haut=1;
      if(i==106)
	haut=0;
      i++;
    }
  if(i==117)
    {
      terminer = 3;
      droite=0;
    }
  deplaceJoueur();
  deplaceMob();
  deplaceObjet();
  return terminer;
}
