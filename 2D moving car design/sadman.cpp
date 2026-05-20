#include<windows.h>
#include <GL/freeglut.h>
#include <math.h>
#include "sadman.h"
#include "functions.h"

#define NUM_LOWER 3
#define NUM_UPPER 3

Car lowerLane[NUM_LOWER];
Car upperLane[NUM_UPPER];

float car_speed = 0.006f; 

float h1x = -0.7f;
float h2x = -0.4f;
float h3x = 0.1f;
float h4x = 0.5f;

int h1dir;
int h2dir;
int h3dir;
int h4dir;

float h1speed;
float h2speed;
float h3speed;
float h4speed;

void CarDesign(int brakeFlag) {

    glPushMatrix();
    //glTranslatef(car_tx1,car_ty, 0.0f);
    glScalef(0.5f, 0.7f, 1.0f);  

    glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.8f, 1.0f); // blue car
    glVertex2f(0.34f, -0.65f);
    glVertex2f(0.35f, -0.615f);
    glVertex2f(0.38f, -0.595f);
    glVertex2f(0.515f, -0.55f);
    glVertex2f(0.535f, -0.52f);
    glVertex2f(0.55f, -0.50f);
    glVertex2f(0.59f, -0.49f);
    glVertex2f(0.74f, -0.49f);
    glVertex2f(0.76f, -0.51f);
    glVertex2f(0.77f, -0.58f);
    glVertex2f(0.79f, -0.625f);
    glVertex2f(0.79f, -0.65f); //body shape
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(0.515f, -0.555f);
    glVertex2f(0.56f, -0.515f);
    glVertex2f(0.61f, -0.515f);
	glVertex2f(0.61f, -0.555f);   //car 1st window
    glEnd();

	        //1st window design
            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.515f, -0.555f);
            glVertex2f(0.56f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
			glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.56f, -0.515f);
            glVertex2f(0.61f, -0.515f);
			glEnd();

            glBegin(GL_LINES);
			glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.61f, -0.515f);
			glVertex2f(0.61f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
			glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.61f, -0.555f);
			glVertex2f(0.515f, -0.555f);   
			glEnd();



    glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f); // first door line
	glVertex2f(0.62f, -0.567f);
    glVertex2f(0.62f, -0.63f);
    glEnd();

	glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(0.625f, -0.515f);
	glVertex2f(0.69f, -0.515f);
	glVertex2f(0.69f, -0.555f);
    glVertex2f(0.625f, -0.555f);   //car 2nd window
	glEnd();

            //2nd window design
            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.625f, -0.515f);
            glVertex2f(0.69f, -0.515f);
			glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.69f, -0.515f);
            glVertex2f(0.69f, -0.555f);
			glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
			glVertex2f(0.69f, -0.555f);
			glVertex2f(0.625f, -0.555f);
			glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
			glVertex2f(0.625f, -0.555f);
			glVertex2f(0.625f, -0.515f);
			glEnd();



    glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);   // second door line
	glVertex2f(0.695f, -0.567f);
	glVertex2f(0.695f, -0.63f);
	glEnd();

	glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
	glVertex2f(0.70f, -0.515f);
	glVertex2f(0.75f, -0.515f);
    glVertex2f(0.75f, -0.555f);
	glVertex2f(0.70f, -0.555f);   //car 3rd window
	glEnd();
            
            //3rd window design
            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.70f, -0.515f);
			glVertex2f(0.75f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
			glVertex2f(0.75f, -0.515f);
            glVertex2f(0.75f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
			glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.75f, -0.555f);
            glVertex2f(0.70f, -0.555f);
            glEnd();

			glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.70f, -0.555f);
            glVertex2f(0.70f, -0.515f);
			glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f); 
	glVertex2f(0.34f, -0.65f);
    glVertex2f(0.35f, -0.64f);
    glVertex2f(0.79f, -0.64f);
    glVertex2f(0.79f, -0.65f); //simple design on body
    glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9f, 0.9f, 0.2f);
    glVertex2f(0.35f, -0.615f);
    glVertex2f(0.38f, -0.595f);
	glVertex2f(0.391f, -0.595f);
	glVertex2f(0.391f, -0.615f);  //yellow light front
	glEnd();

	glBegin(GL_POLYGON);
	
    if (brakeFlag == 1)
        glColor3f(1.0f, 0.0f, 0.0f);  //  bright
    else
        glColor3f(0.3f, 0.0f, 0.0f);  // dim

    glVertex2f(0.79f, -0.625f);
    glVertex2f(0.79f, -0.64f);
    glVertex2f(0.78f, -0.64f);
    glVertex2f(0.78f, -0.625f);   //red light back
	glEnd();


	glColor3f(0.0, 0.0, 0.0);
    drawCircle(0.45f, -0.65f, 0.04f, 100);
    drawCircle(0.70f, -0.65f, 0.04f, 100); //black upper wheals

    glColor3f(1.0, 1.0, 1.0);
    drawCircle(0.45f, -0.65f, 0.025f, 100);
    drawCircle(0.70f, -0.65f, 0.025f, 100); //white inner wheals 

    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(0.45f, -0.65f, 0.019f, 100);
    drawCircle(0.70f, -0.65f, 0.019f, 100); //ash inner wheals

    glPopMatrix();
}

void Car2Design(int brakeFlag) {
    
	//float car_ty = 0.20f; //eta korar karone car tar position upore uthe jacche

    glPushMatrix();
    //glTranslatef(car_tx2, car_ty, 0.0f);
    glScalef(0.5f, 0.7f, 1.0f);

    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.8f, 0.0f); // green car
    glVertex2f(-0.34f, -0.65f);
    glVertex2f(-0.35f, -0.615f);
    glVertex2f(-0.38f, -0.595f);
    glVertex2f(-0.515f, -0.55f);
    glVertex2f(-0.535f, -0.52f);
    glVertex2f(-0.55f, -0.50f);
    glVertex2f(-0.59f, -0.49f);
    glVertex2f(-0.74f, -0.49f);
    glVertex2f(-0.76f, -0.51f);
    glVertex2f(-0.77f, -0.58f);
    glVertex2f(-0.79f, -0.625f);
    glVertex2f(-0.79f, -0.65f); //body shape
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(-0.515f, -0.555f);
    glVertex2f(-0.56f, -0.515f);
    glVertex2f(-0.61f, -0.515f);
    glVertex2f(-0.61f, -0.555f);   //car 1st window
    glEnd();

            //1st window design
            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.515f, -0.555f);
            glVertex2f(-0.56f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.56f, -0.515f);
            glVertex2f(-0.61f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.61f, -0.515f);
            glVertex2f(-0.61f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.61f, -0.555f);
            glVertex2f(-0.515f, -0.555f);
            glEnd();



    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f); // first door line
    glVertex2f(-0.62f, -0.567f);
    glVertex2f(-0.62f, -0.63f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(-0.625f, -0.515f);
    glVertex2f(-0.69f, -0.515f);
    glVertex2f(-0.69f, -0.555f);
    glVertex2f(-0.625f, -0.555f);   //car 2nd window
    glEnd();

            //2nd window design
            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.625f, -0.515f);
            glVertex2f(-0.69f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.69f, -0.515f);
            glVertex2f(-0.69f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.69f, -0.555f);
            glVertex2f(-0.625f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.625f, -0.555f);
            glVertex2f(-0.625f, -0.515f);
            glEnd();



    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);   // second door line
    glVertex2f(-0.695f, -0.567f);
    glVertex2f(-0.695f, -0.63f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(-0.70f, -0.515f);
    glVertex2f(-0.75f, -0.515f);
    glVertex2f(-0.75f, -0.555f);
    glVertex2f(-0.70f, -0.555f);   //car 3rd window
    glEnd();

            //3rd window design
            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.70f, -0.515f);
            glVertex2f(-0.75f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.75f, -0.515f);
            glVertex2f(-0.75f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.75f, -0.555f);
            glVertex2f(-0.70f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(-0.70f, -0.555f);
            glVertex2f(-0.70f, -0.515f);
            glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.34f, -0.65f);
    glVertex2f(-0.35f, -0.64f);
    glVertex2f(-0.79f, -0.64f);
    glVertex2f(-0.79f, -0.65f); //simple design on body
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.2f);
    glVertex2f(-0.35f, -0.615f);
    glVertex2f(-0.38f, -0.595f);
    glVertex2f(-0.391f, -0.595f);
    glVertex2f(-0.391f, -0.615f);  //yellow light front
    glEnd();

    glBegin(GL_POLYGON);
    
    if (brakeFlag == 1)
        glColor3f(1.0f, 0.0f, 0.0f);  //  bright
    else
        glColor3f(0.3f, 0.0f, 0.0f);  // dim

    glVertex2f(-0.79f, -0.625f);
    glVertex2f(-0.79f, -0.64f);
    glVertex2f(-0.78f, -0.64f);
    glVertex2f(-0.78f, -0.625f);   //red light back
    glEnd();


    glColor3f(0.0, 0.0, 0.0);
    drawCircle(-0.45f, -0.65f, 0.04f, 100);
    drawCircle(-0.70f, -0.65f, 0.04f, 100); //black upper wheals

    glColor3f(1.0, 1.0, 1.0);
    drawCircle(-0.45f, -0.65f, 0.025f, 100);
    drawCircle(-0.70f, -0.65f, 0.025f, 100); //white inner wheals 

    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(-0.45f, -0.65f, 0.019f, 100);
    drawCircle(-0.70f, -0.65f, 0.019f, 100); //ash inner wheals

    glPopMatrix();
}

void Car3Design(int brakeFlag) {

    //car_ty = -0.1f;

    glPushMatrix();
    //glTranslatef(car_tx3, car_ty, 0.0f);
    glScalef(0.5f, 0.7f, 1.0f);
 
    glBegin(GL_POLYGON);
    glColor3f(0.95f, 0.09f, 0.94f); // purple car
    glVertex2f(0.34f, -0.65f);
    glVertex2f(0.35f, -0.615f);
    glVertex2f(0.38f, -0.595f);
    glVertex2f(0.515f, -0.55f);
    glVertex2f(0.535f, -0.52f);
    glVertex2f(0.55f, -0.50f);
    glVertex2f(0.59f, -0.49f);
    glVertex2f(0.74f, -0.49f);
    glVertex2f(0.76f, -0.51f);
    glVertex2f(0.77f, -0.58f);
    glVertex2f(0.79f, -0.625f);
    glVertex2f(0.79f, -0.65f); //body shape
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(0.515f, -0.555f);
    glVertex2f(0.56f, -0.515f);
    glVertex2f(0.61f, -0.515f);
    glVertex2f(0.61f, -0.555f);   //car 1st window
    glEnd();

            //1st window design
            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.515f, -0.555f);
            glVertex2f(0.56f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.56f, -0.515f);
            glVertex2f(0.61f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.61f, -0.515f);
            glVertex2f(0.61f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.61f, -0.555f);
            glVertex2f(0.515f, -0.555f);
            glEnd();



    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f); // first door line
    glVertex2f(0.62f, -0.567f);
    glVertex2f(0.62f, -0.63f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(0.625f, -0.515f);
    glVertex2f(0.69f, -0.515f);
    glVertex2f(0.69f, -0.555f);
    glVertex2f(0.625f, -0.555f);   //car 2nd window
    glEnd();

            //2nd window design
            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.625f, -0.515f);
            glVertex2f(0.69f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.69f, -0.515f);
            glVertex2f(0.69f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.69f, -0.555f);
            glVertex2f(0.625f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.625f, -0.555f);
            glVertex2f(0.625f, -0.515f);
            glEnd();



    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);   // second door line
    glVertex2f(0.695f, -0.567f);
    glVertex2f(0.695f, -0.63f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(0.70f, -0.515f);
    glVertex2f(0.75f, -0.515f);
    glVertex2f(0.75f, -0.555f);
    glVertex2f(0.70f, -0.555f);   //car 3rd window
    glEnd();

            //3rd window design
            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.70f, -0.515f);
            glVertex2f(0.75f, -0.515f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.75f, -0.515f);
            glVertex2f(0.75f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.75f, -0.555f);
            glVertex2f(0.70f, -0.555f);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.8f, 0.8f, 0.8f);
            glVertex2f(0.70f, -0.555f);
            glVertex2f(0.70f, -0.515f);
            glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0.34f, -0.65f);
    glVertex2f(0.35f, -0.64f);
    glVertex2f(0.79f, -0.64f);
    glVertex2f(0.79f, -0.65f); //simple design on body
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.2f);
    glVertex2f(0.35f, -0.615f);
    glVertex2f(0.38f, -0.595f);
    glVertex2f(0.391f, -0.595f);
    glVertex2f(0.391f, -0.615f);  //yellow light front
    glEnd();

    glBegin(GL_POLYGON);
    
    if (brakeFlag == 1)
        glColor3f(1.0f, 0.0f, 0.0f);  //  bright
    else
        glColor3f(0.3f, 0.0f, 0.0f);  // dim

    glVertex2f(0.79f, -0.625f);
    glVertex2f(0.79f, -0.64f);
    glVertex2f(0.78f, -0.64f);
    glVertex2f(0.78f, -0.625f);   //red light back
    glEnd();


    glColor3f(0.0, 0.0, 0.0);
    drawCircle(0.45f, -0.65f, 0.04f, 100);
    drawCircle(0.70f, -0.65f, 0.04f, 100); //black upper wheals

    glColor3f(1.0, 1.0, 1.0);
    drawCircle(0.45f, -0.65f, 0.025f, 100);
    drawCircle(0.70f, -0.65f, 0.025f, 100); //white inner wheals 

    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(0.45f, -0.65f, 0.019f, 100);
    drawCircle(0.70f, -0.65f, 0.019f, 100); //ash inner wheals

    glPopMatrix();
}

void Car4Design(int brakeFlag, int lightFlag) {
    
    //car_ty = -0.4f;

    glPushMatrix();
    //glTranslatef(car_tx4, car_ty, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f); //red car to white
    glVertex2f(0.16f, -0.08f);
    glVertex2f(0.20f, -0.08f);
    glVertex2f(0.20f, -0.19f);
    glVertex2f(0.1f, -0.19f);
    glVertex2f(0.1f, -0.15f); //front body shape
    glEnd();

    //front light
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.10f, -0.15f);
    glVertex2f(0.11f, -0.15f);
    glVertex2f(0.11f, -0.17f);
    glVertex2f(0.10f, -0.17f);
    glEnd();
            
            //window
            glBegin(GL_POLYGON);
            glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(0.165f, -0.09f);
            glVertex2f(0.19f, -0.09f);
			glVertex2f(0.19f, -0.14f);
			glVertex2f(0.13f, -0.14f);
			glEnd();

			//window design
            glBegin(GL_LINES);
            glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(0.165f, -0.09f);
			glVertex2f(0.19f, -0.09f);
            glEnd();
            glBegin(GL_LINES);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(0.19f, -0.09f);
            glVertex2f(0.19f, -0.14f);
            glEnd();
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(0.19f, -0.14f);
            glVertex2f(0.13f, -0.14f);
			glEnd();
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2f(0.13f, -0.14f);
			glVertex2f(0.165f, -0.09f);
			glEnd();

	glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.201f, -0.06f);
    glVertex2f(0.37f, -0.06f);
    glVertex2f(0.37f, -0.19f);
	glVertex2f(0.201f, -0.19f); //back body
    glEnd();

	//back light
	glBegin(GL_POLYGON);
    if (brakeFlag == 1)
        glColor3f(1.0f, 0.0f, 0.0f); // bright red
    else
        glColor3f(0.3f, 0.0f, 0.0f); // dim red
	glVertex2f(0.36f, -0.17f);
	glVertex2f(0.37f, -0.17f);
	glVertex2f(0.37f, -0.18f);
	glVertex2f(0.36f, -0.18f);
	glEnd();

	        //back body design
            glBegin(GL_LINES);
            glColor3f(0.7f, 0.9f, 1.0f);
			glVertex2f(0.201f, -0.12f);
			glVertex2f(0.37f, -0.12f);
            glEnd();
			glBegin(GL_LINES);
			glColor3f(0.7f, 0.9f, 1.0f);
			glVertex2f(0.201f, -0.15f);
            glVertex2f(0.37f, -0.15f);
			glEnd();
            glBegin(GL_LINES);
            glColor3f(0.7f, 0.9f, 1.0f);
            glVertex2f(0.201f, -0.09f);
            glVertex2f(0.37f, -0.09f);
            glEnd();

     glColor3f(0.0, 0.0, 0.0);
     drawCircle(0.16f, -0.195f, 0.025f, 100); //front black wheel
     glColor3f(1.0, 1.0, 1.0);
     drawCircle(0.16f, -0.195f, 0.017f, 100); // white inner
     glColor3f(0.7f, 0.7f, 0.7f);
     drawCircle(0.16f, -0.195f, 0.013f, 100); // ash inner

     glColor3f(0.0, 0.0, 0.0);
	 drawCircle(0.32f, -0.195f, 0.025f, 100);  //back black wheel
     glColor3f(1.0, 1.0, 1.0);
     drawCircle(0.32f, -0.195f, 0.017f, 100);  // white inner
     glColor3f(0.7f, 0.7f, 0.7f);
     drawCircle(0.32f, -0.195f, 0.013f, 100); // ash inner

     if (lightFlag == 1) {

         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         glBegin(GL_QUADS);
         // near side (bright)
         glColor4f(1.0f, 0.95f, 0.40f, 0.65f);
         glVertex2f(0.10f, -0.15f);

         glColor4f(1.0f, 0.95f, 0.40f, 0.65f);
         glVertex2f(0.10f, -0.17f);

         glColor4f(1.0f, 0.95f, 0.40f, 0.05f);
         glVertex2f(-0.18f, -0.26f);

         glColor4f(1.0f, 0.95f, 0.40f, 0.05f);
         glVertex2f(-0.18f, -0.06f);

         glEnd();
         glDisable(GL_BLEND);
     }

    glPopMatrix();
}

void Car5Design(int brakeFlag) {

    //float car_ty = 0.20f; 

    glPushMatrix();
    //glTranslatef(car_tx5, car_ty, 0.0f);
    glScalef(0.5f, 0.7f, 1.0f);

    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.8f, 1.0f); // blue car
    glVertex2f(-0.34f, -0.65f);
    glVertex2f(-0.35f, -0.615f);
    glVertex2f(-0.38f, -0.595f);
    glVertex2f(-0.515f, -0.55f);
    glVertex2f(-0.535f, -0.52f);
    glVertex2f(-0.55f, -0.50f);
    glVertex2f(-0.59f, -0.49f);
    glVertex2f(-0.74f, -0.49f);
    glVertex2f(-0.76f, -0.51f);
    glVertex2f(-0.77f, -0.58f);
    glVertex2f(-0.79f, -0.625f);
    glVertex2f(-0.79f, -0.65f); //body shape
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(-0.515f, -0.555f);
    glVertex2f(-0.56f, -0.515f);
    glVertex2f(-0.61f, -0.515f);
    glVertex2f(-0.61f, -0.555f);   //car 1st window
    glEnd();

    //1st window design
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.515f, -0.555f);
    glVertex2f(-0.56f, -0.515f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.56f, -0.515f);
    glVertex2f(-0.61f, -0.515f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.61f, -0.515f);
    glVertex2f(-0.61f, -0.555f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.61f, -0.555f);
    glVertex2f(-0.515f, -0.555f);
    glEnd();



    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f); // first door line
    glVertex2f(-0.62f, -0.567f);
    glVertex2f(-0.62f, -0.63f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(-0.625f, -0.515f);
    glVertex2f(-0.69f, -0.515f);
    glVertex2f(-0.69f, -0.555f);
    glVertex2f(-0.625f, -0.555f);   //car 2nd window
    glEnd();

    //2nd window design
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.625f, -0.515f);
    glVertex2f(-0.69f, -0.515f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.69f, -0.515f);
    glVertex2f(-0.69f, -0.555f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.69f, -0.555f);
    glVertex2f(-0.625f, -0.555f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.625f, -0.555f);
    glVertex2f(-0.625f, -0.515f);
    glEnd();



    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);   // second door line
    glVertex2f(-0.695f, -0.567f);
    glVertex2f(-0.695f, -0.63f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(-0.70f, -0.515f);
    glVertex2f(-0.75f, -0.515f);
    glVertex2f(-0.75f, -0.555f);
    glVertex2f(-0.70f, -0.555f);   //car 3rd window
    glEnd();

    //3rd window design
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.70f, -0.515f);
    glVertex2f(-0.75f, -0.515f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.75f, -0.515f);
    glVertex2f(-0.75f, -0.555f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.75f, -0.555f);
    glVertex2f(-0.70f, -0.555f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.70f, -0.555f);
    glVertex2f(-0.70f, -0.515f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.34f, -0.65f);
    glVertex2f(-0.35f, -0.64f);
    glVertex2f(-0.79f, -0.64f);
    glVertex2f(-0.79f, -0.65f); //simple design on body
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 0.2f);
    glVertex2f(-0.35f, -0.615f);
    glVertex2f(-0.38f, -0.595f);
    glVertex2f(-0.391f, -0.595f);
    glVertex2f(-0.391f, -0.615f);  //yellow light front
    glEnd();

    glBegin(GL_POLYGON);
    
    if (brakeFlag == 1)
        glColor3f(1.0f, 0.0f, 0.0f);  //  bright
    else
        glColor3f(0.3f, 0.0f, 0.0f);  // dim

    glVertex2f(-0.79f, -0.625f);
    glVertex2f(-0.79f, -0.64f);
    glVertex2f(-0.78f, -0.64f);
    glVertex2f(-0.78f, -0.625f);   //red light back
    glEnd();


    glColor3f(0.0, 0.0, 0.0);
    drawCircle(-0.45f, -0.65f, 0.04f, 100);
    drawCircle(-0.70f, -0.65f, 0.04f, 100); //black upper wheals

    glColor3f(1.0, 1.0, 1.0);
    drawCircle(-0.45f, -0.65f, 0.025f, 100);
    drawCircle(-0.70f, -0.65f, 0.025f, 100); //white inner wheals 

    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(-0.45f, -0.65f, 0.019f, 100);
    drawCircle(-0.70f, -0.65f, 0.019f, 100); //ash inner wheals

    glPopMatrix();
}

void Car6Design(int brakeFlag) {

    //car_ty = -0.1f;

    glPushMatrix();
    //glTranslatef(car_tx6, car_ty, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f); //red car
    glVertex2f(-0.16f, -0.08f);
    glVertex2f(-0.20f, -0.08f);
    glVertex2f(-0.20f, -0.19f);
    glVertex2f(-0.1f, -0.19f);
    glVertex2f(-0.1f, -0.15f); //front body shape
    glEnd();

    //front light
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(-0.10f, -0.15f);
    glVertex2f(-0.11f, -0.15f);
    glVertex2f(-0.11f, -0.17f);
    glVertex2f(-0.10f, -0.17f);
    glEnd();

            //window
            glBegin(GL_POLYGON);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(-0.165f, -0.09f);
            glVertex2f(-0.19f, -0.09f);
            glVertex2f(-0.19f, -0.14f);
            glVertex2f(-0.13f, -0.14f);
            glEnd();

            //window design
            glBegin(GL_LINES);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2f(-0.165f, -0.09f);
            glVertex2f(-0.19f, -0.09f);
            glEnd();
            glBegin(GL_LINES);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2f(-0.19f, -0.09f);
            glVertex2f(-0.19f, -0.14f);
            glEnd();
            glBegin(GL_LINES);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2f(-0.19f, -0.14f);
            glVertex2f(-0.13f, -0.14f);
            glEnd();
            glBegin(GL_LINES);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2f(-0.13f, -0.14f);
            glVertex2f(-0.165f, -0.09f);
            glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.75f, 0.75f, 0.75f);
    glVertex2f(-0.201f, -0.06f);
    glVertex2f(-0.37f, -0.06f);
    glVertex2f(-0.37f, -0.19f);
    glVertex2f(-0.201f, -0.19f); //back body
    glEnd();

    //back light
    glBegin(GL_POLYGON);
    
    if (brakeFlag == 1)
        glColor3f(1.0f, 0.0f, 0.0f);  //  bright
    else
        glColor3f(0.3f, 0.0f, 0.0f);  // dim

    glVertex2f(-0.36f, -0.17f);
    glVertex2f(-0.37f, -0.17f);
    glVertex2f(-0.37f, -0.18f);
    glVertex2f(-0.36f, -0.18f);
    glEnd();

            //back body design
            glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(-0.201f, -0.12f);
            glVertex2f(-0.37f, -0.12f);
            glEnd();
            glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(-0.201f, -0.15f);
            glVertex2f(-0.37f, -0.15f);
            glEnd();
            glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(-0.201f, -0.09f);
            glVertex2f(-0.37f, -0.09f);
            glEnd();

    glColor3f(0.0, 0.0, 0.0);
    drawCircle(-0.16f, -0.195f, 0.025f, 100); //front black wheel
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(-0.16f, -0.195f, 0.017f, 100); // white inner
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(-0.16f, -0.195f, 0.013f, 100); // ash inner

    glColor3f(0.0, 0.0, 0.0);
    drawCircle(-0.32f, -0.195f, 0.025f, 100);  //back black wheel
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(-0.32f, -0.195f, 0.017f, 100);  // white inner
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(-0.32f, -0.195f, 0.013f, 100); // ash inner

    glPopMatrix();
}

void initCars() {
    
    for (int i = 0; i < NUM_LOWER; i++) {
        lowerLane[i].x = 1.0f + i * 0.5f; // start spacing
        lowerLane[i].y = -0.4f;
        lowerLane[i].speed = car_speed + (rand() % 5) * 0.002f;
        lowerLane[i].brake = 0;
    }

    for (int i = 0; i < NUM_UPPER; i++) {
        upperLane[i].x = -1.0f - i * 0.5f;
        upperLane[i].y = -0.1f;
        upperLane[i].speed = car_speed + (rand() % 5) * 0.002f;
        upperLane[i].brake = 0;
    }

    h1speed = 0.001f + (rand() % 5) * 0.0005f;
    h2speed = 0.001f + (rand() % 5) * 0.0005f;
    h3speed = 0.001f + (rand() % 5) * 0.0005f;
    //h4speed = 0.001f + (rand() % 5) * 0.0005f;

    h1dir = rand() % 2;
    h2dir = rand() % 2;
    h3dir = rand() % 2;
    //h4dir = rand() % 2;
}

//void drawTrafficLight() {
//
//    // POLE
//    glBegin(GL_QUADS);
//    glColor3f(0.2f, 0.2f, 0.2f);
//    glVertex2f(-0.60f, -0.2f);
//    glVertex2f(-0.58f, -0.2f);
//    glVertex2f(-0.58f, 0.05f);
//    glVertex2f(-0.60f, 0.05f);
//
//    glEnd();
//
//    // LIGHT BOX
//    glBegin(GL_QUADS);
//    glColor3f(0.1f, 0.1f, 0.1f);
//    glVertex2f(-0.62f, 0.05f);
//    glVertex2f(-0.54f, 0.05f);
//    glVertex2f(-0.54f, 0.20f);
//    glVertex2f(-0.62f, 0.20f);
//
//    glEnd();
//
//    //  RED LIGHT
//    if (lightState == 0)
//        glColor3f(1.0f, 0.0f, 0.0f);
//    else
//        glColor3f(0.3f, 0.0f, 0.0f);
//    drawCircle(-0.58f, 0.17f, 0.015f, 100);   
//
//    // YELLOW LIGHT
//    if (lightState == 1)
//        glColor3f(1.0f, 1.0f, 0.0f);
//    else
//        glColor3f(0.3f, 0.3f, 0.0f);
//    drawCircle(-0.58f, 0.12f, 0.015f, 100);
//
//    // GREEN LIGHT
//    if (lightState == 2)
//        glColor3f(0.0f, 1.0f, 0.0f);
//    else
//        glColor3f(0.0f, 0.3f, 0.0f);
//    drawCircle(-0.58f, 0.07f, 0.015f, 100);
//
//}

void drawHuman(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // ===== HEAD =====
    glColor3f(1.0f, 0.82f, 0.68f);
    drawCircle(0.0f, 0.09f, 0.018f, 50);

    // ===== NECK =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);

    glEnd();

    // ===== HAIR =====
    glBegin(GL_POLYGON);
    glColor3f(0.05f, 0.05f, 0.05f);

    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);

    glEnd();

    // ===== BODY / SHIRT =====
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.55f, 0.75f);

    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);

    glEnd();

    // ===== LEFT ARM =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.028f, 0.050f);
    glVertex2f(-0.040f, 0.040f);
    glVertex2f(-0.036f, -0.010f);
    glVertex2f(-0.022f, 0.000f);

    glEnd();

    // ===== RIGHT ARM =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(0.028f, 0.050f);
    glVertex2f(0.040f, 0.040f);
    glVertex2f(0.036f, -0.010f);
    glVertex2f(0.022f, 0.000f);

    glEnd();

    // ===== LEFT LEG =====
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);

    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);
    glEnd();

    // ===== RIGHT LEG =====
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);

    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);
    glEnd();

    // ===== LEFT SHOE =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);

    glEnd();

    // ===== RIGHT SHOE =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);

    glEnd();

    glPopMatrix();
}

void drawHuman2(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // ===== HEAD =====
    glColor3f(1.0f, 0.82f, 0.68f);
    drawCircle(0.0f, 0.09f, 0.018f, 50);

    // ===== NECK =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);

    glEnd();

    // ===== HAIR =====
    glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.05f, 0.05f); // red hair

    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);

    glEnd();

    // ===== BODY / SHIRT =====
    glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.55f, 0.0f); // green shirt

    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);

    glEnd();

    // ===== LEFT ARM =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.028f, 0.050f);
    glVertex2f(-0.040f, 0.040f);
    glVertex2f(-0.036f, -0.010f);
    glVertex2f(-0.022f, 0.000f);

    glEnd();

    // ===== RIGHT ARM =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(0.028f, 0.050f);
    glVertex2f(0.040f, 0.040f);
    glVertex2f(0.036f, -0.010f);
    glVertex2f(0.022f, 0.000f);

    glEnd();

    // ===== LEFT LEG =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.6f); 

    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);
    glEnd();

    // ===== RIGHT LEG =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.6f);

    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);
    glEnd();

    // ===== LEFT SHOE =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);

    glEnd();

    // ===== RIGHT SHOE =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);

    glEnd();

    glPopMatrix();
}

void drawHuman3(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // ===== HEAD =====
    glColor3f(1.0f, 0.82f, 0.68f);
    drawCircle(0.0f, 0.09f, 0.018f, 50);

    // ===== NECK =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);

    glEnd();

    // ===== HAIR =====
    glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.05f, 1.0f); // blue hair

    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);

    glEnd();

    // ===== BODY / SHIRT =====
    glBegin(GL_POLYGON);
	glColor3f(0.6f, 0.3f, 0.7f); // purple shirt

    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);

    glEnd();

    // ===== LEFT ARM =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.028f, 0.050f);
    glVertex2f(-0.040f, 0.040f);
    glVertex2f(-0.036f, -0.010f);
    glVertex2f(-0.022f, 0.000f);

    glEnd();

    // ===== RIGHT ARM =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(0.028f, 0.050f);
    glVertex2f(0.040f, 0.040f);
    glVertex2f(0.036f, -0.010f);
    glVertex2f(0.022f, 0.000f);

    glEnd();

    // ===== LEFT LEG =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.6f); 

    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);
    glEnd();

    // ===== RIGHT LEG =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.6f);

    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);
    glEnd();

    // ===== LEFT SHOE =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);

    glEnd();

    // ===== RIGHT SHOE =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);

    glEnd();

    glPopMatrix();
}

void drawHuman4(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // ===== HEAD =====
    glColor3f(1.0f, 0.82f, 0.68f);
    drawCircle(0.0f, 0.09f, 0.018f, 50);

    // ===== NECK =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);

    glEnd();

    // ===== HAIR =====
    glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.05f, 0.95f); // pink hair

    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);

    glEnd();

    // ===== BODY / SHIRT =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.05f, 0.95f); // green shirt

    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);

    glEnd();

    // ===== LEFT ARM =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.028f, 0.050f);
    glVertex2f(-0.040f, 0.040f);
    glVertex2f(-0.036f, -0.010f);
    glVertex2f(-0.022f, 0.000f);

    glEnd();

    // ===== RIGHT ARM =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(0.028f, 0.050f);
    glVertex2f(0.040f, 0.040f);
    glVertex2f(0.036f, -0.010f);
    glVertex2f(0.022f, 0.000f);

    glEnd();

    // ===== LEFT LEG =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); 

    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);
    glEnd();

    // ===== RIGHT LEG =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);
    glEnd();

    // ===== LEFT SHOE =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 1.0f);

    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);

    glEnd();

    // ===== RIGHT SHOE =====
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 1.0f); 

    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);

    glEnd();

    glPopMatrix();
}