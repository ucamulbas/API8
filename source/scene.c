#include "../include/scene.h"

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

void scene1()
{
  static int i = 0;
  if(i<120)
    {
      droite=1;
      i++;
    }
  else
    droite=0;
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
void scene3()
{
  static int i = 0;
  deplaceJoueur();
  deplaceObjet();
  deplaceMob();
}
