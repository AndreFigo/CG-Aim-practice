/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    Projeto
    Andre Carvalho 2019216156
    Ficheiro header
======================================================================================= */
#ifndef tiro_ao_alvo_h
#define tiro_ao_alvo_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/Glut.h>
#include "RgbImage.h"

//-------------colors
#define RED 1.0, 0.0, 0.0, 1.0
#define BLUE 0.0, 0.0, 1.0, 1.0
#define YELLOW 1.0, 0.8, 0.0, 1.0
#define GREEN 0.0, 1.0, 0.0, 1.0
#define WHITE 1.0, 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0, 1.0
#define GREY 0.7, 0.7, 0.7, 1.0
#define DARK_GREY 0.4, 0.4, 0.4, 1.0

#define VERTICAL 0, 1, 0
#define HORIZONTAL 0, 0, 1

#define PI 3.14159
#define MAX_BULLETS 12

GLfloat comp = 1.5, height_aim = 0.03, larg = 0.2;
static GLfloat gun_vertex[] = {
    //��������������������� Cima
    -larg, 0, comp,  // 0
    -larg, 0, -comp, // 1
    larg, 0, -comp,  // 2
    larg, 0, comp,   // 3

    //������������������� aim frente
    -0.05, height_aim, -1.2, // 4
    -0.05, height_aim, -1,   // 5
    0.05, height_aim, -1,    // 6
    0.05, height_aim, -1.2,  // 7

    -0.05, height_aim, -1, // 8
    0.05, height_aim, -1,  // 9
    0.05, 0, -1,           // 10
    -0.05, 0, -1,          // 11

    //�������������������� aim esquerda

    -0.15, height_aim, 0.3, // 12
    -0.15, height_aim, 0.4, // 13
    -0.1, height_aim, 0.4,  // 14
    -0.1, height_aim, 0.3,  // 15

    -0.15, height_aim, 0.4, // 16
    -0.1, height_aim, 0.4,  // 17
    -0.1, 0, 0.4,           // 18
    -0.15, 0, 0.4,          // 19

    //�������������������� aim direita

    0.15, height_aim, 0.3, // 20
    0.15, height_aim, 0.4, // 21
    0.1, height_aim, 0.4,  // 22
    0.1, height_aim, 0.3,  // 23

    0.15, height_aim, 0.4, // 24
    0.1, height_aim, 0.4,  // 25
    0.1, 0, 0.4,           // 26
    0.15, 0, 0.4,          // 27

    // =================== bulltet

    0.05, -height_aim, -1,    // 28
    0.05, -height_aim, -0.5,  // 29
    -0.05, -height_aim, -0.5, // 30
    -0.05, -height_aim, -1,   // 31

    0.05, -height_aim, -0.5,      // 32
    -0.05, -height_aim, -0.5,     // 33
    -0.05, -height_aim * 2, -0.5, // 34
    0.05, -height_aim * 2, -0.5,  // 35

};

static GLfloat normais[] = {

    //�������������������� Cima
    VERTICAL,
    VERTICAL,
    VERTICAL,
    VERTICAL,

    //�������������������� aim frente
    VERTICAL,
    VERTICAL,
    VERTICAL,
    VERTICAL,
    HORIZONTAL,
    HORIZONTAL,
    HORIZONTAL,
    HORIZONTAL,

    //�������������������� aim esquerda
    VERTICAL,
    VERTICAL,
    VERTICAL,
    VERTICAL,
    HORIZONTAL,
    HORIZONTAL,
    HORIZONTAL,
    HORIZONTAL,

    //�������������������� aim direita
    VERTICAL,
    VERTICAL,
    VERTICAL,
    VERTICAL,
    HORIZONTAL,
    HORIZONTAL,
    HORIZONTAL,
    HORIZONTAL,

    // =================== bulltet
    VERTICAL,
    VERTICAL,
    VERTICAL,
    VERTICAL,
    HORIZONTAL,
    HORIZONTAL,
    HORIZONTAL,
    HORIZONTAL,

};

static GLfloat textures_array[] = {

    //�������������������� Cima
    0, 0,
    1, 0,
    1, 1,
    0, 1,
    //�������������������� aim frente
    0, 0,
    1, 0,
    1, 1,
    0, 1,
    0, 0,
    1, 0,
    1, 1,
    0, 1,
    //�������������������� aim esquerda
    0, 0,
    1, 0,
    1, 1,
    0, 1,
    0, 0,
    1, 0,
    1, 1,
    0, 1,
    //�������������������� aim direita
    0, 0,
    1, 0,
    1, 1,
    0, 1,
    0, 0,
    1, 0,
    1, 1,
    0, 1,
    // missing bullet texture
};

// static GLfloat cor[] = {
//     //�������������������� Cima
//     GREY,
//     GREY,
//     GREY,
//     GREY,
//     //�������������������� aim frente
//     BLACK,
//     BLACK,
//     BLACK,
//     BLACK,
//     DARK_GREY,
//     DARK_GREY,
//     DARK_GREY,
//     DARK_GREY,
//     //�������������������� aim esquerda
//     BLACK,
//     BLACK,
//     BLACK,
//     BLACK,
//     DARK_GREY,
//     DARK_GREY,
//     DARK_GREY,
//     DARK_GREY,
//     //�������������������� aim direita
//     BLACK,
//     BLACK,
//     BLACK,
//     BLACK,
//     DARK_GREY,
//     DARK_GREY,
//     DARK_GREY,
//     DARK_GREY,
//     // =================== bulltet
//     YELLOW,
//     YELLOW,
//     YELLOW,
//     YELLOW,
//     YELLOW,
//     YELLOW,
//     YELLOW,
//     YELLOW,

// };

//=========================================================== poligonos

static GLuint main_cima[] = {0, 1, 2, 3};
static GLuint aim_frente_cima[] = {4, 5, 6, 7};
static GLuint aim_frente_vertical[] = {8, 9, 10, 11};
static GLuint aim_esquerda_cima[] = {12, 13, 14, 15};
static GLuint aim_esquerda_vertical[] = {16, 17, 18, 19};
static GLuint aim_direita_cima[] = {20, 21, 22, 23};
static GLuint aim_direita_vertical[] = {24, 25, 26, 27};
static GLuint bullet_top[] = {28, 29, 30, 31};
static GLuint bullet_front[] = {32, 33, 34, 35};

//===========================================================Variaveis e constantes

float rgb_buttons[6][3] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}};

// position, aim and gun
int shot_gun = 0, speed_level = 1;
float shift_value = 0.5, gun_ang_x = 0, gun_ang_y = 0, ang_rot;
GLfloat x_aim = 0, y_aim = 0, z_aim = 0, pos_z = 20;
GLfloat destiny_x = 0, destiny_z = 0, destiny_y = 0, atual_y = 0, atual_z = 0, atual_x = 0;

// back buttons and speed
int left_back = 0, right_back = 0;
float left_animation_t, right_animation_t, add_left, add_right;
int speed_ang = 0, turn_right = 0, turn_left = 0, add_rot = 4, counter_right, counter_left;

// target and rotation
int score = 0, total_levels = 10, n_bullets = 0, max_bullets = MAX_BULLETS, rotate = 0, ang_rotate_targ = 0;
float gunshots[MAX_BULLETS][4];

GLint msec = 10;
GLint wScreenMain = 600, hScreenMain = 600;

//============================================ TEXTURAS
RgbImage imag;
GLuint texture;

//============================================ Lights

GLfloat pos_foco[] = {0.0f, 0.0f, pos_z - (2 * comp), 1.0f}; // Foco 1
GLfloat aberturaFoco = 1;

GLint luzR = 1; //:::   'R'
GLint luzG = 1; //:::   'G'
GLint luzB = 1; //:::   'B'

int turn_on_main_light = 1;
GLfloat intensidade_main = 0.1;

GLfloat luzGlobalCorAmb[4] = {0.1, 0.1, 0.1, 1.0}; //
GLfloat localPos[4] = {0.0, 10, pos_z / 2, 1.0};
GLfloat localCorAmb[4] = {0, 0, 0, 0.0};
GLfloat localCorDif[4] = {luzR, luzG, luzB, 1.0};
GLfloat localCorEsp[4] = {luzR, luzG, luzB, 1.0};

//============================================ Materials

GLfloat goldAmb[] = {0.24725, 0.1995, 0.0745};
GLfloat goldDif[] = {0.75164, 0.60648, 0.22648};
GLfloat goldSpec[] = {0.628281, 0.555802, 0.366065};
GLint goldCoef = 0.4 * 128;

GLfloat blackPlasticAmb[] = {0.0, 0.0, 0.0};
GLfloat blackPlasticDif[] = {0.00, 0.00, 0.00};
GLfloat blackPlasticSpec[] = {0.0, 0.00, 0.0};
GLint blackPlasticCoef = 0.25 * 128;

GLfloat silverAmb[] = {0.19225, 0.19225, 0.19225};
GLfloat silverDif[] = {0.50754, 0.50754, 0.50754};
GLfloat silverSpec[] = {0.508273, 0.508273, 0.508273};
GLint silverCoef = 0.4 * 128;

GLfloat darkSilverAmb[] = {0.09225, 0.09225, 0.09225};
GLfloat darkSilverDif[] = {0.40754, 0.40754, 0.40754};
GLfloat darkSilverSpec[] = {0.408273, 0.408273, 0.408273};
GLint darkSilverCoef = 0.4 * 128;

#endif /* tiro_ao_alvo_h */