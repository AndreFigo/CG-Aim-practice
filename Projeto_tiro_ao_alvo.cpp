/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2021/22
	................................................ JHenriques / APerrotta
	Trabalho 3 - Visualizacao
======================================================================================= */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/Glut.h>
#include "Projeto_tiro_ao_alvo.h"

//--------------------------------- Definir cores
#define RED		 1.0, 0.0, 0.0, 1.0
#define BLUE     0.0, 0.0, 1.0, 1.0
#define YELLOW	 1.0, 0.8, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GREY    0.7, 0.7, 0.7, 1.0
#define DARK_GREY    0.4, 0.4, 0.4, 1.0


#define PI		 3.14159

//================================================================================
//===========================================================Variaveis e constantes

GLfloat tam = 0.3;



GLfloat comp = 1.5, height_aim= 0.03, larg=0.2;
static GLfloat gun_vertex[] = {
		//……………………………………………………… Cima
		-larg,  0,  comp,	// 0 
		-larg,  0, -comp,	// 1 
		 larg ,  0, -comp,	// 2
		 larg,  0,  comp,	// 3 
	//………………………………………………… aim frente
		-0.05,  height_aim,  -1.2,	// 4
		-0.05,  height_aim, -1,	// 5 
		 0.05 ,  height_aim, -1,	// 6
		 0.05,  height_aim,  -1.2,	// 7 

		-0.05,  height_aim,  -1,	// 8 
		0.05,  height_aim, -1,	// 9 
		0.05 ,  0, -1,	//10
		-0.05,  0,  -1,	// 11 

	//…………………………………………………… aim esquerda

		 -0.15,  height_aim,  0.3,	// 12
		-0.15,  height_aim, 0.4,	// 13 
		 -0.1 ,  height_aim, 0.4,	// 14
		 -0.1,  height_aim,  0.3,	// 15 

		 -0.15,  height_aim,  0.4,	// 16 
		-0.1,  height_aim, 0.4,	// 17 
		-0.1 ,  0, 0.4,	//18
		-0.15,  0,  0.4,	// 19 

			//…………………………………………………… aim direita

		  0.15,  height_aim,  0.3,	// 20
		0.15,  height_aim, 0.4,	// 21 
		 0.1 ,  height_aim, 0.4,	// 22
		 0.1,  height_aim,  0.3,	// 23 

		 0.15,  height_aim,  0.4,	// 24 
		0.1,  height_aim, 0.4,	// 25 
		0.1 ,  0, 0.4,	//26
		0.15,  0,  0.4,	// 27 


		// =================== bulltet

		0.05,  -height_aim,  -1,	// 28
		0.05,  -height_aim, -0.5,	// 29 
		 -0.05 ,  -height_aim, -0.5,	// 30
		 -0.05,  -height_aim,  -1,	// 31 


		 0.05,  -height_aim,  -0.5,	// 32
		-0.05,  -height_aim, -0.5,	// 33 
		 -0.05 ,  -height_aim*2, -0.5,	// 34
		 0.05,  -height_aim*2,  -0.5,	// 35 



	
	//
};


static GLfloat normais[] = {

	//BASE
		0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,

	  //…………………………………………………………………………………………………… 
		0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   
	   0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,

		0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,

	   0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,


		0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,

	   0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,

		0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,

		 0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
	  

		

		
};
//------------------------------------------------------------ Cores
static GLfloat  cor[] = {
		GREY,
		GREY,
		GREY,
		GREY,
		BLACK,
		BLACK,
		BLACK,
		BLACK,
		DARK_GREY,
		DARK_GREY,
		DARK_GREY,
		DARK_GREY,
		BLACK,
		BLACK,
		BLACK,
		BLACK,
		DARK_GREY,
		DARK_GREY,
		DARK_GREY,
		DARK_GREY,
		BLACK,
		BLACK,
		BLACK,
		BLACK,
		DARK_GREY,
		DARK_GREY,
		DARK_GREY,
		DARK_GREY,
		YELLOW,
		YELLOW,
		YELLOW,
		YELLOW,
		YELLOW,
		YELLOW,
		YELLOW,
		YELLOW,
		
};


float rgb_buttons[5][3] = {
	{1,1,1},
	{1,1,1},
	{1,1,1},
	{1,1,1},
	{1,1,1}
};



//=========================================================== FACES DA MESA

static GLuint     main_cima[] = { 0,1,2,3 };   // regra da mao direita
static GLuint     aim_frente_cima[] = { 4,5,6,7 };    // regra da mao direita
static GLuint     aim_frente_vertical[] = { 8,9,10,11 };   // regra da mao direita
static GLuint     aim_esquerda_cima[] = { 12,13,14,15 };    // regra da mao direita
static GLuint     aim_esquerda_vertical[] = { 16,17,18,19 };   // regra da mao direita
static GLuint     aim_direita_cima[] = { 20,21,22,23 };    // regra da mao direita
static GLuint     aim_direita_vertical[] = { 24,25,26,27 };   // regra da mao direita
static GLuint     bullet_top[] = { 28,29,30,31};   // regra da mao direita
static GLuint     bullet_front[] = { 32,33,34,35 };   // regra da mao direita


GLfloat x_aim=0, y_aim=0, z_aim=0, pos_z=50;
float shift_value = 0.5, gun_ang_x = 0, gun_ang_y=0, ang_rot;
int ang = 60;
int shot_gun = 0, speed_level = 1;
float bullet_z = 0, destiny_x=0, destiny_z=0,  destiny_y = 0, atual_y = 0, atual_z=0, atual_x=0;

GLint     msec = 10;

//++++++++++++ falta a esquerda 
//++++++++++++ falta a direita 


//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreenMain = 600, hScreenMain = 600;			//.. janela (pixeis)
GLfloat		xC = 20.0, yC = 20.0, zC = 20.0;		//.. Mundo  (unidades mundo)

//-------------------------------------6----------------------- Visualizacao/Observador 
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat  angZoom = 45;
GLfloat  incZoom = 3;



//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	



	glFrontFace(GL_CCW);
	


	glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, vertices_comando); //………………………………………VertexArrays: vertices + normais + cores
	glVertexPointer(3, GL_FLOAT, 0, gun_vertex); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, cor);


	ang_rot = atan(shift_value / pos_z) * 180 / PI;
	printf("%f\n", ang_rot);


}

void reset_but_color() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			rgb_buttons[i][j] = 1;
		}
	}
}

void drawCircle(float t,float z) {

	int num = 10000;
	glPushMatrix();
	for (int i = 0; i < num; i++) {
		glRotatef(360.0 * i / num, 0, 0, 1);
		glBegin(GL_POLYGON);
			glVertex3f(-t, -t, z);
			glVertex3f(-t, t, z);
			glVertex3f(t, 0, z);
		glEnd();
	}
	glPopMatrix();

}

void drawTarget(int levels) {
	float z = 0;
	for (int i = 0; i <levels; i++) {
		if (i % 2 == 1) 
			glColor4f(RED);
		else
			glColor4f(WHITE);

		drawCircle(i+1,z );
		z -= 0.01;
	}
}



void draw_gun() {

	glPushMatrix();
	

		glPushMatrix();

			glTranslatef(0,0,pos_z);
			glRotatef(gun_ang_y, 0, 1, 0);
			glRotatef(gun_ang_x, 1, 0, 0);
			//glRotatef(10, 0, 0, 1);

			glTranslatef(0,-1 , -comp);


			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, main_cima);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_frente_cima);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_frente_vertical);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_esquerda_cima);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_esquerda_vertical);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_direita_cima);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_direita_vertical);

		glPopMatrix();

	// bullet animation 
		glPushMatrix();

			if (shot_gun) {
			
				float add_z =  ( destiny_z - pos_z)/(10*speed_level);
				float add_x = (destiny_x) / (10 * speed_level);
				float add_y = (destiny_y) / (10 * speed_level);

				atual_x += add_x;
				atual_y += add_y;
				atual_z += add_z;


				printf("atual_y, dest_y  %f, %f\n",  atual_y, destiny_y);
				printf("atual_x, dest_x  %f, %f\n", atual_x, destiny_x);
				printf("atual_z, dest_z  %f, %f\n", pos_z+atual_z, destiny_z);


				glTranslatef(atual_x, atual_y, atual_z);





				//if (pos_z + atual_z <= destiny_z && fabs(atual_x) >= fabs(destiny_x) && fabs(atual_y) >= fabs(destiny_y)) {
					if ( fabs(atual_y) >= fabs(destiny_y)) {
					shot_gun = 0;
					printf("acabou %f, %f\n", atual_z, destiny_z);
				}

			}
			glTranslatef(0, 0, pos_z);
			glRotatef(gun_ang_y, 0, 1, 0);
			glRotatef(gun_ang_x, 1, 0, 0);
			//glRotatef(10, 0, 0, 1);

			glTranslatef(0, -1, -comp);

			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bullet_top);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bullet_front);



		glPopMatrix();

  

	glPopMatrix();


		

	




}

void dir_but(float r, float g, float b) {

	
	glColor3f(r,g,b);

	glBegin(GL_POLYGON);

	glVertex3f(-0.1, 0.5, 0);
	glVertex3f(0.1, 0.5, 0);
	glVertex3f(0.1, 0.2, 0);
	glVertex3f(0, 0.1, 0);
	glVertex3f(-0.1, 0.2, 0);



	glEnd();




}
void back_but(float raio) {
	glColor4f(WHITE);

	float dist = 0.5;
	float x, y;

	glBegin(GL_POLYGON);

	for (float i = 0; i < 90; i+=0.1) {
		x = 0.25+raio * cos(PI * i / 180.0);
		y = raio * sin(PI * i / 180.0);

		glVertex3f(x, y, 0);

	}


	for (float i = 90; i < 180; i += 0.1) {
		x = -0.25+raio * cos(PI * i / 180.0);
		y = raio * sin(PI * i / 180.0);

		glVertex3f(x, y, 0);

	}


	glEnd();



}

void draw_square(float w, float h) {

	glColor4f(DARK_GREY);

	glBegin(GL_POLYGON);

	glVertex3f(-w/2, h/2, 0);
	glVertex3f(w / 2, h / 2, 0);
	glVertex3f(w / 2, -h / 2, 0);
	glVertex3f(-w / 2, -h / 2, 0);




	glEnd();

}

void draw_controller() {

	


	glPushMatrix();

	

		glPushMatrix();

			glTranslatef(-1.5,0,0);

			dir_but(rgb_buttons[0][0], rgb_buttons[0][1], rgb_buttons[0][2] );
			glRotatef(90, 0, 0, 1);
			dir_but(rgb_buttons[1][0], rgb_buttons[1][1], rgb_buttons[1][2]);

			glRotatef(90, 0, 0, 1);
			dir_but(rgb_buttons[2][0], rgb_buttons[2][1], rgb_buttons[2][2]);

			glRotatef(90, 0, 0, 1);
			dir_but(rgb_buttons[3][0], rgb_buttons[3][1], rgb_buttons[3][2]);



		glPopMatrix();

		glPushMatrix();

			glTranslatef(1.5, 0, 0);
			glColor3f(rgb_buttons[4][0], rgb_buttons[4][1], rgb_buttons[4][2]);
			drawCircle(0.5,0 );


		glPopMatrix();


	
	draw_square(6,4);

		glPushMatrix();

			glTranslatef(-2,2,0);

			back_but(0.4);


		glPopMatrix();


		glPushMatrix();

			glTranslatef(2, 2, 0);

			back_but(0.4);


		glPopMatrix();


	glPopMatrix();



}


void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//x = raio * cos(PI * ang / 180.0); // radianos
	//z = raio * sin(PI * ang / 180.0); // radianos

	//================================================================= Não modificar !!!!!!!!!!!!
	glViewport(200, 0, wScreenMain, hScreenMain);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10, 10, -10, 10);
	gluPerspective(90, (float)wScreenMain / hScreenMain, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, pos_z, x_aim, y_aim, z_aim, 0, 1, 0);

	//gluLookAt(0, 5, pos_z, 0, 0, pos_z, 0, 0, 1);



	
	drawTarget(10);
	draw_gun();


	//…………………………………………………………………………………………………………………………………………………………
	

	glViewport(0, 0, 200, 200);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4, 4, -4, 4, -4, 4);
	//gluPerspective(angZoom, (float)100 / 100, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);



	//…………………………………………………………………………………………………………………………………………………………
	draw_controller();

	reset_but_color();



	

	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}



//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {



	switch (key) {
		
	case 'w':

		rgb_buttons[0][1] = 0;
		rgb_buttons[0][2] = 0;

		y_aim += shift_value;
		gun_ang_x =  (atan(y_aim / pos_z) * 180 / PI) ;

		glutPostRedisplay();
		break;
	case 'a':
		rgb_buttons[1][1] = 0;
		rgb_buttons[1][2] = 0;

		x_aim -= shift_value;
	

		 gun_ang_y = -1 * (atan(x_aim / pos_z) * 180 / PI) ;


		glutPostRedisplay();
		break;

	case 's':
		rgb_buttons[2][1] = 0;
		rgb_buttons[2][2] = 0;

		y_aim -= shift_value;
		

		gun_ang_x =  (atan(y_aim / pos_z) * 180 / PI) ;




		glutPostRedisplay();
		break;

	case 'd':
		rgb_buttons[3][1] = 0;
		rgb_buttons[3][2] = 0;

		x_aim += shift_value;

		
		
		gun_ang_y = -1*(atan(x_aim / pos_z) * 180 / PI) ;


		glutPostRedisplay();

		break;
	case 'q':
		rgb_buttons[4][1] = 0;
		rgb_buttons[4][2] = 0;

		if (shot_gun) {
			
		}
		else {
			destiny_x = x_aim;
			destiny_z = z_aim;
			destiny_y = y_aim;
			atual_y = 0;
			atual_x = 0;
			atual_z = 0;
			shot_gun = 1;
		}
		glutPostRedisplay();

		break;

	case 27:
		exit(0);
		break;
	}

	printf("%f, %f \n", gun_ang_x, gun_ang_y);

}

// As setinhas nao sao usadas
// 
//void teclasNotAscii(int key, int x, int y) {
//
//	if (key == GLUT_KEY_UP) {
//		y_aim += shift_value;
//		glutPostRedisplay();
//	}
//	if (key == GLUT_KEY_DOWN) {
//		y_aim -= shift_value;
//		glutPostRedisplay();
//	}
//	if (key == GLUT_KEY_LEFT) {
//		x_aim -= shift_value;
//		glutPostRedisplay();
//	}
//	if (key == GLUT_KEY_RIGHT) {
//		x_aim += shift_value;
//		glutPostRedisplay();
//	}
//
//
//}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Shot with q");

	inicializa();

	//glutSpecialFunc(teclasNotAscii); not used
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);	
	glutTimerFunc(msec, Timer, 1);


	glutMainLoop();

	return 0;
}


