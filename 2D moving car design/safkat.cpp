#include<windows.h>
#include <GL/freeglut.h>
#include <math.h>
#include "safkat.h"
#include "fahim.h"
#include "functions.h"

// ================ TRAFFIC LIGHT STATE =================
// 0 = GREEN (cars move freely)
// 1 = RED   (cars fully stop)
// 2 = YELLOW (cars slow down)
int trafficLight = 0;

// STARS
// four-pointed stars in the sky
void drawStar(float cx, float cy, float size) {

    float outer = size;
    float inner = size * 0.35f;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 1.0f, 0.85f, 1.0f);
    glVertex2f(cx, cy);

    // 4-pointed star: top, right, bottom, left, back to top
    float pts[10][2] = {
        { cx,          cy + outer },
        { cx + inner,  cy + inner },
        { cx + outer,  cy         },
        { cx + inner,  cy - inner },
        { cx,          cy - outer },
        { cx - inner,  cy - inner },
        { cx - outer,  cy         },
        { cx - inner,  cy + inner },
        { cx,          cy + outer },
    };

    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0)
            glColor4f(1.0f, 1.0f, 0.70f, 0.0f);
        else
            glColor4f(1.0f, 1.0f, 0.85f, 0.85f);
        glVertex2f(pts[i][0], pts[i][1]);
    }
    glEnd();

    // Small solid bright core circle
    glColor3f(1.0f, 1.0f, 0.9f);
    drawCircle(cx, cy, size * 0.18f, 20);
}

//void drawStars() {
//    if (isNight != 1) return;   // only show at night
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    drawStar(-0.55f, 0.75f, 0.045f);
//    drawStar(0.10f, 0.82f, 0.040f);
//    drawStar(0.72f, 0.70f, 0.050f);
//
//    glDisable(GL_BLEND);
//




// Adding Tree
void drawTree() {
    float tx = 0.60f;
    // Trunk
    drawRect(tx - 0.018f, 0.00f, 0.036f, 0.14f, 0.36f, 0.22f, 0.08f);


    // Tier 1 (bottom)
    drawTriangle(
        tx - 0.18f, 0.10f,
        tx + 0.18f, 0.10f,
        tx, 0.32f,
        0.13f, 0.55f, 0.07f
    );
    // Tier 2 (middle)
    drawTriangle(
        tx - 0.13f, 0.22f,
        tx + 0.13f, 0.22f,
        tx, 0.42f,
        0.18f, 0.65f, 0.09f
    );
    // Tier 3 (top)
    drawTriangle(
        tx - 0.08f, 0.33f,
        tx + 0.08f, 0.33f,
        tx, 0.50f,
        0.22f, 0.72f, 0.10f
    );
}

//  TRAFFIC LIGHT
void drawTrafficLight() {

    drawRect(-0.625f, -0.22f, 0.015f, 0.22f, 0.3f, 0.3f, 0.3f);


    drawRect(-0.645f, 0.00f, 0.055f, 0.18f, 0.15f, 0.15f, 0.15f);

    // RED light (top)
    if (trafficLight == 1)
        glColor3f(1.0f, 0.0f, 0.0f);
    else
        glColor3f(0.25f, 0.0f, 0.0f);
    drawCircle(-0.6175f, 0.155f, 0.018f, 50);

    // YELLOW light (middle)
    if (trafficLight == 2)
        glColor3f(1.0f, 0.85f, 0.0f);
    else
        glColor3f(0.25f, 0.21f, 0.0f);
    drawCircle(-0.6175f, 0.09f, 0.018f, 50);

    // GREEN light (bottom)
    if (trafficLight == 0)
        glColor3f(0.0f, 1.0f, 0.2f);
    else
        glColor3f(0.0f, 0.25f, 0.05f);
    drawCircle(-0.6175f, 0.025f, 0.018f, 50);
}


// LAMPPOSTS
void drawLampposts() {


    float upPoleX = 0.82f;
    float upBaseY = 0.00f;
    float upTopY = 0.30f;
    float upArmTip = 0.70f;
    float upBulbY = 0.285f;

    // Pole
    drawRect(upPoleX, upBaseY, 0.013f, upTopY - upBaseY, 0.50f, 0.50f, 0.50f);
    // Horizontal arm
    drawRect(upArmTip, upTopY - 0.013f, upPoleX - upArmTip, 0.013f, 0.50f, 0.50f, 0.50f);
    // head
    drawRect(upArmTip - 0.005f, upBulbY - 0.020f, 0.040f, 0.025f, 0.20f, 0.20f, 0.20f);

    // Bulb
    if (isNight == 1)
        glColor3f(1.0f, 0.95f, 0.45f);
    else
        glColor3f(0.35f, 0.35f, 0.35f);
    drawCircle(upArmTip + 0.015f, upBulbY - 0.008f, 0.011f, 50);

    // Night
    if (isNight == 1) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 0.95f, 0.40f, 0.50f);
        glVertex2f(upArmTip + 0.015f, upBulbY - 0.020f);
        glColor4f(1.0f, 0.95f, 0.40f, 0.0f);
        glVertex2f(upArmTip - 0.18f, -0.22f);
        glColor4f(1.0f, 0.95f, 0.40f, 0.0f);
        glVertex2f(upArmTip + 0.20f, -0.22f);
        glEnd();
        glDisable(GL_BLEND);
    }

    // first lampost
    float midPoleX = -0.28f;
    float midBaseY = 0.00f;
    float midTopY = 0.30f;
    float midArmTip = -0.42f;
    float midBulbY = midTopY - 0.015f;

    // Pole
    drawRect(midPoleX, midBaseY, 0.013f, midTopY - midBaseY, 0.50f, 0.50f, 0.50f);
    // Horizontal arm
    drawRect(midArmTip, midTopY - 0.013f, midPoleX - midArmTip, 0.013f, 0.50f, 0.50f, 0.50f);
    // head
    drawRect(midArmTip - 0.005f, midBulbY - 0.020f, 0.040f, 0.025f, 0.20f, 0.20f, 0.20f);

    // Bulb
    if (isNight == 1)
        glColor3f(1.0f, 0.95f, 0.45f);
    else
        glColor3f(0.35f, 0.35f, 0.35f);
    drawCircle(midArmTip + 0.015f, midBulbY - 0.008f, 0.011f, 50);

    // Night
    if (isNight == 1) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 0.95f, 0.40f, 0.50f);
        glVertex2f(midArmTip + 0.015f, midBulbY - 0.020f);
        glColor4f(1.0f, 0.95f, 0.40f, 0.0f);
        glVertex2f(midArmTip - 0.18f, -0.22f);
        glColor4f(1.0f, 0.95f, 0.40f, 0.0f);
        glVertex2f(midArmTip + 0.20f, -0.22f);
        glEnd();
        glDisable(GL_BLEND);
    }

}
