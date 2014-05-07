#include "../include/affichage.h"

/*
  idTexture[0]: solCote
  idTexture[1]: block
  idTexture[2]: blockUse
  idTexture[3]: fond
  idTexture[4]: Mario
  idTexture[5]: solFond
  idTexture[6]: sol
  idTexture[7]: blockCassable
  idTexture[8]: herbe
  idTexture[9]: Champi
  idTexture[10]: Gumba

  id[0]: sol
  id[1]: cubeSpe
  id[2]: fond
  id[3]: faceSupBlock
  id[4]: faceInfBlock
  id[5]: drapeau
*/

void dessineBlock (GLint x, GLint y)
{
  GLint face = 0;//variable pour savoir si il faut mettre de l'herbe ou pas (1 pour mettre l'herbe)
  static GLfloat cBlanc[]={1.0,1.0,1.0,0.0};
  static GLfloat rouge[]={1.0,0.0,0.0,0.0};
  static GLfloat marron[]={0.3,0.1,0.0,0.0};
  if(monde[y][x].id==5)
    {
      glTranslatef(mob[monde[y][x].numObjet].x,mob[monde[y][x].numObjet].y,0.0);
      if(!beau)
	{
	  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, marron);
	  glutSolidSphere(1.0,50,50);
	  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cBlanc);
	}
      else
	{
	  glRotatef(10,0,1,0);
	  glRotatef(-90,1,0,0);
	  glBindTexture(GL_TEXTURE_2D, idTexture[10]);
	   gluSphere(quadAtmosphere,1,128,128);
	  glBindTexture(GL_TEXTURE_2D, 0);
	}
      return;
    }
  glBindBuffer(GL_ARRAY_BUFFER, id[1]);
  if(monde[y][x].id==2)
    {
      if(!monde[y][x].use)
	glBindTexture(GL_TEXTURE_2D, idTexture[1]); //mon block est a l'etat initial
      else
	{
	  if(monde[y][x].obj==1 && objet[monde[y][x].numObjet].use==0)
	    {
	      glPushMatrix();
	      glTranslatef(objet[monde[y][x].numObjet].x,objet[monde[y][x].numObjet].y,0.0);
	      if(!beau)
		{
		  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rouge);
		  glutWireSphere(1.0,50,50);
		  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cBlanc);
		}
	      else
		{
		  glRotatef(10,0,1,0);
		  glRotatef(-90,1,0,0);
		  glBindTexture(GL_TEXTURE_2D, idTexture[9]);
		  gluSphere(quadAtmosphere,1,128,128);
		}
	      glPopMatrix();
	    }
	  glBindTexture(GL_TEXTURE_2D, idTexture[2]); //mon block a ete frappé
	}
    }
  else if(monde[y][x].id==1)
    {
      if(monde[y-1][x].id==0 || monde[y-1][x].id==3 || y==0 || monde[y-1][x].id==5 || monde[y-1][x].id==6) //y'a t'il quelque chose au dessu de mon block
	{
	  glBindTexture(GL_TEXTURE_2D, idTexture[6]); //oui alors je charge la texture correspondente
	  face=1;
	}
      else //sinon je charge la texture de cote
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);
    }
  else if(monde[y][x].id==4)//si c'est un block cassable
    glBindTexture(GL_TEXTURE_2D, idTexture[7]);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  //je dessine les cote
  glVertexPointer(3,GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(0));
  glTexCoordPointer(2,GL_FLOAT,2*sizeof(GLfloat),BUFFER_OFFSET(48*sizeof(GLfloat)));
  glNormalPointer(GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(48+32*sizeof(GLfloat)));
  glDrawArrays(GL_QUADS,0,20);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  if(face) //est-ce que je doit changer de texture ?
    {
      glBindTexture(GL_TEXTURE_2D, 0);
      glBindTexture(GL_TEXTURE_2D, idTexture[8]);
    }
  //je dessine le haut et le bas des blocks
  glBindBuffer(GL_ARRAY_BUFFER, id[3]);
  glVertexPointer(3,GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(0));
  glTexCoordPointer(2,GL_FLOAT,2*sizeof(GLfloat),BUFFER_OFFSET(12*sizeof(GLfloat)));
  glNormalPointer(GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(20*sizeof(GLfloat)));
  glDrawArrays(GL_QUADS,0,4);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  if(face)
    {
      glBindTexture(GL_TEXTURE_2D, 0);
      glBindTexture(GL_TEXTURE_2D, idTexture[0]);
    
    }
  glBindBuffer(GL_ARRAY_BUFFER, id[4]);
  glVertexPointer(3,GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(0));
  glTexCoordPointer(2,GL_FLOAT,2*sizeof(GLfloat),BUFFER_OFFSET(12*sizeof(GLfloat)));
  glNormalPointer(GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(20*sizeof(GLfloat)));
  glDrawArrays(GL_QUADS,0,4);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void dessineFond ()
{
  static GLfloat cBlanc[]={1.0,1.0,1.0,1.0};
  static GLfloat cNoir[]={0.0,0.0,0.0,0.0};
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,cBlanc);
  glBindBuffer(GL_ARRAY_BUFFER, id[2]);
  glBindTexture(GL_TEXTURE_2D, idTexture[3]);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  //je dessine le fond
  glVertexPointer(3,GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(0));
  glTexCoordPointer(2,GL_FLOAT,2*sizeof(GLfloat),BUFFER_OFFSET(12*sizeof(GLfloat)));
  glNormalPointer(GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(28*sizeof(GLfloat)));
  glDrawArrays(GL_QUADS,0,4);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  //je dessine le sol
  glBindBuffer(GL_ARRAY_BUFFER, id[0]);
  glBindTexture(GL_TEXTURE_2D, idTexture[5]);
  glVertexPointer(3,GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(0));
  glTexCoordPointer(2,GL_FLOAT,2*sizeof(GLfloat),BUFFER_OFFSET(12*sizeof(GLfloat)));
  glNormalPointer(GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(28*sizeof(GLfloat)));
  glDrawArrays(GL_QUADS,0,4);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,cNoir);
  glPopMatrix();
}


void display ()
{
  GLint x,y;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBlendFunc (GL_ONE, GL_ZERO);
  glLoadIdentity();
  //je place la camera
  if(!vue)
    gluLookAt(camx,camy+3,CAMZ+30,camx,camy,CAMZ-0.1,0.0,1.0,0.0); //vue de face
  else
    gluLookAt(camx,camy+15,CAMZ+20,camx+0.1,camy+4.0,CAMZ,0.0,1.0,0.0); //vue legerement de haut
  //je place mon monde
  for(y=0;y<tailleY;y++)
    for(x=0;x<tailleX;x++)
      {
	if(monde[y][x].id==6)
	  {
	    glPushMatrix();
	    glTranslatef(posFinNivX,posFinNivY-1,CAMZ);
	    glRotatef(-90,1,0,0);
	    gluCylinder(quadAtmosphere,0.5,0.5,10,100,100);
	    glPopMatrix();
	    continue;
	  }
	if(monde[y][x].id!=3 && monde[y][x].id!=0 && monde[y][x].id<=5 && monde[y][x].id>=1)
	  {
	    
	    if((monde[y][x].id==4 && monde[y][x].use==1) || (monde[y][x].id==5 && mob[monde[y][x].numObjet].use==1))//permet de ne pas afficher les blocks comme les points d'apparitions
	      continue;
	    if(sqrt((camx-monde[y][x].x)*(camx-monde[y][x].x))<=60 || monde[y][x].id==5)//affiche les blocks que si ils sont assez proche
	      {
		glPushMatrix();
		glTranslatef(monde[y][x].x,monde[y][x].y,CAMZ);
		dessineBlock(x,y);
		glPopMatrix();
	      }
	  }
      }
  glPushMatrix();
  glTranslatef(camx,camy+tailleJoueur+2,CAMZ);
  if(!invincible)//je ne suis pas invincible
    {
      glRotatef(70,1,0,0);
      glRotatef(180,0,1,0);
      glRotatef(-160,0,0,1);
      glBindTexture(GL_TEXTURE_2D,idTexture[4]);
      gluSphere(quadAtmosphere,tailleJoueur,128,128);
      glBindTexture(GL_TEXTURE_2D,0);
    }
  else//je suis invincible
    glutWireSphere(tailleJoueur,50,50);
  glPopMatrix();
  dessineFond();
  if(transi)
    transition();
  glutSwapBuffers();
}

void transition()
{
  static float i = 0.0;
  static float monter = 0.0;
  glEnableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_LIGHTING);
  //monter de drapeau
  glPushMatrix();
  glColor3f(0.2,0.8,0.2);
  glTranslatef(posFinNivX,posFinNivY+monter,CAMZ);
  glBindBuffer(GL_ARRAY_BUFFER,id[5]);
  glVertexPointer(3,GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(0));
  glDrawArrays(GL_TRIANGLES,0,3);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glColor3f(1.0,1.0,1.0);
  glPopMatrix();
  //transition
  glDisable(GL_DEPTH_TEST);
  glColor4f(0.0,0.0,0.0,i);
  glBindBuffer(GL_ARRAY_BUFFER,id[2]);
  glVertexPointer(3,GL_FLOAT,3*sizeof(GLfloat),BUFFER_OFFSET(0));
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_QUADS,0,4);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  if((int)i==1)
    {
      reinitMonde();
      chargeMonde();
      transi=0;
      i=0.0;
      monter=0;
      suivant++;
    }
  else
    {
      i+=0.01;
      if(monter<9)
	monter+=0.2;
    }
}
