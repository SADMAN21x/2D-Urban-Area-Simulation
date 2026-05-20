#include<windows.h>
#include <GL/freeglut.h>
#define PI 3.1416
#include<math.h>
#include "functions.h"

void CC(float x, float y, float ra, int r, int g, int b) {
    int i;
    GLfloat p1 = x; GLfloat q1 = y; GLfloat r1 = ra;
    int tringle2 = 200;
    GLfloat tp2 = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(r, g, b);
    glVertex2f(p1, q1);

    for (i = 0;i <= tringle2; i++) {
        glVertex2f(
            p1 + (r1 * cos(i * tp2 / tringle2)),
            q1 + (r1 * sin(i * tp2 / tringle2))
        );
    }
    glEnd();
}

void drawSun(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);

    glColor4f(1.0f, 0.9f, 0.3f, 1.0f);
    glVertex2f(cx, cy);

    for (int i = 0; i <= 100; i++) {
        float angle = 2 * 3.1416f * i / 100;

        glColor4f(1.0f, 0.6f, 0.2f, 0.0f);

        float x = cx + cos(angle) * r;
        float y = cy + sin(angle) * r;
        glVertex2f(x, y);
    }
    glEnd();
}

void drawRect(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawQuads(float x1, float y1, float x2, float y2, double r, double g, double b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawCircle(float center_x, float center_y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(center_x, center_y);
    for (int i = 0; i <= segments; i++) {
        float angle = 2 * PI * i / segments;
        glVertex2f(center_x + radius * (float)cos(angle), center_y + radius * (float)sin(angle));
    }
    glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0;i <= seg;i++) {
        float a = 2.0f * 3.14159f * i / seg;
        glVertex2f(cx + cosf(a) * rx, cy + sinf(a) * ry);
    }
    glEnd();
}