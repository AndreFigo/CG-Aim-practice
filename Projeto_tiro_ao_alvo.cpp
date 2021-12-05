/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2021/22
	Projeto
	Andre Carvalho 2019216156
	Ficheiro principal
======================================================================================= */

#include "Projeto_tiro_ao_alvo.h"

void initMaterials(int material)
{

	switch (material)
	{
	case 0: //…………………………………………………………………………………………… gold
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);
		break;
	case 1: //……………………………………………………………………………………………black
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);
		break;
	case 2: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
		break;
	case 3: //…………………………………………………………………………………………… dark silver
		glMaterialfv(GL_FRONT, GL_AMBIENT, darkSilverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, darkSilverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, darkSilverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, darkSilverCoef);
		break;
	}
}

void initTexturas()
{
	//----------------------------------------- Gun texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	imag.LoadBmpFile("gun_text.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());
}

void updateLuz()
{
	localCorAmb[0] = luzR * intensidade_main;
	localCorAmb[1] = luzG * intensidade_main;
	localCorAmb[2] = luzB * intensidade_main;
	localCorDif[0] = luzR * intensidade_main;
	localCorDif[1] = luzG * intensidade_main;
	localCorDif[2] = luzB * intensidade_main;
	localCorEsp[0] = luzR * intensidade_main;
	localCorEsp[1] = luzG * intensidade_main;
	localCorEsp[2] = luzB * intensidade_main;

	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

void defineLuzes()
{

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);

	GLfloat Foco_direccao[] = {x_aim, y_aim, z_aim - pos_z, 0}; //……… -Z
	GLfloat Foco_cor[] = {0, 1, 0, 1};							//……… Cor da luz 1
	GLfloat Foco_ak = 1.0;
	GLfloat Foco_al = 0.05f;
	GLfloat Foco_aq = 0.0f;
	GLfloat Foco_Expon = 10.0; // Foco, SPOT_Exponent
	printf("pos foco %f\n", pos_foco[2]);
	//……………………………………………………………………………………………………………………………Foco laser
	glLightfv(GL_LIGHT1, GL_POSITION, pos_foco);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);
}

void inicializa(void)
{
	glClearColor(BLACK);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	initTexturas();
	defineLuzes();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, gun_vertex);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	// glEnableClientState(GL_COLOR_ARRAY);
	// glColorPointer(4, GL_FLOAT, 0, cor);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, textures_array); // coordenadas textura

	ang_rot = atan(shift_value / pos_z) * 180 / PI;
}

void write_text(char *string, GLfloat x, GLfloat y)
{
	glRasterPos2f(x, y);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void reset_but_color()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rgb_buttons[i][j] = 1;
		}
	}
}

void drawCircle(float t, float z)
{

	glPushMatrix();

	glBegin(GL_POLYGON);

	for (float i = 0; i < 360; i += 0.01)
	{
		glVertex3f(t * cos(PI * i / 180.0), t * sin(PI * i / 180.0), z);
	}
	glEnd();

	glPopMatrix();
}

int calculate_score()
{
	float dist = sqrt(destiny_x * destiny_x + destiny_y * destiny_y);

	if (dist > total_levels)
		return 0;
	return total_levels - floor(dist);
}

void display_dot(float x, float y, float z, float dot_size)
{
	glPushMatrix();
	glColor4f(BLACK);
	glTranslatef(x, y, 0);
	drawCircle(dot_size, z);
	glPopMatrix();
}

void drawTarget(int levels, float dot_size)
{

	glPushMatrix();

	if (rotate)
	{
		ang_rotate_targ += 5;
	}

	glRotatef(ang_rotate_targ, 0, 0, 1);

	float z = 0;
	for (int i = 0; i < levels; i++)
	{
		if (i % 2 == 1)
			glColor4f(RED);
		else
			glColor4f(WHITE);

		drawCircle(i + 1, z);
		z -= 0.01;
	}
	z = 0.01;
	for (int i = 0; i < n_bullets; i++)
	{
		if (gunshots[i][2])
		{
			glPushMatrix();
			glRotatef(-gunshots[i][3], 0, 0, 1);
			display_dot(gunshots[i][0], gunshots[i][1], z, dot_size);
			glPopMatrix();
		}
	}

	glPopMatrix();
}

void draw_gun()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();

	glPushMatrix();

	glTranslatef(0, 0, pos_z);
	glRotatef(gun_ang_y, 0, 1, 0);
	glRotatef(gun_ang_x, 1, 0, 0);

	glTranslatef(0, -1, -comp);
	glBindTexture(GL_TEXTURE_2D, texture);

	initMaterials(2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, main_cima);
	initMaterials(1);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_frente_cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_esquerda_cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_direita_cima);

	initMaterials(3);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_frente_vertical);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_esquerda_vertical);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, aim_direita_vertical);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	// bullet animation
	glPushMatrix();

	if (shot_gun)
	{

		float add_z = (destiny_z - pos_z) / (100 / speed_level);
		float add_x = (destiny_x) / (100 / speed_level);
		float add_y = (destiny_y + 1) / (100 / speed_level);

		atual_x += add_x;
		atual_y += add_y;
		atual_z += add_z;

		glTranslatef(atual_x, atual_y, atual_z);

		if (pos_z + atual_z <= destiny_z && fabs(atual_x) >= fabs(destiny_x) && fabs(atual_y) >= fabs(destiny_y + 1))
		{
			score = calculate_score();
			if (score > 0)
			{
				gunshots[n_bullets - 1][0] = destiny_x;
				gunshots[n_bullets - 1][1] = destiny_y;
				gunshots[n_bullets - 1][2] = 1;
				gunshots[n_bullets - 1][3] = ang_rotate_targ;
			}
			shot_gun = 0;
		}
	}
	glTranslatef(0, 0, pos_z);
	glRotatef(gun_ang_y, 0, 1, 0);
	glRotatef(gun_ang_x, 1, 0, 0);

	glTranslatef(0, -1, -comp);
	initMaterials(0);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bullet_top);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bullet_front);

	glPopMatrix();

	glPopMatrix();
}

void dir_but(float r, float g, float b)
{

	glColor3f(r, g, b);

	glBegin(GL_POLYGON);

	glVertex3f(-0.1, 0.5, 0);
	glVertex3f(0.1, 0.5, 0);
	glVertex3f(0.1, 0.2, 0);
	glVertex3f(0, 0.1, 0);
	glVertex3f(-0.1, 0.2, 0);

	glEnd();
}
void back_but(float raio)
{
	glColor4f(WHITE);

	float dist = 0.5;
	float x, y;

	glBegin(GL_POLYGON);

	for (float i = 0; i < 90; i += 0.1)
	{
		x = 0.25 + raio * cos(PI * i / 180.0);
		y = raio * sin(PI * i / 180.0);

		glVertex3f(x, y, 0);
	}

	for (float i = 90; i < 180; i += 0.1)
	{
		x = -0.25 + raio * cos(PI * i / 180.0);
		y = raio * sin(PI * i / 180.0);

		glVertex3f(x, y, 0);
	}

	glEnd();
}

void draw_square(float w, float h)
{

	glColor4f(DARK_GREY);

	glBegin(GL_POLYGON);

	glVertex3f(-w / 2, h / 2, 0);
	glVertex3f(w / 2, h / 2, 0);
	glVertex3f(w / 2, -h / 2, 0);
	glVertex3f(-w / 2, -h / 2, 0);

	glEnd();
}

void draw_controller()
{

	glPushMatrix();

	glPushMatrix();

	glTranslatef(-1.5, 0, 0);

	dir_but(rgb_buttons[0][0], rgb_buttons[0][1], rgb_buttons[0][2]);
	glRotatef(90, 0, 0, 1);
	dir_but(rgb_buttons[1][0], rgb_buttons[1][1], rgb_buttons[1][2]);

	glRotatef(90, 0, 0, 1);
	dir_but(rgb_buttons[2][0], rgb_buttons[2][1], rgb_buttons[2][2]);

	glRotatef(90, 0, 0, 1);
	dir_but(rgb_buttons[3][0], rgb_buttons[3][1], rgb_buttons[3][2]);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(1.5, 0.4, 0);
	glColor3f(rgb_buttons[4][0], rgb_buttons[4][1], rgb_buttons[4][2]);
	drawCircle(0.3, 0);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(2.2, -0.4, 0);
	glColor3f(rgb_buttons[5][0], rgb_buttons[5][1], rgb_buttons[5][2]);
	drawCircle(0.3, 0);

	glPopMatrix();

	draw_square(6, 4);

	glPushMatrix();

	if (left_back)
	{
		left_animation_t += add_left;
		if (left_animation_t == 3)
			add_left = -1;

		if (left_animation_t == 0)
			left_back = 0;

		glTranslatef(0, -left_animation_t * 0.1, 0);
	}

	glTranslatef(-2, 2, 0);

	back_but(0.4);

	glPopMatrix();

	glPushMatrix();

	if (right_back)
	{
		right_animation_t += add_right;
		if (right_animation_t == 3)
			add_right = -1;

		if (right_animation_t == 0)
			right_back = 0;

		glTranslatef(0, -right_animation_t * 0.1, 0);
	}

	glTranslatef(2, 2, 0);

	back_but(0.4);

	glPopMatrix();

	glPopMatrix();
}

void draw_pointer(float tam)
{

	glBegin(GL_TRIANGLES);

	glVertex3f(tam / 10, tam / 7, 0);
	glVertex3f(tam / 10, -tam / 7, 0);
	glVertex3f(-tam, 0, 0);

	glEnd();
}

void draw_stats()
{

	write_text((char *)"SPEED LEVEL", -1.2, 2);

	for (int i = 1; i < 11; i++)
	{
		char num[3];
		sprintf_s(num, 3, "%d", i);
		write_text(num, (1.4 - 0.03 * i) * cos(PI * (180 - ((i - 1) * 20)) / 180.0), (1.4 - 0.03 * i) * sin(PI * (180 - ((i - 1) * 20)) / 180.0));
	}

	float raio = 1;
	glPushMatrix();

	glPushMatrix();

	if (turn_right)
	{
		speed_ang += add_rot;
		counter_right++;
		if (counter_right == 5)
			turn_right = 0;
	}

	if (turn_left)
	{
		speed_ang -= add_rot;
		counter_left++;
		if (counter_left == 5)
			turn_left = 0;
	}

	glRotatef(-speed_ang, 0, 0, 1);

	glColor4f(RED);
	draw_pointer(raio);

	glPopMatrix();

	glColor4f(WHITE);
	drawCircle(raio, 0);

	write_text((char *)"YOUR SCORE:", -1.3, -2);

	glColor4f(RED);

	char score_label[3];
	sprintf_s(score_label, 3, "%d", score);
	write_text(score_label, -0.2, -2.5);

	/*if (score == total_levels)
	{
		glColor4f(WHITE);

		write_text((char *)"GOOD JOB!!", -1.2, -4);
	}*/

	glPopMatrix();
}

void draw_mini_target()
{

	glPushMatrix();
	glColor4f(WHITE);

	write_text((char *)"Target:", -7.5, 11);
	glTranslatef(0, -2, 0);
	drawTarget(total_levels, 0.5);
	glPopMatrix();
}

void iluminacao()
{
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
	if (turn_on_main_light)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
}

void display(void)
{

	//========================= Apaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);

	//����������������������������� main screen

	glViewport(200, 0, wScreenMain, hScreenMain);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)wScreenMain / hScreenMain, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, pos_z, x_aim, y_aim, z_aim, 0, 1, 0);

	iluminacao();
	updateLuz();

	draw_gun();
	drawTarget(total_levels, 0.2);
	glDisable(GL_LIGHTING);

	//�������������������������������������� controller

	glViewport(0, 0, 200, 200);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4, 4, -4, 4, -4, 4);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

	draw_controller();

	//�������������������������������������������� stats

	glViewport(0, 300, 200, 300);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -3, 3, -4, 4);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

	draw_stats();

	//�������������������������������������������� mini target

	glViewport(50, 200, 100, 100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-13, 13, -13, 13, 0, 13);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

	draw_mini_target();

	// reset buttons color
	reset_but_color();

	glutSwapBuffers();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'i':
	case 'I':
		intensidade_main = intensidade_main - 0.1;
		if (intensidade_main < 0)
			intensidade_main = 0;

		glutPostRedisplay();
		break;
	case 'o':
	case 'O':
		intensidade_main = intensidade_main + 0.1;
		if (intensidade_main > 1)
			intensidade_main = 1;

		glutPostRedisplay();
		break;
	case 'l':
	case 'L':
		turn_on_main_light = !turn_on_main_light;

		glutPostRedisplay();
		break;
	case 'k':
	case 'K':
		aberturaFoco += 1;
		if (aberturaFoco > 20)
			aberturaFoco = 20;
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);

		glutPostRedisplay();
		break;
	case 'j':
	case 'J':
		aberturaFoco -= 1;
		if (aberturaFoco < 1)
			aberturaFoco = 1;
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);

		glutPostRedisplay();
		break;

	case 'w':
	case 'W':

		rgb_buttons[0][1] = 0;
		rgb_buttons[0][2] = 0;

		y_aim += shift_value;
		gun_ang_x = (atan(y_aim / pos_z) * 180 / PI);

		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		rgb_buttons[1][1] = 0;
		rgb_buttons[1][2] = 0;

		x_aim -= shift_value;

		gun_ang_y = -1 * (atan(x_aim / pos_z) * 180 / PI);

		glutPostRedisplay();
		break;

	case 's':
	case 'S':

		rgb_buttons[2][1] = 0;
		rgb_buttons[2][2] = 0;

		y_aim -= shift_value;

		gun_ang_x = (atan(y_aim / pos_z) * 180 / PI);

		glutPostRedisplay();
		break;

	case 'd':
	case 'D':
		rgb_buttons[3][1] = 0;
		rgb_buttons[3][2] = 0;

		x_aim += shift_value;

		gun_ang_y = -1 * (atan(x_aim / pos_z) * 180 / PI);

		glutPostRedisplay();

		break;
	case 'p':
	case 'P':

		rgb_buttons[4][1] = 0;
		rgb_buttons[4][2] = 0;

		if (!shot_gun && n_bullets < max_bullets)
		{

			destiny_x = x_aim;
			destiny_z = z_aim;
			destiny_y = y_aim;

			n_bullets++;
			atual_y = 0;
			atual_x = 0;
			atual_z = 0;
			shot_gun = 1;
		}
		glutPostRedisplay();

		break;

	case 'r':
	case 'R':

		rgb_buttons[5][1] = 0;
		rgb_buttons[5][2] = 0;

		if (rotate)
			rotate = 0;
		else
			rotate = 1;

		glutPostRedisplay();

		break;

	case 'q':
	case 'Q':

		if (!left_back && !turn_left)
		{
			if (speed_level > 1)
			{

				speed_level -= 1;

				left_animation_t = 0;
				add_left = 1;
				left_back = 1;

				turn_left = 1;
				counter_left = 0;
			}
		}

		glutPostRedisplay();

		break;

	case 'e':
	case 'E':

		if (!right_back && !turn_right)
		{
			if (speed_level < 10)
			{

				speed_level += 1;

				right_animation_t = 0;
				add_right = 1;
				right_back = 1;

				turn_right = 1;
				counter_right = 0;
			}
		}

		glutPostRedisplay();

		break;
	case 27:
		exit(0);
		break;
	}
}

//======================================================= MAIN

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Shot with P; Move with w/a/s/d; Change speed with q/e; Rotate target with r");

	inicializa();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
