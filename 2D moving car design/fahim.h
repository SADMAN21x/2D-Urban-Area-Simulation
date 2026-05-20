#pragma once

extern GLfloat tx;
extern GLfloat ty;
extern GLfloat tx1;
extern GLfloat ty1;
extern GLfloat tx2;
extern GLfloat ty2;

extern float r;
extern float g;
extern float b;

extern float r1;
extern float g1;
extern float b1;

extern float starScale;
extern float starScaleDir;

extern float translateFlag;

extern int isNight;

void displayFahim();
void updateFahim(int value);
void keyboardFahim(unsigned char key, int x, int y);

void display();
void update(int value);
void keyboard(unsigned char key, int x, int y);
