#include "../include/collision.h"

void collisionJoueur()
{
  GLuint x,y;
  for(y=0;y<tailleY;y++)
    for(x=0;x<tailleX;x++)
      {
  	if(monde[y][x].id!=3 && monde[y][x].id!=0 && monde[y][x].id!=5 && monde[y][x].id!=6) //est-ce que c'est un block ?
  	  {
	    /*
	      (camy+2+2*tailleJoueur) : haut de la boule
	      (camy+1+tailleJoueur-(tailleJoueur-1)) : bas de la boule
	      (camy+2+tailleJoueur) : milieu de la boule
	    */
	    if(monde[y][x].use==1 && monde[y][x].id==4) //est-il casse ?
	      continue;
	    if(((camy+2+2*tailleJoueur)>=(monde[y][x].y-1) && (camy+2+2*tailleJoueur)<=(monde[y][x].y+1)) &&
	       ((((camx+tailleJoueur)>(monde[y][x].x-1)) && ((camx+tailleJoueur)<(monde[y][x].x+1))) ||
		((camx-tailleJoueur)>(monde[y][x].x-1) && (camx-tailleJoueur)<(monde[y][x].x+1)) ||
		(camx>(monde[y][x].x-1) && camx<(monde[y][x].x+1)))) //je touche avec la tete ?
	      {
		collHaut=1; //tete
		if(haut || sautF)
		  {
		    if(monde[y][x].id==4 && tailleJoueur==1.5)
		      monde[y][x].use=1;
		    if(monde[y][x].id==2)
		      {
			monde[y][x].use=1;
			if(!objet[monde[y][x].numObjet].use)
			  objet[monde[y][x].numObjet].obj=1;
		      }
		  }
		if(sautF)
		  sautF = 0;
	      }
	    if(((camy+1+tailleJoueur-(tailleJoueur-1))>=(monde[y][x].y-1) && (camy+1+tailleJoueur-(tailleJoueur-1))<=(monde[y][x].y+1)) &&
	       ((((camx+tailleJoueur)>(monde[y][x].x-1)) && ((camx+tailleJoueur)<(monde[y][x].x+1))) ||
		((camx-tailleJoueur)>(monde[y][x].x-1) && (camx-tailleJoueur)<(monde[y][x].x+1)) ||
		(camx>(monde[y][x].x-1) && camx<(monde[y][x].x+1)))) //je touche avec le bas ?
	      collBas=1; //bas
	    if(((camx+tailleJoueur)>=(monde[y][x].x-1) && (camx+tailleJoueur)<=(monde[y][x].x+1)) &&
	       (((camy+2+2*tailleJoueur)>(monde[y][x].y-1) && (camy+2+2*tailleJoueur)<(monde[y][x].y+1)) ||
	       	((camy+1+tailleJoueur-(tailleJoueur-1))>(monde[y][x].y-1) && (camy+1+tailleJoueur-(tailleJoueur-1))<(monde[y][x].y+1)) ||
		(((camy+2+tailleJoueur)>(monde[y][x].y-1) && (camy+2+tailleJoueur)<(monde[y][x].y+1))))) //je touche a droite ?
	      collDroite=1; //droite
	    if(((camx-tailleJoueur)>=(monde[y][x].x-1) && (camx-tailleJoueur)<=(monde[y][x].x+1)) &&
	       (((camy+2+2*tailleJoueur)>(monde[y][x].y-1) && (camy+2+2*tailleJoueur)<(monde[y][x].y+1)) ||
	       	((camy+1+tailleJoueur-(tailleJoueur-1))>(monde[y][x].y-1) && (camy+1+tailleJoueur-(tailleJoueur-1))<(monde[y][x].y+1)) ||
		(((camy+2+tailleJoueur)>(monde[y][x].y-1) && (camy+2+tailleJoueur)<(monde[y][x].y+1))))) // je touche a gauche ?
	      collGauche=1; //gauche
  	  }
      }
  //collision avec les objets
  for(y=0;y<nbObjet;y++)
    if(sqrt((camx-(objet[y].x+objet[y].xd))*(camx-(objet[y].x+objet[y].xd)) + ((camy+2)-(objet[y].y+objet[y].yd))*((camy+2)-(objet[y].y+objet[y].yd)))<=tailleJoueur+1 && objet[y].obj)
      {
	objet[y].use=1;
	objet[y].obj=0;
	if(tailleJoueur==1)
	  tailleJoueur=1.5;
      }
  //collision avec les monstres
  for(y=0;y<nbMob;y++)
    if(sqrt((camx-(mob[y].x+mob[y].xd))*(camx-(mob[y].x+mob[y].xd)) + ((camy+2)-(mob[y].y+mob[y].yd))*((camy+2)-(mob[y].y+mob[y].yd)))<=tailleJoueur+1 && !mob[y].use)//si j'ai toucher un monstre
      {
	if((camy+1+tailleJoueur-(tailleJoueur-1))>(mob[y].y+mob[y].yd))//si je touche l'ennemie par au dessu
	  {
	    mob[y].use=1;//il meurt
	    mob[y].obj=0;
	    if(!anticipation)
	      sautF=2;
	    else if(anticipation==1)
	      sautF=4;
	    else if(anticipation==2)
	      sautF=1;
	    else
	      sautF=5;
	    continue;
	  }
	if(tailleJoueur==1.5)//sinon si je suis grand
	  {
	    tailleJoueur=1;//je rapetisse
	    invincible=60;//je suis invincible 60 tour de boucle
	  }
	if(tailleJoueur==1 && !invincible)//si je suis petit et pas invincible
	  {
	    tailleJoueur=1.0;//je meurt
	    rechargeMonde();
	  }
      }
}

void collisionObjetMonstre(GLfloat tx, GLfloat ty)
{
  GLuint x,y;
  for(y=0;y<tailleY;y++)
    for(x=0;x<tailleX;x++)
      {
  	if(monde[y][x].id!=3 && monde[y][x].id!=0 && monde[y][x].id!=5 && monde[y][x].id!=6)
  	  {
	    if(monde[y][x].use==1 && monde[y][x].id==4) //est-il casse ?
	      continue;
	    if(((ty-1)>=(monde[y][x].y-1) && (ty-1)<=(monde[y][x].y+1)) &&
	       (((tx+1)>(monde[y][x].x-1) && ((tx+1)<(monde[y][x].x+1))) ||
		((tx-1)>(monde[y][x].x-1) && (tx-1)<(monde[y][x].x+1)) ||
		(tx>(monde[y][x].x-1) && tx<(monde[y][x].x+1)))) //je touche avec le bas ?
	      collBas=1; //bas
	    if(((tx+1)>=(monde[y][x].x-1) && (tx+1)<=(monde[y][x].x+1)) &&
	       (((ty+1)>(monde[y][x].y-1) && (ty+1)<(monde[y][x].y+1)) ||
	       	((ty-1)>(monde[y][x].y-1) && (ty-1)<(monde[y][x].y+1)) ||
		(((ty)>(monde[y][x].y-1) && (ty)<(monde[y][x].y+1))))) //je touche a droite ?
	      collDroite=1; //droite
	    if(((tx-1)>=(monde[y][x].x-1) && (tx-1)<=(monde[y][x].x+1)) &&
	       (((ty+1)>(monde[y][x].y-1) && (ty+1)<(monde[y][x].y+1)) ||
	       	((ty-1)>(monde[y][x].y-1) && (ty-1)<(monde[y][x].y+1)) ||
		(((ty)>(monde[y][x].y-1) && (ty)<(monde[y][x].y+1))))) // je touche a gauche ?
	      collGauche=1; //gauche
  	  }
      }
}
