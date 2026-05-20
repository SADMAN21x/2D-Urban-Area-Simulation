#include<windows.h>
#include <GL/glut.h>
#include<math.h>
#include "sadman2.h"
#include "functions.h"
#include "fahim.h"
#define PI 3.1416

float wheelAngle = 0.0f;

float parkh1x = -0.5f;
float parkh1y = -0.2f;
float parkh2x = 0.0f;
float parkh2y = -0.4f;
float parkh3x = 0.5f;
float parkh3y = -0.1f;

float parkh1speedX = 0.002f;
float parkh1speedY = 0.001f;

float parkh2speedX = -0.0015f;
float parkh2speedY = 0.002f;

float parkh3speedX = 0.001f;
float parkh3speedY = -0.002f;

//faisal vai er update code for park scene
float sd_skyR1 = 0.50f, sd_skyG1 = 0.85f, sd_skyB1 = 1.00f; // top
float sd_skyR2 = 0.80f, sd_skyG2 = 0.93f, sd_skyB2 = 1.00f; // bottom
bool  sd_isNight = false;
float sd_cloudX = 0.0f;

void cabin(float x, float y, float r, float red, float green, float blue)
{
    // upper white half
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    for (int i = 0; i <= 50; i++)
    {
        float angle = PI * i / 50.0f;

        glVertex2f(
            x + cos(angle) * r,
            y + sin(angle) * r
        );
    }
    glEnd();
    // lower colorful half
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    for (int i = 50; i <= 100; i++)
    {
        float angle = PI * i / 50.0f;

        glVertex2f(
            x + cos(angle) * r,
            y + sin(angle) * r
        );
    }
    glEnd();
}

void greenField()
{
	glBegin(GL_QUADS);
    glColor3f(0.2, 0.8, 0.2);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, 0.4);
    glVertex2f(-1.0, 0.4);
    glEnd();
}

//void parksky() {
//
//    glBegin(GL_QUADS);
//    glColor3f(0.4f, 0.7f, 1.0f);
//    glVertex2f(-1.0f, 0.4f);
//    glVertex2f(1.0f, 0.4f);
//    glColor3f(0.75f, 0.9f, 1.0f);
//    glVertex2f(1.0f, 1.0f);
//    glVertex2f(-1.0f, 1.0f);
//
//    glEnd();
//}

void parksky()
{
    glBegin(GL_QUADS);
    glColor3f(sd_skyR1, sd_skyG1, sd_skyB1);
    glVertex2f(-1.0f, 0.4f);
    glVertex2f(1.0f, 0.4f);
    glColor3f(sd_skyR2, sd_skyG2, sd_skyB2);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
}

void tree() {

    //tree body
    glBegin(GL_QUADS);
    glColor3f(0.45, 0.22, 0.05);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.47f, -0.5f);
    glVertex2f(0.47f, -0.3f);
    glVertex2f(0.5f, -0.3f);
    glEnd();

    //grass
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.55f, 0.0f);
    // grass 1
    glVertex2f(0.45f, -0.50f);
    glVertex2f(0.46f, -0.45f);
    glVertex2f(0.47f, -0.50f);
    // grass 2
    glVertex2f(0.465f, -0.50f);
    glVertex2f(0.475f, -0.44f);
    glVertex2f(0.485f, -0.50f);
    // grass 3
    glVertex2f(0.48f, -0.50f);
    glVertex2f(0.49f, -0.46f);
    glVertex2f(0.50f, -0.50f);
    // grass 4
    glVertex2f(0.495f, -0.50f);
    glVertex2f(0.505f, -0.45f);
    glVertex2f(0.515f, -0.50f);
    glEnd();

    // stone 1
    glColor3f(0.6f, 0.6f, 0.6f);
    drawCircle(0.455f, -0.515f, 0.012f, 100);

    // stone 2
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(0.485f, -0.525f, 0.010f, 100);

    // stone 3
    glColor3f(0.5f, 0.5f, 0.5f);
    drawCircle(0.515f, -0.515f, 0.013f, 100);

    // stone 4
    glColor3f(0.75f, 0.75f, 0.75f);
    drawCircle(0.50f, -0.54f, 0.009f, 100);

    //tree leaves
    glColor3f(0.65f, 0.8f, 0.2f);
    drawCircle(0.485f, -0.25f, 0.1f, 100);
    glColor3f(0.65f, 0.8f, 0.2f);
    drawCircle(0.45f, -0.15f, 0.09f, 100);
    glColor3f(0.65f, 0.8f, 0.2f);
    drawCircle(0.52f, -0.15f, 0.09f, 100);
    glColor3f(0.65f, 0.8f, 0.2f);
    drawCircle(0.55f, -0.31f, 0.07f, 100);
    glColor3f(0.65f, 0.8f, 0.2f);
    drawCircle(0.41f, -0.31f, 0.07f, 100);

    // white flower
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.47f, -0.18f, 0.012f, 100);
    drawCircle(0.49f, -0.18f, 0.012f, 100);
    drawCircle(0.48f, -0.16f, 0.012f, 100);
    drawCircle(0.48f, -0.20f, 0.012f, 100);

    glColor3f(1.0f, 0.8f, 0.0f);
    drawCircle(0.48f, -0.18f, 0.010f, 100);

    // pink flower
    glColor3f(1.0f, 0.4f, 0.7f);
    drawCircle(0.52f, -0.20f, 0.012f, 100);
    drawCircle(0.54f, -0.20f, 0.012f, 100);
    drawCircle(0.53f, -0.18f, 0.012f, 100);
    drawCircle(0.53f, -0.22f, 0.012f, 100);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.53f, -0.20f, 0.010f, 100);

    // red flower
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(0.45f, -0.28f, 0.011f, 100);
    drawCircle(0.47f, -0.28f, 0.011f, 100);
    drawCircle(0.46f, -0.26f, 0.011f, 100);
    drawCircle(0.46f, -0.30f, 0.011f, 100);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.46f, -0.28f, 0.009f, 100);

    // small flower
    glColor3f(0.8f, 0.5f, 1.0f);
    drawCircle(0.51f, -0.11f, 0.010f, 100);
    drawCircle(0.525f, -0.11f, 0.010f, 100);
    drawCircle(0.517f, -0.095f, 0.010f, 100);
    drawCircle(0.517f, -0.125f, 0.010f, 100);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.517f, -0.11f, 0.008f, 100);
}

void tree2() {

    //tree body
    glBegin(GL_QUADS);
    glColor3f(0.65, 0.40, 0.20);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.47f, -0.5f);
    glVertex2f(-0.47f, -0.3f);
    glVertex2f(-0.5f, -0.3f);
    glEnd();

    //tree leaves
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.55f, 0.15f);
    glVertex2f(-0.535f, -0.3f);
    glVertex2f(-0.535f, -0.1f);
    glVertex2f(-0.505f, 0.0f);
    glVertex2f(-0.465f, 0.0f);
    glVertex2f(-0.435f, -0.1f);
    glVertex2f(-0.435f, -0.3f);
    glEnd();

    glColor3f(0.2f, 0.55f, 0.15f);
    drawCircle(-0.435f, -0.3f, 0.01f, 100);
    drawCircle(-0.435f, -0.28f, 0.01f, 100);
    drawCircle(-0.435f, -0.26f, 0.01f, 100);
    drawCircle(-0.435f, -0.24f, 0.01f, 100);
    drawCircle(-0.435f, -0.22f, 0.01f, 100);
    drawCircle(-0.435f, -0.20f, 0.01f, 100);
    drawCircle(-0.435f, -0.18f, 0.01f, 100);
    drawCircle(-0.435f, -0.16f, 0.01f, 100);
    drawCircle(-0.435f, -0.14f, 0.01f, 100);
    drawCircle(-0.435f, -0.12f, 0.01f, 100);
    drawCircle(-0.435f, -0.10f, 0.01f, 100);

    drawCircle(-0.535f, -0.30f, 0.01f, 100);
    drawCircle(-0.535f, -0.28f, 0.01f, 100);
    drawCircle(-0.535f, -0.26f, 0.01f, 100);
    drawCircle(-0.535f, -0.24f, 0.01f, 100);
    drawCircle(-0.535f, -0.22f, 0.01f, 100);
    drawCircle(-0.535f, -0.20f, 0.01f, 100);
    drawCircle(-0.535f, -0.18f, 0.01f, 100);
    drawCircle(-0.535f, -0.16f, 0.01f, 100);
    drawCircle(-0.535f, -0.14f, 0.01f, 100);
    drawCircle(-0.535f, -0.12f, 0.01f, 100);
    drawCircle(-0.535f, -0.10f, 0.01f, 100);

    drawCircle(-0.535f, -0.308f, 0.01f, 100);
    drawCircle(-0.525f, -0.308f, 0.01f, 100);
    drawCircle(-0.515f, -0.308f, 0.01f, 100);
    drawCircle(-0.505f, -0.308f, 0.01f, 100);
    drawCircle(-0.495f, -0.308f, 0.01f, 100);
    drawCircle(-0.485f, -0.308f, 0.01f, 100);
    drawCircle(-0.475f, -0.308f, 0.01f, 100);
    drawCircle(-0.465f, -0.308f, 0.01f, 100);
    drawCircle(-0.455f, -0.308f, 0.01f, 100);
    drawCircle(-0.445f, -0.308f, 0.01f, 100);
    drawCircle(-0.435f, -0.308f, 0.01f, 100);

    drawCircle(-0.535f, -0.10f, 0.01f, 100);
    drawCircle(-0.530f, -0.08f, 0.01f, 100);
    drawCircle(-0.525f, -0.06f, 0.01f, 100);
    drawCircle(-0.520f, -0.04f, 0.01f, 100);
    drawCircle(-0.515f, -0.02f, 0.01f, 100);
    drawCircle(-0.505f, 0.00f, 0.01f, 100);

    drawCircle(-0.505f, 0.00f, 0.01f, 100);
    drawCircle(-0.495f, 0.00f, 0.01f, 100);
    drawCircle(-0.485f, 0.00f, 0.01f, 100);
    drawCircle(-0.475f, 0.00f, 0.01f, 100);
    drawCircle(-0.465f, 0.00f, 0.01f, 100);

    drawCircle(-0.465f, 0.00f, 0.01f, 100);
    drawCircle(-0.460f, -0.02f, 0.01f, 100);
    drawCircle(-0.455f, -0.04f, 0.01f, 100);
    drawCircle(-0.450f, -0.06f, 0.01f, 100);
    drawCircle(-0.445f, -0.08f, 0.01f, 100);
    drawCircle(-0.435f, -0.10f, 0.01f, 100);

}

void tree3() {

    //tree body
    glBegin(GL_QUADS);
    glColor3f(0.45, 0.22, 0.05);
    glVertex2f(-0.27f, -0.5f);
    glVertex2f(-0.27f, -0.3f);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(-0.3f, -0.5f);
    glEnd();

    //tree leaves
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.6f, 0.15f);
    glVertex2f(-0.23f, -0.3f);
    glVertex2f(-0.285f, -0.15f);
    glVertex2f(-0.34f, -0.3f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.6f, 0.15f);
    glVertex2f(-0.23f, -0.20f);
    glColor3f(0.65f, 0.8f, 0.2f);
    glVertex2f(-0.285f, -0.05f);
    glColor3f(0.65f, 0.8f, 0.2f);
    glVertex2f(-0.34f, -0.20f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.65f, 0.8f, 0.2f);
    glVertex2f(-0.23f, -0.10f);
    glColor3f(1.0f, 0.8f, 0.2f);
    glVertex2f(-0.285f, 0.05f);
    glColor3f(1.0f, 0.8f, 0.2f);
    glVertex2f(-0.34f, -0.10f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    // grass 1
    glVertex2f(-0.33f, -0.50f);
    glVertex2f(-0.325f, -0.46f);
    glVertex2f(-0.32f, -0.50f);
    // grass 2
    glVertex2f(-0.315f, -0.50f);
    glVertex2f(-0.31f, -0.45f);
    glVertex2f(-0.305f, -0.50f);
    // grass 3
    glVertex2f(-0.30f, -0.50f);
    glVertex2f(-0.295f, -0.46f);
    glVertex2f(-0.29f, -0.50f);
    // grass 4
    glVertex2f(-0.285f, -0.50f);
    glVertex2f(-0.28f, -0.44f);
    glVertex2f(-0.275f, -0.50f);
    // grass 5
    glVertex2f(-0.27f, -0.50f);
    glVertex2f(-0.265f, -0.46f);
    glVertex2f(-0.26f, -0.50f);
    // grass 6
    glVertex2f(-0.255f, -0.50f);
    glVertex2f(-0.25f, -0.45f);
    glVertex2f(-0.245f, -0.50f);
    glEnd();
}

void flower() {

    // white flower
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.47f, -0.18f, 0.012f, 100);
    drawCircle(0.49f, -0.18f, 0.012f, 100);
    drawCircle(0.48f, -0.16f, 0.012f, 100);
    drawCircle(0.48f, -0.20f, 0.012f, 100);

    glColor3f(1.0f, 0.8f, 0.0f);
    drawCircle(0.48f, -0.18f, 0.010f, 100);

}

void flower2() {

    // pink flower
    glColor3f(1.0f, 0.4f, 0.7f);
    drawCircle(0.52f, -0.20f, 0.012f, 100);
    drawCircle(0.54f, -0.20f, 0.012f, 100);
    drawCircle(0.53f, -0.18f, 0.012f, 100);
    drawCircle(0.53f, -0.22f, 0.012f, 100);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.53f, -0.20f, 0.010f, 100);

}

void flower3() {

    // red flower
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(0.45f, -0.28f, 0.011f, 100);
    drawCircle(0.47f, -0.28f, 0.011f, 100);
    drawCircle(0.46f, -0.26f, 0.011f, 100);
    drawCircle(0.46f, -0.30f, 0.011f, 100);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.46f, -0.28f, 0.009f, 100);
}

void pathway()
{
    // curved pathway

    glColor3f(0.75f, 0.65f, 0.45f);

    glBegin(GL_POLYGON);

    glVertex2f(-0.90f, -1.00f);
    glVertex2f(-0.75f, -0.85f);
    glVertex2f(-0.55f, -0.70f);
    glVertex2f(-0.35f, -0.55f);
    glVertex2f(-0.10f, -0.40f);

    glVertex2f(0.10f, -0.35f);
    glVertex2f(0.25f, -0.38f);
    glVertex2f(0.40f, -0.48f);
    glVertex2f(0.55f, -0.62f);
    glVertex2f(0.75f, -0.82f);
    glVertex2f(0.90f, -1.00f);

    glVertex2f(0.72f, -1.00f);
    glVertex2f(0.58f, -0.85f);
    glVertex2f(0.42f, -0.70f);
    glVertex2f(0.28f, -0.60f);
    glVertex2f(0.12f, -0.52f);

    glVertex2f(-0.05f, -0.50f);
    glVertex2f(-0.22f, -0.58f);
    glVertex2f(-0.40f, -0.72f);
    glVertex2f(-0.58f, -0.86f);
    glVertex2f(-0.72f, -1.00f);

    glEnd();

    // pathway border

    glLineWidth(3.0f);

    glColor3f(0.55f, 0.40f, 0.20f);

    glBegin(GL_LINE_LOOP);

    glVertex2f(-0.90f, -1.00f);
    glVertex2f(-0.75f, -0.85f);
    glVertex2f(-0.55f, -0.70f);
    glVertex2f(-0.35f, -0.55f);
    glVertex2f(-0.10f, -0.40f);

    glVertex2f(0.10f, -0.35f);
    glVertex2f(0.25f, -0.38f);
    glVertex2f(0.40f, -0.48f);
    glVertex2f(0.55f, -0.62f);
    glVertex2f(0.75f, -0.82f);
    glVertex2f(0.90f, -1.00f);

    glVertex2f(0.72f, -1.00f);
    glVertex2f(0.58f, -0.85f);
    glVertex2f(0.42f, -0.70f);
    glVertex2f(0.28f, -0.60f);
    glVertex2f(0.12f, -0.52f);

    glVertex2f(-0.05f, -0.50f);
    glVertex2f(-0.22f, -0.58f);
    glVertex2f(-0.40f, -0.72f);
    glVertex2f(-0.58f, -0.86f);
    glVertex2f(-0.72f, -1.00f);

    glEnd();
}

void bench() {


    glBegin(GL_QUADS);
    glColor3f(0.82f, 0.60f, 0.35f);
    glVertex2f(-0.95f, -0.65f);
    glVertex2f(-0.80f, -0.55f);
    glVertex2f(-0.785f, -0.66f);
    glVertex2f(-0.935f, -0.76f);  //upper
    glEnd();

    //upper bench design
    glBegin(GL_LINES);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.9425f, -0.72f);
    glVertex2f(-0.79f, -0.62f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.9485f, -0.69f);
    glVertex2f(-0.795f, -0.59f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.85f, -0.77f);
    glVertex2f(-0.7f, -0.67f);
    glVertex2f(-0.785f, -0.66f);
    glVertex2f(-0.935f, -0.76f); //lower
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.82f, 0.60f, 0.35f);
    glVertex2f(-0.935f, -0.76f);
    glVertex2f(-0.935f, -0.77f);
    glVertex2f(-0.85f, -0.78f);
    glVertex2f(-0.85f, -0.77f); //lower border
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.82f, 0.60f, 0.35f);
    glVertex2f(-0.85f, -0.78f);
    glVertex2f(-0.85f, -0.77f);
    glVertex2f(-0.7f, -0.67f);
    glVertex2f(-0.7f, -0.68f); //lower border
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.925f, -0.77f);
    glVertex2f(-0.925f, -0.80f);
    glVertex2f(-0.915f, -0.805f);
    glVertex2f(-0.915f, -0.77f); //left leg
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.84f, -0.77f);
    glVertex2f(-0.84f, -0.825f);
    glVertex2f(-0.85f, -0.820f);
    glVertex2f(-0.85f, -0.78f); //right leg
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.70f, -0.68f);
    glVertex2f(-0.70f, -0.735f);
    glVertex2f(-0.71f, -0.73f);
    glVertex2f(-0.7115f, -0.69f); //upper right leg
    glEnd();

}

void nagordola() {

    //middle circle
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle(0.55f, -0.10f, 0.05f, 100);

    // left stand
    glBegin(GL_TRIANGLES);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(0.45f, -0.50f);
    glVertex2f(0.50f, -0.50f);
    glVertex2f(0.55f, -0.10f);
    glEnd();

    // right stand
    glBegin(GL_TRIANGLES);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(0.60f, -0.50f);
    glVertex2f(0.65f, -0.50f);
    glVertex2f(0.55f, -0.10f);
    glEnd();

    // bottom base
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(0.40f, -0.50f);
    glVertex2f(0.70f, -0.50f);
    glVertex2f(0.70f, -0.52f);
    glVertex2f(0.40f, -0.52f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.55f, -0.10f, 0.0f);
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.55f, 0.10f, 0.0f);

    //main circle
    float centerX = 0.55f;
    float centerY = -0.10f;
    float outerRadius = 0.30f;
    float innerRadius = 0.24f;

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0f, 0.45f, 0.55f);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * PI * i / 100;
        glVertex2f(
            centerX + cos(angle) * outerRadius,
            centerY + sin(angle) * outerRadius  // outer circle point
        );
        glVertex2f(
            centerX + cos(angle) * innerRadius,
            centerY + sin(angle) * innerRadius  // inner circle point
        );
    }
    glEnd();

    //2 circle connections
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(0.25f, 0.25f, 0.25f);
    // top
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.55f, 0.14f);
    // bottom
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.55f, -0.34f);
    // left
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.31f, -0.10f);
    // right
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.79f, -0.10f);
    // top-left
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.38f, 0.07f);
    // top-right
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.72f, 0.07f);
    // bottom-left
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.38f, -0.27f);
    // bottom-right
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.72f, -0.27f);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.55f, -0.10f, 0.02f, 100); //middile circle design
    glPopMatrix();

    // cabin design

    cabin(0.55f, 0.20f, 0.04f, 1.0f, 0.0f, 0.0f);     // top
    cabin(0.55f, -0.40f, 0.04f, 1.0f, 0.0f, 0.0f);    // bottom
    cabin(0.25f, -0.10f, 0.04f, 1.0f, 0.0f, 0.0f);    // left
    cabin(0.85f, -0.10f, 0.04f, 1.0f, 0.0f, 0.0f);    // right
    cabin(0.34f, 0.11f, 0.04f, 1.0f, 0.0f, 0.0f);    // top-left
    cabin(0.76f, 0.11f, 0.04f, 1.0f, 0.0f, 0.0f);    // top-right
    cabin(0.34f, -0.31f, 0.04f, 1.0f, 0.0f, 0.0f);    // bottom-left
    cabin(0.76f, -0.31f, 0.04f, 1.0f, 0.0f, 0.0f);    // bottom-right

    glPopMatrix();
}

void Fence() {

    glBegin(GL_QUADS);
    glColor3f(0.60f, 0.35f, 0.15f);
    // upper bar
    glVertex2f(-0.40f, -0.05f);
    glVertex2f(0.40f, -0.05f);
    glVertex2f(0.40f, -0.03f);
    glVertex2f(-0.40f, -0.03f);
    // lower bar
    glVertex2f(-0.40f, -0.11f);
    glVertex2f(0.40f, -0.11f);
    glVertex2f(0.40f, -0.09f);
    glVertex2f(-0.40f, -0.09f);
    glEnd();

    glColor3f(0.50f, 0.25f, 0.08f);
    for (float x = -0.40f; x <= 0.40f; x += 0.06f)
    {
        glBegin(GL_POLYGON);
        glVertex2f(x, -0.15f);
        glVertex2f(x + 0.02f, -0.15f);
        glVertex2f(x + 0.02f, 0.00f);
        glVertex2f(x + 0.01f, 0.03f);
        glVertex2f(x, 0.00f);
        glEnd();
    }
}

void manus()
{
    glPushMatrix();
    //glTranslatef(x, y, 0.0f);

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

void manus2()
{
    glPushMatrix();
    //glTranslatef(x, y, 0.0f);

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

void manus3()
{
    glPushMatrix();
    //glTranslatef(x, y, 0.0f);

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

// -- Sun / Moon --
void sd_drawCelestial() {
    if (!sd_isNight) {
        // Sun with gradient glow
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (int h = 6;h >= 1;h--) { glColor4f(1.0f, 0.85f, 0.2f, 0.025f * h); drawCircle(-0.75f, 0.80f, 0.05f + h * 0.022f, 20); }
        glDisable(GL_BLEND);
        glColor3f(1.0f, 0.92f, 0.15f); drawCircle(-0.75f, 0.80f, 0.055f, 36);
        glColor3f(1.0f, 0.98f, 0.65f); drawCircle(-0.76f, 0.81f, 0.022f, 18);
    }
    else {
        // Moon
        glColor3f(0.97f, 0.97f, 0.84f); drawCircle(-0.75f, 0.80f, 0.055f, 30);
        glColor3f(0.10f, 0.10f, 0.22f); drawCircle(-0.73f, 0.82f, 0.044f, 30);
        // Stars
        glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        srand(42);
        for (int i = 0;i < 40;i++) {
            float sx = -1.0f + 2.0f * (rand() % 1000) / 1000.0f;
            float sy = 0.35f + 0.65f * (rand() % 1000) / 1000.0f;
            float sa = 0.5f + 0.5f * sinf(wheelAngle * 0.05f + i * 0.7f);
            glColor4f(1.0f, 1.0f, 0.9f, sa);
            drawCircle(sx, sy, 0.005f, 6);
        }
        glDisable(GL_BLEND);
    }
}

// -- Clouds --
void sd_drawCloud(float bx, float by, float sc) {
    glPushMatrix(); glTranslatef(bx + sd_cloudX, by, 0); glScalef(sc, sc, 1.0f);
    float cr, cg, cb;
    if (sd_isNight) { cr = 0.22f;cg = 0.22f;cb = 0.32f; }
    else { cr = 0.98f;cg = 0.98f;cb = 1.00f; }
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(cr * 0.8f, cg * 0.8f, cb * 0.8f, 0.5f); drawEllipse(0.05f, -0.008f, 0.09f, 0.025f);
    glColor4f(cr, cg, cb, 1.0f);
    float puffs[][3] = { {0.0f,0.0f,0.05f},{0.045f,0.016f,0.065f},{0.095f,0.004f,0.055f},{0.07f,-0.014f,0.036f},{-0.025f,-0.009f,0.034f} };
    for (auto& p : puffs) drawCircle(p[0], p[1], p[2], 22);
    glDisable(GL_BLEND);
    glPopMatrix();
}



void displaySadman2()
{
    glClearColor(0.75f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    parksky();
    sd_drawCelestial();
    sd_drawCloud(-0.30f, 0.72f, 1.00f);
    sd_drawCloud(0.30f, 0.78f, 0.80f);
    sd_drawCloud(0.72f, 0.68f, 0.70f);
    greenField();
    pathway();

	//fence
    glPushMatrix();
    glTranslatef(-0.6f, 0.5f, 0.0f);
    Fence();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    Fence();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6f, 0.5f, 0.0f);
    Fence();
    glPopMatrix();

    //manus
    glPushMatrix();
    glTranslatef(parkh1x, parkh1y, 0.0f);
    manus();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(parkh2x, parkh2y, 0.0f);
    manus2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(parkh3x, parkh3y, 0.0f);
    manus3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    bench();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.05f, 0.55f, 0.0f);
    bench();
    glPopMatrix();

    //tree3 
    glPushMatrix();
    glTranslatef(0.55f, 0.48f, 0.0f);
    tree3();
    glPopMatrix();

    //tree more
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.65f, -0.35f, 0.0f);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.32f, 0.10f, 0.0f);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.995f, 0.6f, 0.0f);
    tree();
    glPopMatrix();

    //tree2 more
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    tree2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.35f, 0.18f, 0.0f);
    tree2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.30f, 0.2f, 0.0f);
    tree2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55f, -0.12f, 0.0f);
    tree2();
    glPopMatrix();

    //tree3 more
    glPushMatrix();
    glTranslatef(-0.30f, -0.20f, 0.0f);
    tree3();
    glPopMatrix();

    //flower more
    glPushMatrix();
    glTranslatef(-0.90f, -0.20f, 0.0f);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.70f, -0.25f, 0.0f);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.50f, -0.22f, 0.0f);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.30f, -0.27f, 0.0f);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.10f, -0.23f, 0.0f);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.10f, -0.28f, 0.0f);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.30f, -0.24f, 0.0f);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.50f, -0.26f, 0.0f);
    flower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.70f, -0.22f, 0.0f);
    flower();
    glPopMatrix();

    //flower2 more
    glPushMatrix();
    glTranslatef(-0.90f, 0.45f, 0.0f);
    flower2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.95f, -0.50f, 0.0f);
    flower2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.40f, -0.47f, 0.0f);
    flower2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.20f, -0.52f, 0.0f);
    flower2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.00f, -0.48f, 0.0f);
    flower2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.20f, -0.53f, 0.0f);
    flower2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.40f, -0.49f, 0.0f);
    flower2();
    glPopMatrix();

    //flower3 more
    glPushMatrix();
    glTranslatef(0.35f, -0.19f, 0.0f);
    flower3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55f, -0.23f, 0.0f);
    flower3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75f, -0.18f, 0.0f);
    flower3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.85f, -0.18f, 0.0f);
    flower3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15f, 0.5f, 0.0f);
    nagordola();
    glPopMatrix();

    //glFlush();
}

void keyboardSadman2(unsigned char key, int x, int y) {
    
    switch (key) {
    case 'v': case 'V':
        sd_isNight = !sd_isNight;
        if (sd_isNight) {
            sd_skyR1 = 0.02f; sd_skyG1 = 0.02f; sd_skyB1 = 0.08f;
            sd_skyR2 = 0.05f; sd_skyG2 = 0.05f; sd_skyB2 = 0.12f;
        }
        else {
            sd_skyR1 = 0.50f; sd_skyG1 = 0.85f; sd_skyB1 = 1.00f;
            sd_skyR2 = 0.80f; sd_skyG2 = 0.93f; sd_skyB2 = 1.00f;
        }
        break;
    }
}

void updateSadman2(int value)
{
    wheelAngle -= 1.0f;

    // cloud drift
    sd_cloudX += 0.0003f;
    if (sd_cloudX > 0.6f) sd_cloudX = -0.6f;

    parkh1x += parkh1speedX;
    parkh1y += parkh1speedY;
    parkh2x += parkh2speedX;
    parkh2y += parkh2speedY;
    parkh3x += parkh3speedX;
    parkh3y += parkh3speedY;

    if (parkh1x > 0.9f || parkh1x < -0.9f)
    {
        parkh1speedX = -parkh1speedX;
    }
    if (parkh1y > 0.3f || parkh1y < -0.9f)
    {
        parkh1speedY = -parkh1speedY;
    }
    if (parkh2x > 0.9f || parkh2x < -0.9f)
    {
        parkh2speedX = -parkh2speedX;
    }
    if (parkh2y > 0.3f || parkh2y < -0.9f)
    {
        parkh2speedY = -parkh2speedY;
    }

    if (parkh3x > 0.9f || parkh3x < -0.9f)
    {
        parkh3speedX = -parkh3speedX;
    }
    if (parkh3y > 0.3f || parkh3y < -0.9f)
    {
        parkh3speedY = -parkh3speedY;
    }

    if (rand() % 200 == 0)
    {
        parkh1speedX = ((rand() % 5) - 2) * 0.001f;
        parkh1speedY = ((rand() % 5) - 2) * 0.001f;
    }
    if (rand() % 200 == 0)
    {
        parkh2speedX = ((rand() % 5) - 2) * 0.001f;
        parkh2speedY = ((rand() % 5) - 2) * 0.001f;
    }
    if (rand() % 200 == 0)
    {
        parkh3speedX = ((rand() % 5) - 2) * 0.001f;
        parkh3speedY = ((rand() % 5) - 2) * 0.001f;
    }

    //glutPostRedisplay();
    //glutTimerFunc(16, updateSadman2, 0);
}

//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowSize(1500, 1000);
//    glutCreateWindow("Park Scene");
//
//    glClearColor(0.5, 0.85, 1.0, 1.0);
//
//    glutDisplayFunc(displaySadman2);
//    glutKeyboardFunc(keyboardSadman2);
//    glutTimerFunc(16, updateSadman2, 0);
//    glutMainLoop();
//
//    return 0;
//}



