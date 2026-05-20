#include<windows.h>
#include <GL/freeglut.h>
#define PI 3.1416
#include<math.h>
#include "sadman.h"
#include "sadman2.h"
#include "faisal.h"
#include "faisal2.h"
#include "safkat.h"
#include "functions.h"
#include "fahim.h"
#include <stdlib.h>
#include <time.h>

int currentScene = 1;

GLfloat tx = 0.4;
GLfloat ty = -0.10;
GLfloat tx1 = 0.4;
GLfloat ty1 = -0.10;
GLfloat tx2 = -0.95;
GLfloat ty2 = 0.8;

float r = 0.2;
float g = 0.5;
float b = 0.8;

float r1 = 0.7;
float g1 = 0.9;
float b1 = 1.0;

float translateFlag = 0;

int isNight = 0;
bool rain = false;
float rainX[1000];
float rainY[1000];
float rainSpeed[1000];
float rainSpeedMultiplier = 1.0f;

float humanY = -0.02f;
float humanX = -1.2f;
int humanDirection = 0;// 0 = going down, 1 = going up
int humanMoving = 0;

float starScale = 1.0f;
float starScaleDir = 0.01f;

void drawSky() {
    glBegin(GL_QUADS);

    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);

    glColor3f(r, g, b);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);

    glEnd();
}

//update star funtion from fahim vai
void drawStars() {
    if (isNight != 1) return;   // only show at night

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ===== STAR 1 =====
    glPushMatrix();
    glTranslatef(-0.55f, 0.75f, 0.0f);
    glScalef(starScale, starScale, 1.0f);
    drawStar(0.0f, 0.0f, 0.02f);
    glPopMatrix();

    // ===== STAR 2 =====
    glPushMatrix();
    glTranslatef(0.10f, 0.82f, 0.0f);
    glScalef(starScale * 0.8f, starScale * 0.8f, 1.0f);
    drawStar(0.0f, 0.0f, 0.018f);
    glPopMatrix();

    // ===== STAR 3 =====
    glPushMatrix();
    glTranslatef(0.72f, 0.70f, 0.0f);
    glScalef(starScale * 1.2f, starScale * 1.2f, 1.0f);
    drawStar(0.0f, 0.0f, 0.025f);
    glPopMatrix();
    // ===== STAR 4 =====
    glPushMatrix();
    glTranslatef(-0.80f, 0.60f, 0.0f);
    glScalef(starScale * 0.9f, starScale * 0.9f, 1.0f);
    drawStar(0.0f, 0.0f, 0.018f);
    glPopMatrix();

    // ===== STAR 5 =====
    glPushMatrix();
    glTranslatef(-0.20f, 0.88f, 0.0f);
    glScalef(starScale * 1.1f, starScale * 1.1f, 1.0f);
    drawStar(0.0f, 0.0f, 0.015f);
    glPopMatrix();

    // ===== STAR 6 =====
    glPushMatrix();
    glTranslatef(0.45f, 0.78f, 0.0f);
    glScalef(starScale * 0.7f, starScale * 0.7f, 1.0f);
    drawStar(0.0f, 0.0f, 0.020f);
    glPopMatrix();

    // ===== STAR 7 =====
    glPushMatrix();
    glTranslatef(0.90f, 0.85f, 0.0f);
    glScalef(starScale * 1.3f, starScale * 1.3f, 1.0f);
    drawStar(0.0f, 0.0f, 0.017f);
    glPopMatrix();

    // ===== STAR 8 =====
    glPushMatrix();
    glTranslatef(0.00f, 0.65f, 0.0f);
    glScalef(starScale * 0.85f, starScale * 0.85f, 1.0f);
    drawStar(0.0f, 0.0f, 0.016f);
    glPopMatrix();

    glDisable(GL_BLEND);
}

void drawSunCloud() {
    glPushMatrix();
    glTranslatef(tx, ty, 0.0f);
    drawSun(0.3f, 0.0f, 0.1f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx1, ty1, 0.0f);
    CC(0.3f, 0.0f, 0.1f, 255, 255, 255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx2, ty2, 0.0f);
    CC(0.3f, 0.0f, 0.1f, 255, 255, 255);
    CC(0.4f, 0.0f, 0.065f, 255, 255, 255);
    CC(0.2f, 0.0f, 0.065f, 255, 255, 255);
    glPopMatrix();
}

void drawBackgroundCity() {
    drawRect(-1.0, 0.0, 0.4, 0.5, r, g, b);
    drawRect(-0.9, 0.0, 0.2, 0.65, r, g, b);
    drawRect(-0.85, 0.0, 0.05, 0.69, r, g, b);

    drawRect(-0.5, 0.0, 0.3, 0.6, r, g, b);
    drawRect(-0.45, 0.0, 0.2, 0.65, r, g, b);
    drawRect(-0.15, 0.0, 0.2, 0.6, r, g, b);

    drawRect(0.7, 0.0, 0.3, 0.4, r, g, b);
    drawRect(0.35, 0.0, 0.3, 0.5, r, g, b);

    drawRect(0.1, 0.0, 0.2, 0.55, r, g, b);
    drawRect(0.15, 0.0, 0.1, 0.65, r, g, b);
    drawRect(0.17, 0.0, 0.06, 0.68, r, g, b);

    drawTriangle(0.1, 0.55, 0.15, 0.55, 0.15, 0.60, r, g, b);
    drawTriangle(0.3, 0.55, 0.25, 0.55, 0.25, 0.60, r, g, b);
}

void drawGrass() {
    glBegin(GL_QUADS);
    glColor3f(0.25f, 0.61f, 0.04f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 0.02f);
    glVertex2f(-1.0f, 0.02f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();
}

void drawRoad() {
    glBegin(GL_QUADS);
    glColor3f(0.65f, 0.64f, 0.57f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.063f, 0.071f, 0.071f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(1.0f, -0.7f);
    glVertex2f(-1.0f, -0.7f);
    glVertex2f(-1.0f, -0.2f);   //main road
    glEnd();

    drawRect(0.9, -0.45, 0.2, 0.05, 1.0f, 1.0f, 1.0f);
    drawRect(0.6, -0.45, 0.2, 0.05, 1.0f, 1.0f, 1.0f);
    drawRect(0.3, -0.45, 0.2, 0.05, 1.0f, 1.0f, 1.0f);
    drawRect(0.0, -0.45, 0.2, 0.05, 1.0f, 1.0f, 1.0f);
    drawRect(-0.3, -0.45, 0.2, 0.05, 1.0f, 1.0f, 1.0f);
    drawRect(-0.6, -0.45, 0.2, 0.05, 1.0f, 1.0f, 1.0f);
}

void drawZebraCrossing() {
    drawRect(-0.95, -0.25, 0.3, 0.05, 1.0f, 1.0f, 1.0f);
    drawRect(-0.95, -0.35, 0.3, 0.05, 1.0f, 1.0f, 1.0f);
    drawRect(-0.95, -0.45, 0.3, 0.05, 1.0f, 1.0f, 1.0f);
    drawRect(-0.95, -0.55, 0.3, 0.05, 1.0f, 1.0f, 1.0f);
    drawRect(-0.95, -0.65, 0.3, 0.05, 1.0f, 1.0f, 1.0f);
}

void drawHouses() {

    // Far left house
    drawQuads(-0.95, 0.0, -0.65, 0.25, 1.0f, 0.8f, 0.3f);
    drawRect(-0.92, 0.0, 0.08, 0.15, 0.61f, 0.25f, 0.04f);
    drawRect(-0.78, 0.06, 0.1, 0.1, r1, g1, b1);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.78f, 0.06f);
    glVertex2f(-0.68f, 0.06f);
    glVertex2f(-0.68f, 0.16f);
    glVertex2f(-0.78f, 0.16f);
    glEnd();
    drawRect(-0.90f, 0.28f, 0.04f, 0.09f,
        0.4f, 0.1f, 0.1f);
    drawTriangle(-0.62, 0.25, -0.98, 0.25, -0.81, 0.38, 0.61f, 0.25f, 0.04f);
    drawTriangle(-0.65, 0.25, -0.95, 0.25, -0.81, 0.35, 1.0f, 0.8f, 0.3f);
    // fence posts
    for (float i = -0.90f; i < -0.55f; i += 0.04f)
    {
        drawRect(i, 0.0f, 0.015f, 0.08f,
            0.6f, 0.4f, 0.2f);
    }

    // horizontal fence bars
    drawRect(-0.90f, 0.05f, 0.45f, 0.01f,
        0.5f, 0.3f, 0.1f);

    drawRect(-0.90f, 0.025f, 0.45f, 0.01f,
        0.5f, 0.3f, 0.1f);

    // Second to left house
    drawQuads(-0.60, 0.0, -0.30, 0.45, 0.239f, 0.353f, 0.502f);
    drawQuads(-0.55, 0.35, -0.50, 0.40, r1, g1, b1);
    drawQuads(-0.40, 0.35, -0.35, 0.40, r1, g1, b1);
    drawQuads(-0.55, 0.30, -0.35, 0.32, 1.0f, 1.0f, 1.0f);
    drawQuads(-0.40, 0.25, -0.35, 0.20, r1, g1, b1);
    drawQuads(-0.55, 0.25, -0.50, 0.20, r1, g1, b1);
    drawQuads(-0.55, 0.15, -0.35, 0.17, 1.0f, 1.0f, 1.0f);
    drawQuads(-0.40, 0.05, -0.35, 0.10, r1, g1, b1);
    drawQuads(-0.55, 0.05, -0.50, 0.10, r1, g1, b1);
    drawQuads(-0.47, 0.00, -0.42, 0.10, 0.588f, 0.435f, 0.200f);

    // Third to left house
    drawQuads(-0.20, 0.0, 0.10, 0.4, 0.906f, 0.365f, 0.337f);
    drawQuads(-0.15, 0.35, -0.10, 0.30, r1, g1, b1);
    drawQuads(0.0, 0.35, 0.05, 0.30, r1, g1, b1);
    drawQuads(-0.15, 0.26, 0.05, 0.28, 1.0f, 1.0f, 1.0f);
    drawQuads(-0.15, 0.25, -0.10, 0.20, r1, g1, b1);
    drawQuads(0.0, 0.25, 0.05, 0.20, r1, g1, b1);
    drawQuads(-0.20, 0.15, 0.10, 0.17, 1.0f, 1.0f, 1.0f);
    drawTriangle(-0.23, 0.40, 0.13, 0.4, -0.05, 0.53, 1.0f, 1.0f, 1.0f);
    drawTriangle(-0.20, 0.40, 0.1, 0.4, -0.05, 0.5, 0.906f, 0.365f, 0.337f);

    // Hospital (right side)
    drawQuads(0.20, 0.0, 0.50, 0.45, 1.0f, 1.0f, 1.0f);
    drawQuads(0.25, 0.35, 0.30, 0.30, r1, g1, b1);
    drawQuads(0.25, 0.20, 0.30, 0.25, r1, g1, b1);
    drawQuads(0.45, 0.35, 0.40, 0.30, r1, g1, b1);
    drawQuads(0.45, 0.25, 0.40, 0.20, r1, g1, b1);

    // Red cross (hospital sign)
    drawQuads(0.32, 0.38, 0.37, 0.35, 1.0f, 0.0f, 0.0f);
    drawQuads(0.335, 0.40, 0.355, 0.33, 1.0f, 0.0f, 0.0f);
}

void drawRain()
{
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    for (int i = 0; i < 1000; i++)
    {
        // different brightness for depth effect
        if (i % 3 == 0)
            glColor3f(0.8f, 0.8f, 1.0f);
        else if (i % 3 == 1)
            glColor3f(0.6f, 0.6f, 1.0f);
        else
            glColor3f(0.4f, 0.4f, 0.9f);

        // slanted rain
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i] - 0.015f, rainY[i] - 0.06f);
    }

    glEnd();

    glLineWidth(1.0f);
}

void display()
{
    //glClear(GL_COLOR_BUFFER_BIT);

    if (currentScene == 1)
    {
        displayFahim();
    }
    else if (currentScene == 2)
    {
        displaySadman2();
    }
    else if (currentScene == 3)
    {
        displayfaisal();
    }

    glutSwapBuffers();
    //glFlush();
}

void update(int value)
{
    if (currentScene == 1)
    {
        updateFahim(value);
    }
    else if (currentScene == 2)
    {
        updateSadman2(value);
    }
    else if (currentScene == 3)
    {
        updatefaisal(value);
    }

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
    {
        currentScene = 1;
    }
    else if (key == '2')
    {
        currentScene = 2;
    }
    else if (key == '3')
    {
        currentScene = 3;
    }

    if (currentScene == 1)
    {
        keyboardFahim(key, x, y);
    }
    else if (currentScene == 2)
    {
        keyboardSadman2(key, x, y);
    }
    else if (currentScene == 3)
    {
        keyboardfaisal(key, x, y);
    }
}
void displayFahim() {
    glClearColor(0.6f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawStars();
    drawSunCloud();
    drawBackgroundCity();

    glPushMatrix();
    glTranslatef(planeX, planeY + 0.65f, 0.0f);
    glScalef(0.2f, 0.2f, 1.0f);
    drawPlane();
    glPopMatrix();
    drawBird(birdX, 0.5f, 0.0f);
    drawBird(birdX + 0.15f, 0.55f, 1.2f);
    drawBird(birdX + 0.30f, 0.48f, 2.4f);
    drawBird(birdX - 0.18f, 0.52f, 0.7f);
    drawBird(birdX + 0.45f, 0.51f, 1.9f);

    drawGrass();
    drawRoad();
    drawZebraCrossing();
    drawHouses();
    drawTree();
    drawLampposts();

    drawHuman(-0.82f, humanY);
    drawHuman(h1x, -0.02f);
    drawHuman2(h2x, -0.05f);
    drawHuman3(h3x, -0.01f);
    drawHuman4(h4x, -0.04f);

    drawTrafficLight();   
          
    // LOWER lane cars
    for (int i = 0; i < NUM_LOWER; i++) {
        glPushMatrix();

        if (i == 0) glTranslatef(lowerLane[i].x, -0.1f, 0);
        else if (i == 1) glTranslatef(lowerLane[i].x, -0.1f, 0);
        else glTranslatef(lowerLane[i].x + 0.1f, -0.4f, 0);

        if (i == 0) CarDesign(lowerLane[i].brake);
        else if (i == 1) Car3Design(lowerLane[i].brake);
        else Car4Design(lowerLane[i].brake, isNight);

        glPopMatrix();
    }

    // UPPER lane cars
    for (int i = 0; i < NUM_UPPER; i++) {
        glPushMatrix();

        if (i == 0) glTranslatef(upperLane[i].x, 0.15f, 0);
        else if (i == 1) glTranslatef(upperLane[i].x, 0.17f, 0);
        else glTranslatef(upperLane[i].x - 0.1f, -0.15f, 0);

        if (i == 0) Car2Design(upperLane[i].brake);
        else if (i == 1) Car5Design(upperLane[i].brake);
        else Car6Design(upperLane[i].brake);

        glPopMatrix();
    }

    if (rain)
    {
        drawRain();
    }
    //glFlush();
}

void keyboardFahim(unsigned char key, int x, int y) {
    switch (key) {
    case 't':
        translateFlag = 1;
        break;

    case 'y':
        translateFlag = 0;
        break;

        // Traffic light
    case 'r':   // RED
        trafficLight = 1;
        if (humanMoving == 0)
        {
            humanMoving = 1;   //manus rasta par hoy
        }
        break;

    case 'n':   // YELLOW
        trafficLight = 2;
        break;

    case 'g':   // GREEN
        trafficLight = 0;
        break;

    case 'f':   // start rain
        rain = true;
        break;

    case 'c':   // stop rain
        rain = false;
        break;
    case 'w':
        rainSpeedMultiplier += 0.2f;
        break;

    case 's':
        if (rainSpeedMultiplier > 0.2f)
            rainSpeedMultiplier -= 0.2f;
        break;
    }
    glutPostRedisplay();
}

void updateFahim(int value) {
    
    if (translateFlag == 1) {
        ty += 0.005f;

        if (ty > 2.3) {
            tx = 0.40f; ty = -0.10f;
            tx1 = 0.40f; ty1 = -0.10f;
        }

        if (ty > 1.1f) {
            r = 0.024f; g = 0.043f; b = 0.102f;
            r1 = 1.0f; g1 = 1.0f; b1 = 0.0f;
            ty1 += 0.005f;

            isNight = 1;   //  night
        }
        else {
            r = 0.2f; g = 0.5f; b = 0.8f;
            r1 = 0.7f; g1 = 0.9f; b1 = 1.0f;

            isNight = 0;   //  day
        }

        if (ty < 1.0) {
            r = 0.2f; g = 0.5f; b = 0.8f;
            r1 = 0.7; g1 = 0.9; b1 = 1.0;
        }

        tx2 += 0.005f;
        if (tx2 > 1.1) tx2 = -1.1;

        // Bird movement
        birdX += 0.005f;
        if (birdX > 1.2f) birdX = -1.2f;
        birdFlap++;

        planeX += 0.01f;
        if (planeX > 1.5f) planeX = -1.5f;
        
		// Human movement
        // Human moves only during RED light
        if (humanMoving == 1)
        {
            // top -> bottom
            if (humanDirection == 0)
            {
                humanY -= 0.008f;

                // reached bottom
                if (humanY <= -0.75f)
                {
                    humanY = -0.75f;

                    humanMoving = 0;
                    humanDirection = 1;
                }
            }

            // bottom -> top
            else
            {
                humanY += 0.008f;

                // reached top
                if (humanY >= -0.02f)
                {
                    humanY = -0.02f;

                    humanMoving = 0;
                    humanDirection = 0;
                }
            }
        }

		// x axis er human movement
        if (h1dir == 0)
            h1x += h1speed;
        else
            h1x -= h1speed;
        if (h2dir == 0)
            h2x += h2speed;
        else
            h2x -= h2speed;
        if (h3dir == 0)
            h3x += h3speed;
        else
            h3x -= h3speed;
        if (h4dir == 0)
            h4x += h4speed;
        else
            h4x -= h4speed;

        if (h1x > 1.2f)
        {
            h1x = -1.2f;

            h1speed = 0.001f + (rand() % 5) * 0.0005f;

            h1dir = rand() % 2;
        }

        if (h1x < -1.2f)
        {
            h1x = 1.2f;

            h1speed = 0.001f + (rand() % 5) * 0.0005f;

            h1dir = rand() % 2;
        }

        if (h2x > 1.2f)
        {
            h2x = -1.2f;

            h2speed = 0.001f + (rand() % 5) * 0.0005f;

            h2dir = rand() % 2;
        }

        if (h2x < -1.2f)
        {
            h2x = 1.2f;

            h2speed = 0.001f + (rand() % 5) * 0.0005f;

            h2dir = rand() % 2;
        }

        if (h3x > 1.2f)
        {
            h3x = -1.2f;

            h3speed = 0.001f + (rand() % 5) * 0.0005f;

            h3dir = rand() % 2;
        }

        if (h3x < -1.2f)
        {
            h3x = 1.2f;

            h3speed = 0.001f + (rand() % 5) * 0.0005f;

            h3dir = rand() % 2;
        }

        if (h4x > 1.2f)
        {
            h4x = -1.2f;

            h4speed = 0.001f + (rand() % 5) * 0.0005f;

            h4dir = rand() % 2;
        }

        if (h4x < -1.2f)
        {
            h4x = 1.2f;

            h4speed = 0.001f + (rand() % 5) * 0.0005f;

            h4dir = rand() % 2;
        }


        //car movement
        // LOWER lane
        for (int i = 0; i < NUM_LOWER; i++) {

            // RED LIGHT STOP AT ZEBRA CROSSING
            if (trafficLight == 1)
            {
                if (lowerLane[i].x < -0.7f &&
                    lowerLane[i].x > -1.2f)
                {
                    lowerLane[i].brake = 1;
                    continue;
                }
            }

            int blocked = 0;
            for (int j = 0; j < NUM_LOWER; j++) {
                if (i != j) {
                    if (lowerLane[j].x < lowerLane[i].x &&
                        (lowerLane[i].x - lowerLane[j].x) < 0.25f) {

                        blocked = 1;
                        lowerLane[i].brake = 1;
                        lowerLane[j].brake = 1;
                        break;
                    }
                }
            }

            float speedMult = 1.0f;
            // yellow light slow zone only near zebra crossing
            if (trafficLight == 2)
            {
                if (lowerLane[i].x < -0.7f &&
                    lowerLane[i].x > -1.2f)
                {
                    speedMult = 0.25f;
                }
            }

            if (!blocked) {
                lowerLane[i].x -= lowerLane[i].speed * speedMult;
                lowerLane[i].brake = 0;
            }
            else {
                lowerLane[i].x -= lowerLane[i].speed * 0.2f * speedMult;
            }

            // respawn
            if (lowerLane[i].x < -1.8f) {
                lowerLane[i].x = 1.5f + (rand() % 100) / 100.0f;
                lowerLane[i].speed = 0.007f + (rand() % 5) * 0.002f;
            }
        }


        // UPPER lane
        for (int i = 0; i < NUM_UPPER; i++) {

            // RED LIGHT STOP ZONE
            if (trafficLight == 1)
            {
                if (upperLane[i].x > -1.2f &&
                    upperLane[i].x < -0.2f)
                {
                    upperLane[i].brake = 1;
                    continue;
                }
            }

            int blocked = 0;

            for (int j = 0; j < NUM_UPPER; j++) {
                if (i != j) {
                    if (upperLane[j].x > upperLane[i].x &&
                        (upperLane[j].x - upperLane[i].x) < 0.25f) {

                        blocked = 1;
                        upperLane[i].brake = 1;
                        upperLane[j].brake = 1;
                        break;
                    }
                }
            }

            float speedMult = 1.0f;
            // yellow light slow zone 
            if (trafficLight == 2)
            {
                if (upperLane[i].x > -1.2f &&
                    upperLane[i].x < -0.2f)
                {
                    speedMult = 0.25f;
                }
            }

            if (!blocked) {
                upperLane[i].x += upperLane[i].speed * speedMult;
                upperLane[i].brake = 0;
            }
            else {
                upperLane[i].x += upperLane[i].speed * 0.2f * speedMult;
            }

            if (upperLane[i].x > 1.8f) {
                upperLane[i].x = -1.5f - (rand() % 100) / 100.0f;
                upperLane[i].speed = 0.007f + (rand() % 5) * 0.002f;
            }
        }
    }

    // star er logic
    if (isNight == 1) {

        starScale += starScaleDir;

        // scale range
        if (starScale > 1.15f || starScale < 0.9f) {
            starScaleDir = -starScaleDir;
        }
    }
    if (rain)
    {
        for (int i = 0; i < 1000; i++)
        {
            rainY[i] -= rainSpeed[i] * rainSpeedMultiplier;
            rainX[i] -= 0.002f; // wind effect

            // reset rain drop
            if (rainY[i] < -1.0f)
            {
                rainY[i] = 1.0f;
                rainX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

                rainSpeed[i] = 0.01f + ((float)rand() / RAND_MAX) * 0.03f;
            }
        }
    }
    /*glutPostRedisplay();
    glutTimerFunc(50, updateFahim, 0);*/
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1500, 1000);
    glutCreateWindow("Rural Scenario");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    srand(time(0));
    initCars();
    initFaisal();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(60, update, 0);
    for (int i = 0; i < 1000; i++)
    {
        rainX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        rainY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

        // random speed for depth effect
        rainSpeed[i] = 0.01f + ((float)rand() / RAND_MAX) * 0.03f;
    }
    glutMainLoop();
    return 0;
}
