#include "../include/scene.h"
void automate()
{
  int x,nbTrou,y,trou;
  int yJoueur = ((camy+1+tailleJoueur-(tailleJoueur-1))/2)-1;
  int xJoueur = camx/2;
  float distance, distanceMob, milieu=(camy+2+tailleJoueur);
  static int stop=0, attObj=0;
  static float scamx=0;
  if(!stop)
    droite=1;
  x=xJoueur;
  if(-yJoueur>=0 && -yJoueur!=tailleY)
    {
      collisionJoueur();
      if(scamx==camx && scamy==camy && collBas && !attObj)
	sautF=3;
      scamx=camx;
      //Detection des trous
      if(monde[-yJoueur][x].id==0 && collBas && -yJoueur-1>0 && (monde[-yJoueur-1][x].id==0 || monde[-yJoueur-1][x].id==3 || monde[-yJoueur-1][x].id==5 || monde[-yJoueur-1][x].id==6))
	{
	  trou=1;
	  for(y=-yJoueur;y<tailleY;y++)
	    if(monde[y][x].id!=0)
	      {
		trou=0;
		break;
	      }
	  if(trou)
	    {
	      for(nbTrou=x+1;nbTrou<tailleX && monde[-yJoueur][nbTrou].id==0;nbTrou++);
	      for(y=-yJoueur-1;y>0 && monde[y][nbTrou].id!=0 && monde[y][nbTrou].id!=3 && monde[y][nbTrou].id!=6 && monde[y][nbTrou].id!=5;y--);
	      if(collBas)
		sautF=((nbTrou-x)*2)+(((-yJoueur-1)-y)*4);
	    }
	}
      //Detection des hauteurs
      if(tailleJoueur!=1)
	x+=1;
      if(-yJoueur-1>0 && monde[-yJoueur-1][x].id!=0 && monde[-yJoueur-1][x].id!=3 && monde[-yJoueur-1][x].id!=6 && monde[-yJoueur-1][x].id!=5)
	{
	  for(y=-yJoueur-1;y>0 && monde[y][x].id!=0 && monde[y][x].id!=3 && monde[y][x].id!=6 && monde[y][x].id!=5;y--);
	  if(collBas)
	    sautF=((-yJoueur-1)-y)*4;
	}
      x=xJoueur;
      //Detection des mobs
      if(tailleJoueur!=1)
	milieu-=0.5;
      for(y=0;y<nbMob;y++)
	{
	  distance=sqrt((camx-(mob[y].x+mob[y].xd))*(camx-(mob[y].x+mob[y].xd)) + ((camy+2)-(mob[y].y+mob[y].yd))*((camy+2)-(mob[y].y+mob[y].yd)));
	  if(distance<=6 && camx<((mob[y].x+mob[y].xd)-3) && milieu==(mob[y].y+mob[y].yd) && !mob[y].use && !sautF && collBas)
	    {
	      if(y<nbMob)
		{
		  distanceMob=sqrt(((mob[y].x+mob[y].xd)-(mob[y+1].x+mob[y+1].xd))*((mob[y].x+mob[y].xd)-(mob[y+1].x+mob[y].xd)) + ((mob[y].y+mob[y].yd)-(mob[y+1].y+mob[y+1].yd))*((mob[y].y+mob[y].yd)-(mob[y+1].y+mob[y+1].yd)));
		  if(distanceMob<=2 && distanceMob>=1 && camx<((mob[y+1].x+mob[y+1].xd)-3) && !mob[y+1].use && !sautF && collBas)
		    anticipation=1;
		  else if(distanceMob<=4 && distanceMob>=2 && camx<((mob[y+1].x+mob[y+1].xd)-3) && !mob[y+1].use && !sautF && collBas)
		    anticipation=2;
		  else
		    anticipation=0;
		}
	      sautF=5;
	    }
	  else if(distance<=7 && camx<((mob[y].x+mob[y].xd)-3) && milieu!=(mob[y].y+mob[y].yd) && !mob[y].use && !sautF && collBas)
	    anticipation=3;
	}
      //Detection des blocks mystere
      for(y=-yJoueur-2;y>0;y--)
	{
	  collisionJoueur();
	  if((tailleJoueur==1 && monde[y][x-1].id==2 && monde[y][x-1].use==0) || (tailleJoueur!=1 && monde[y][x-2].id==2 && monde[y][x-2].use==0))
	    {
	      droite=0;
	      if(collBas)
		{
		  sautF=((-yJoueur-1)-y)*4;
		  stop=1;
		}
	    }
	  else
	    if(collBas)
	      stop=0;
	}
      //Detection des objets
      for(y=0;y<nbObjet;y++)
	{
	  if(objet[y].obj && !objet[y].use && (objet[y].xd+objet[y].x)<camx)
	    {
	      droite=0;
	      stop=1;
	      attObj=1;
	    }
	  else
	    {
	      stop=0;
	      attObj=0;
	    }
	}
    }
  collDroite=collGauche=collHaut=collBas=0;
  deplaceJoueur();
  deplaceMob();
  deplaceObjet();
}

void scene0()
{
  static int i = 0;
  static int ok = 0;
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
    gauche=0;
  deplaceJoueur();
}

void scene2()
{
  static int i = 0;
  if(!i)
    {
      nbObjet=1;
      monde[3][110].obj=1;
      monde[3][110].numObjet=0;
      objet = calloc(nbObjet,sizeof*objet);
      objet[0].x=0.0;
      objet[0].y=2.0;
      objet[0].use=0;
      objet[0].obj=0;
      objet[0].id=0;
      objet[0].xd=monde[3][110].x;
      objet[0].yd=monde[3][110].y;
      tailleJoueur=1;
    }
  if(i<27)
    i++;
  if(i<40 && i>=27)
    {
      monde[6][4].y-=0.5;
      i++;
    }
  if(i>=40 && i<586)
    {
      droite=1;
      if(i<80)
	monde[6][4].x+=0.5;
      if(i>50 && i<60)//creation d'un escalier avec le sol
	{
	  monde[6][15].y-=0.5;
	  monde[6][14].y+=1.;
	  monde[6][16].y-=0.3;
	  monde[6][17].y-=0.1;
	}
      if(i==80)//je commence a sauter les marches
	haut=1;
      if(i==85)
	haut=0;
      if(i==87)
	haut=1;
      if(i==96)
	haut=0;
      if(i==99)
	haut=1;
      if(i==106)//je fini de sauter les marches
	haut=0;
      if(i==110)//disparition du sol
	{
	  monde[6][24].id=0;
	  monde[6][25].id=0;
	}
      if(i==115)//je saute le sol disparru
	haut=1;
      if(i==125)
	haut=0;
      if(i>=200 && i<=230)//soulevement du sol
	{
	  monde[6][46].y+=0.5;
	  monde[6][47].y+=0.5;
	  if(i==210)//saute par dessus le trou
	    haut=1;
	  if(i==216)
	    haut=0;
	}
      if(i==280)//je saute et tue le 1er mob 
	haut=1;
      if(i==290)
	haut=0;
      if(i==315)//je saute et tue le 2eme mob
	haut=1;
      if(i==320)
	haut=0;
      if(i==337)//je saute et tue le 3eme mob
	haut=1;
      if(i==342)
	haut=0;
      if(i==360)//je saute et tue le 4eme mob
	haut=1;
      if(i==366)//j'active le bloque mystere
	haut=0;
      if(i==470)
	haut=1;
      if(i==475)
	haut=0;
      if(i>480 && i<510)//j'att que le champi vienne a moi
	droite=0;
      else
	droite=1;
      i++;
    }
  if(i==586)
    droite=0;
  deplaceJoueur();
  deplaceMob();
  deplaceObjet();
}
