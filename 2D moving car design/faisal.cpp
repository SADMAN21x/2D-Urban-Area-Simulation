#include<windows.h>
#include <GL/freeglut.h>
#include <math.h>
#include "faisal.h"
#include "functions.h"

#define PI 3.1416

GLfloat birdX = -1.0f;
GLfloat planeX = 0.0f;
GLfloat planeY = 0.0f;

//void drawBird(float x, float y) {
//    glColor3ub(0, 0, 0);
//
//    glBegin(GL_LINES);
//    glVertex2f(x, y);
//    glVertex2f(x - 0.05f, y + 0.03f);
//
//    glVertex2f(x, y);
//    glVertex2f(x + 0.05f, y + 0.03f);
//    glEnd();
//}

// birdFlap advances each frame to animate wing beat
int birdFlap = 0;

void drawBird(float x, float y, float flapOffset) {
    // Wing flap: sine wave gives smooth up/down motion per bird
    float flap = sinf((birdFlap * 0.18f) + flapOffset) * 0.022f;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.6f);

    // Body: small dark oval
    glColor3ub(30, 30, 30);
    int segs = 12;
    glBegin(GL_POLYGON);
    for (int i = 0; i < segs; i++) {
        float a = 2.0f * PI * i / segs;
        glVertex2f(x + cosf(a) * 0.012f, y + sinf(a) * 0.006f);
    }
    glEnd();

    // Head: small circle slightly ahead
    glColor3ub(30, 30, 30);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 10; i++) {
        float a = 2.0f * PI * i / 10;
        glVertex2f(x + 0.014f + cosf(a) * 0.007f, y + 0.003f + sinf(a) * 0.007f);
    }
    glEnd();

    // Beak
    glColor3ub(180, 120, 20);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 0.021f, y + 0.004f);
    glVertex2f(x + 0.030f, y + 0.002f);
    glVertex2f(x + 0.021f, y - 0.001f);
    glEnd();

    // Left wing (curves upward when flapping up)
    glColor3ub(25, 25, 25);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    glVertex2f(x - 0.012f, y + flap * 0.3f);
    glVertex2f(x - 0.025f, y + flap * 0.7f);
    glVertex2f(x - 0.038f, y + flap);
    glVertex2f(x - 0.028f, y + flap * 0.5f);
    glVertex2f(x - 0.010f, y);
    glEnd();

    // Right wing
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    glVertex2f(x + 0.010f, y + flap * 0.3f);
    glVertex2f(x + 0.022f, y + flap * 0.7f);
    glVertex2f(x + 0.034f, y + flap);
    glVertex2f(x + 0.024f, y + flap * 0.5f);
    glVertex2f(x + 0.008f, y);
    glEnd();

    // Tail feathers
    glColor3ub(20, 20, 20);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.012f, y);
    glVertex2f(x - 0.026f, y + 0.008f);
    glVertex2f(x - 0.026f, y - 0.008f);
    glEnd();

    glLineWidth(1.0f);
    glDisable(GL_BLEND);
}

void drawPlane() {

    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);

    // Left body
    glVertex2f(-0.6f, 0.1f);
    glVertex2f(0.6f, 0.1f);

    // Curved front (semi-circle)
    for (int i = 0; i <= 20; i++) {
        float angle = PI / 2 - (PI * i / 20); // top → bottom curve
        float x = 0.6f + 0.2f * cos(angle);
        float y = 0.0f + 0.1f * sin(angle);
        glVertex2f(x, y);
    }

    // Bottom body
    glVertex2f(0.6f, -0.1f);
    glVertex2f(-0.6f, -0.1f);

    glEnd();

    glColor3ub(200, 200, 200);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2f, 0.1f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(-0.3f, 0.5f);

    glVertex2f(-0.2f, -0.1f);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(-0.3f, -0.5f);
    glEnd();

    glColor3ub(255, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, 0.1f);
    glVertex2f(-0.8f, 0.4f);
    glVertex2f(-0.8f, 0.1f);
    glEnd();

    // Windows
    drawCircle(-0.4f, 0.0f, 0.04f, 100);
    drawCircle(-0.2f, 0.0f, 0.04f, 100);
    drawCircle(0.0f, 0.0f, 0.04f, 100);
    drawCircle(0.2f, 0.0f, 0.04f, 100);
    drawCircle(0.4f, 0.0f, 0.04f, 100);
}