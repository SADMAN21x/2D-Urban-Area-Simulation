#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "faisal2.h"
#include "fahim.h"
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <ctime>

#define PI     3.14159265f
#define TWO_PI 6.28318530f

#define MAX_RAIN  600
#define MAX_SNOW  250
#define MAX_STARS 220
#define MAX_CARS   14


#define RAIL_TOP    -0.062f
#define VIADUCT_TOP -0.040f
#define VIADUCT_BOT -0.150f
#define PILLAR_BOT  -0.440f
#define ROAD_TOP    -0.460f
#define ROAD_MID    -0.720f
#define ROAD_BOT    -1.000f

struct Particle { float x, y, speed; };
struct Car { float x, speed; int lane; bool dir; int color; };
struct Star { float x, y, r, phase; };

Particle rain[MAX_RAIN];
Particle snow[MAX_SNOW];
Star     stars[MAX_STARS];
Car      cars[MAX_CARS];

float metroX = -1.65f;
float metroSpeed = 0.010f;
float metro2X = 1.65f;
bool  showMetro2 = false;

float cloudOff = 0.0f;
float sunAngle = 0.0f;
float fogDensity = 0.0f;
float fogTarget = 0.0f;

bool faisal_isNight = false;
static bool isRaining = false;
bool isSnow = false;
bool isFog = false;
bool cityLights = false;
bool showPlatform = false;
bool showTraffic = false;

float rainSpeedMult = 1.0f;
int   frameCount = 0;

// Current sky colour — updated in drawSky(), reused for unlit windows
unsigned char skyR = 107, skyG = 184, skyB = 242;

// Per-window static lit/dark
bool winLit[12][16][8];
int  winLastUpdate = -999;

void updateWindowStates() {
    // Recompute only every 180 frames (~3 s). cityLights/L key
    if (frameCount - winLastUpdate < 180) return;
    winLastUpdate = frameCount;
    for (int b = 0;b < 12;b++)
        for (int f = 0;f < 16;f++)
            for (int c = 0;c < 8;c++)
                winLit[b][f][c] = (rand() % 100 < 72);
}

// ============================================================
// Utilities
// ============================================================
inline float frand(float lo, float hi) {
    return lo + (hi - lo) * (rand() / (float)RAND_MAX);
}
inline float clampb(float v) { return v < 0 ? 0 : (v > 255 ? 255 : v); }

void blendOn() { glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
void blendOff() { glDisable(GL_BLEND); }

static void drawCircle(float cx, float cy, float r, int segs = 40) {
    glBegin(GL_POLYGON);
    for (int i = 0;i < segs;i++) {
        float a = TWO_PI * i / segs;
        glVertex2f(cx + cosf(a) * r, cy + sinf(a) * r);
    }
    glEnd();
}

static void drawEllipse(float cx, float cy, float rx, float ry, int segs = 24) {
    glBegin(GL_POLYGON);
    for (int i = 0;i < segs;i++) {
        float a = TWO_PI * i / segs;
        glVertex2f(cx + cosf(a) * rx, cy + sinf(a) * ry);
    }
    glEnd();
}

// Fan-shaped headlight cone
static void drawCone(float ox, float oy, float dir, float length, float halfAngle,
    float r, float g, float b, int steps = 16) {
    blendOn();
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(r, g, b, 0.50f); glVertex2f(ox, oy);
    for (int i = 0;i <= steps;i++) {
        float a = -halfAngle + 2.0f * halfAngle * i / steps;
        glColor4f(r, g, b, 0.0f);
        glVertex2f(ox + dir * cosf(a) * length, oy + sinf(a) * length);
    }
    glEnd();
    blendOff();
}

static void drawText(float x, float y, const char* s, void* font = GLUT_BITMAP_HELVETICA_12) {
    glRasterPos2f(x, y);
    while (*s) glutBitmapCharacter(font, *s++);
}

// ============================================================
// Init
// ============================================================
static void initRain() {
    for (int i = 0;i < MAX_RAIN;i++) {
        rain[i].x = frand(-1.0f, 1.0f); rain[i].y = frand(-1.0f, 1.0f);
        rain[i].speed = frand(0.018f, 0.045f);
    }
}
static void initSnow() {
    for (int i = 0;i < MAX_SNOW;i++) {
        snow[i].x = frand(-1.0f, 1.0f); snow[i].y = frand(-1.0f, 1.0f);
        snow[i].speed = frand(0.003f, 0.008f);
    }
}
static void initStars() {
    for (int i = 0;i < MAX_STARS;i++) {
        stars[i].x = frand(-1.0f, 1.0f); stars[i].y = frand(0.0f, 1.0f);
        stars[i].r = frand(0.002f, 0.007f); stars[i].phase = frand(0.0f, TWO_PI);
    }
}
static void initCars() {
    for (int i = 0;i < MAX_CARS;i++) {
        cars[i].x = frand(-1.2f, 1.2f); cars[i].speed = frand(0.004f, 0.013f);
        cars[i].lane = i % 3; cars[i].dir = (i % 2 == 0); cars[i].color = rand() % 8;
    }
}
static void initFlicker() {
    winLastUpdate = -999;
    for (int b = 0;b < 12;b++)
        for (int f = 0;f < 16;f++)
            for (int c = 0;c < 8;c++)
                winLit[b][f][c] = (rand() % 100 < 72);
}

// ============================================================
// Sky
// ============================================================
static void drawSky() {
    float r, g, b;
    if (faisal_isNight && isRaining) { r = 0.04f;g = 0.04f;b = 0.09f; }
    else if (faisal_isNight) { r = 0.03f;g = 0.03f;b = 0.10f; }
    else if (isRaining) { r = 0.36f;g = 0.39f;b = 0.44f; }
    else { r = 0.42f;g = 0.72f;b = 0.95f; }
    // Store for use as unlit window colour
    skyR = (unsigned char)(r * 255); skyG = (unsigned char)(g * 255); skyB = (unsigned char)(b * 255);
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void drawStars() {
    if (!faisal_isNight) return;
    blendOn();
    for (int i = 0;i < MAX_STARS;i++) {
        float tw = 0.45f + 0.55f * sinf(frameCount * 0.035f + stars[i].phase);
        glColor4f(1.0f, 0.98f, 0.92f, tw);
        drawCircle(stars[i].x, stars[i].y, stars[i].r, 6);
    }
    blendOff();
}

static void drawMoon() {
    if (!faisal_isNight) return;
    float mx = 0.74f, my = 0.82f;
    blendOn();
    for (int h = 6;h >= 1;h--) { glColor4f(0.85f, 0.85f, 0.60f, 0.016f * h); drawCircle(mx, my, 0.068f + h * 0.018f, 20); }
    blendOff();
    glColor3f(0.97f, 0.97f, 0.84f); drawCircle(mx, my, 0.068f, 30);
    glColor3f(0.03f, 0.03f, 0.10f); drawCircle(mx + 0.034f, my + 0.012f, 0.054f, 30);
    glColor3f(0.88f, 0.88f, 0.74f);
    drawCircle(mx - 0.015f, my - 0.018f, 0.010f, 12);
    drawCircle(mx + 0.005f, my + 0.025f, 0.007f, 10);
}

static void drawSun() {
    if (faisal_isNight || isRaining) return;
    float sx = 0.74f, sy = 0.80f;
    blendOn();
    for (int h = 8;h >= 1;h--) { glColor4f(1.0f, 0.85f, 0.20f, 0.022f * h); drawCircle(sx, sy, 0.058f + h * 0.022f, 22); }
    blendOff();
    glPushMatrix(); glTranslatef(sx, sy, 0); glRotatef(sunAngle, 0, 0, 1);
    for (int i = 0;i < 16;i++) {
        float a = TWO_PI * i / 16.0f, inn = 0.072f, out = 0.10f + 0.03f * (i % 2);
        blendOn();
        glBegin(GL_LINES);
        glColor4f(1.0f, 0.88f, 0.25f, 0.65f); glVertex2f(cosf(a) * inn, sinf(a) * inn);
        glColor4f(1.0f, 0.88f, 0.25f, 0.00f); glVertex2f(cosf(a) * out, sinf(a) * out);
        glEnd(); blendOff();
    }
    glPopMatrix();
    glColor3f(1.0f, 0.90f, 0.15f); drawCircle(sx, sy, 0.058f, 36);
    glColor3f(1.0f, 0.97f, 0.60f); drawCircle(sx - 0.014f, sy + 0.012f, 0.024f, 18);
}

// ============================================================
// Clouds
// ============================================================
static void drawCloud(float bx, float by, float sc) {
    glPushMatrix();
    glTranslatef(bx + cloudOff * 0.35f, by, 0);
    glScalef(sc, sc, 1.0f);
    float cr, cg, cb;
    if (faisal_isNight && isRaining) { cr = 0.13f;cg = 0.13f;cb = 0.17f; }
    else if (faisal_isNight) { cr = 0.20f;cg = 0.20f;cb = 0.30f; }
    else if (isRaining) { cr = 0.54f;cg = 0.55f;cb = 0.60f; }
    else { cr = 0.97f;cg = 0.97f;cb = 1.00f; }
    blendOn();
    glColor4f(cr * 0.80f, cg * 0.80f, cb * 0.80f, 0.45f);
    drawEllipse(0.055f, -0.008f, 0.098f, 0.026f);
    glColor4f(cr, cg, cb, 1.0f);
    float puffs[][3] = { {0,0,0.055f},{0.050f,0.018f,0.070f},{0.105f,0.005f,0.060f},{0.078f,-0.015f,0.040f},{-0.028f,-0.010f,0.038f} };
    for (auto& p : puffs) drawCircle(p[0], p[1], p[2], 22);
    blendOff();
    glPopMatrix();
}

// ============================================================
// Buildings
// ============================================================
struct BldDef { float x, w, h;unsigned char r, g, b, wr, wg, wb;int floors; };
const int NB = 11;
BldDef bld[NB] = {
    {-1.00f,0.130f,0.68f, 36,38,52, 255,200, 60, 9},
    {-0.84f,0.095f,0.44f, 28,30,46,  80,160,255, 6},
    {-0.64f,0.165f,0.86f, 32,34,50,   0,210,255,12},
    {-0.40f,0.120f,0.58f, 26,28,44, 255,100,180, 8},
    {-0.22f,0.085f,0.76f, 20,22,40, 255,200,  0,11},
    { 0.00f,0.095f,0.40f, 38,40,55, 100,255,180, 5},
    { 0.14f,0.140f,0.68f, 30,32,48, 255, 80, 80,10},
    { 0.36f,0.105f,0.52f, 24,26,44, 180,100,255, 7},
    { 0.54f,0.155f,0.82f, 18,20,38,   0,255,200,12},
    { 0.76f,0.115f,0.48f, 34,36,52, 255,160,  0, 6},
    { 0.94f,0.135f,0.72f, 28,30,46,  80,200,255,10},
};

static void drawBuildings() {
    for (int bi = 0;bi < NB;bi++) {
        BldDef& B = bld[bi];
        float bx = B.x, bw = B.w;
        float by = -0.08f;   // building base just above viaduct level
        float bh = B.h;

        // Building bottom — extends down to ground (PILLAR_BOT) in a darker shade
        glColor3ub((unsigned char)clampb(B.r - 8), (unsigned char)clampb(B.g - 8), (unsigned char)clampb(B.b - 8));
        glRectf(bx, PILLAR_BOT, bx + bw, by);
        // Ground floor detail line
        glColor3ub((unsigned char)clampb(B.r + 5), (unsigned char)clampb(B.g + 5), (unsigned char)clampb(B.b + 5));
        glRectf(bx, by - 0.012f, bx + bw, by);

        // Windows on the bottom extension (same grid as upper floors)
        {
            float botH = by - PILLAR_BOT;          // total height of bottom section
            int   botFls = (int)(botH / (bh / B.floors)); // same floor height as upper
            if (botFls < 1) botFls = 1;
            float botFlH = botH / botFls;
            int   bwcols = (int)(bw / 0.028f); if (bwcols > 8) bwcols = 8;
            float bww = 0.014f, bwh = botFlH * 0.52f, bwcs = bw / (bwcols + 1);
            for (int fl = 0;fl < botFls;fl++) {
                float wy = PILLAR_BOT + fl * botFlH + botFlH * 0.20f;
                for (int c = 0;c < bwcols;c++) {
                    float wx = bx + bwcs * (c + 1) - bww / 2.0f;
                    bool lit;
                    if (cityLights) {
                        lit = true;
                    }
                    else if (faisal_isNight) {
                        lit = winLit[bi % 12][(fl + B.floors) % 16][c % 8];
                    }
                    else {
                        lit = ((bi * 3 + fl * 2 + c + 1) % 7 < 3);
                    }
                    if (lit) glColor3ub(B.wr, B.wg, B.wb);
                    else    glColor3ub(skyR, skyG, skyB);
                    glRectf(wx, wy, wx + bww, wy + bwh);
                }
            }
        }

        blendOn(); glColor4f(0, 0, 0, 0.16f);
        glRectf(bx + 0.008f, by + 0.008f, bx + bw + 0.008f, by + bh + 0.008f); blendOff();

        glColor3ub(B.r, B.g, B.b);
        glRectf(bx, by, bx + bw, by + bh);
        glColor3ub((unsigned char)clampb(B.r + 18), (unsigned char)clampb(B.g + 18), (unsigned char)clampb(B.b + 18));
        glRectf(bx, by + bh * 0.65f, bx + bw, by + bh);

        int cols = (int)(bw / 0.023f);
        glColor3ub((unsigned char)clampb(B.r + 10), (unsigned char)clampb(B.g + 10), (unsigned char)clampb(B.b + 10));
        glLineWidth(0.6f); glBegin(GL_LINES);
        for (int c = 1;c < cols;c++) { float lx = bx + bw * c / cols; glVertex2f(lx, by); glVertex2f(lx, by + bh); }
        glEnd();

        float flH = bh / B.floors;
        int wcols = (int)(bw / 0.028f); if (wcols > 8) wcols = 8;
        float ww = 0.014f, wh = flH * 0.52f, wcs = bw / (wcols + 1);
        for (int fl = 0;fl < B.floors;fl++) {
            float wy = by + fl * flH + flH * 0.20f;
            for (int c = 0;c < wcols;c++) {
                float wx = bx + wcs * (c + 1) - ww / 2.0f;
                bool lit;
                if (cityLights) {
                    lit = true;  // L key: all windows ON, no flicker
                }
                else if (faisal_isNight) {
                    lit = winLit[bi % 12][fl % 16][c % 8]; // static state, updates every 3s
                }
                else {
                    lit = ((bi * 3 + fl * 2 + c) % 7 < 3);       // day: fixed subset lit
                }
                if (lit) glColor3ub(B.wr, B.wg, B.wb);
                else    glColor3ub(skyR, skyG, skyB);
                glRectf(wx, wy, wx + ww, wy + wh);
            }
        }

        glColor3ub((unsigned char)clampb(B.r - 10), (unsigned char)clampb(B.g - 10), (unsigned char)clampb(B.b - 10));
        glRectf(bx + bw * 0.25f, by + bh, bx + bw * 0.50f, by + bh + 0.022f);

        glColor3ub(110, 112, 120); glLineWidth(1.4f);
        glBegin(GL_LINES);
        glVertex2f(bx + bw * 0.72f, by + bh); glVertex2f(bx + bw * 0.72f, by + bh + 0.045f);
        glEnd();
        bool bon = faisal_isNight && ((frameCount / 35) % 2 == 0);
        glColor3f(bon ? 1.0f : 0.35f, 0.0f, 0.0f);
        drawCircle(bx + bw * 0.72f, by + bh + 0.050f, 0.006f, 8);
        if (bon) { blendOn(); glColor4f(1.0f, 0.0f, 0.0f, 0.18f); drawCircle(bx + bw * 0.72f, by + bh + 0.050f, 0.022f, 12); blendOff(); }
    }
}

// ============================================================
// Infrastructure
// ============================================================
static void drawInfrastructure() {
    // Viaduct deck
    glColor3ub(75, 78, 92);  glRectf(-1.0f, VIADUCT_BOT, 1.0f, VIADUCT_TOP);
    glColor3ub(90, 94, 110); glRectf(-1.0f, VIADUCT_TOP - 0.008f, 1.0f, VIADUCT_TOP);
    glColor3ub(52, 54, 68);  glRectf(-1.0f, VIADUCT_BOT, 1.0f, VIADUCT_BOT + 0.008f);

    // Pillars
    for (float px = -0.88f;px <= 0.88f;px += 0.22f) {
        glColor3ub(65, 67, 82); glRectf(px - 0.020f, VIADUCT_BOT, px + 0.020f, PILLAR_BOT);
        glColor3ub(48, 50, 64); glRectf(px - 0.020f, VIADUCT_BOT, px - 0.012f, PILLAR_BOT);
        glColor3ub(58, 60, 76); glRectf(px - 0.030f, VIADUCT_BOT, px + 0.030f, VIADUCT_BOT + 0.014f);
        glColor3ub(50, 52, 66); glRectf(px - 0.028f, PILLAR_BOT - 0.012f, px + 0.028f, PILLAR_BOT);
    }

    // Ballast / deck surface
    glColor3ub(62, 64, 74);
    glRectf(-1.0f, RAIL_TOP - 0.052f, 1.0f, RAIL_TOP - 0.006f);

    // Sleepers
    glColor3ub(72, 56, 38);
    for (float sx = -1.0f;sx < 1.0f;sx += 0.038f)
        glRectf(sx, RAIL_TOP - 0.050f, sx + 0.020f, RAIL_TOP - 0.010f);

    // Running rails
    glLineWidth(3.0f); glColor3ub(150, 152, 165);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, RAIL_TOP - 0.013f); glVertex2f(1.0f, RAIL_TOP - 0.013f);
    glVertex2f(-1.0f, RAIL_TOP - 0.043f); glVertex2f(1.0f, RAIL_TOP - 0.043f);
    glEnd();

    // Third power rail
    glColor3ub(180, 140, 40);
    glRectf(-1.0f, RAIL_TOP - 0.006f, 1.0f, RAIL_TOP - 0.002f);

    // Pavement under viaduct
    glColor3ub(55, 56, 65); glRectf(-1.0f, PILLAR_BOT, 1.0f, ROAD_TOP);
    glColor3ub(95, 92, 100); glRectf(-1.0f, ROAD_TOP, 1.0f, ROAD_TOP + 0.010f);

    // Road
    glColor3ub(24, 24, 30); glRectf(-1.0f, ROAD_BOT, 1.0f, ROAD_TOP);
    // double yellow centre
    glColor3ub(210, 190, 30);
    glRectf(-1.0f, ROAD_MID + 0.004f, 1.0f, ROAD_MID + 0.007f);
    glRectf(-1.0f, ROAD_MID - 0.007f, 1.0f, ROAD_MID - 0.004f);
    // dashed whites
    glColor3ub(200, 200, 200);
    for (float dx = -1.0f;dx < 1.0f;dx += 0.14f) {
        glRectf(dx, -0.590f, dx + 0.080f, -0.584f);
        glRectf(dx + 0.007f, -0.850f, dx + 0.087f, -0.844f);
    }
    glColor3ub(90, 88, 96); glRectf(-1.0f, ROAD_BOT, 1.0f, ROAD_BOT + 0.012f);
}

// ============================================================
// Street Lamps — original clean style with radial glow
// ============================================================
static void drawStreetLamps() {
    bool on = faisal_isNight || cityLights;
    for (float lx = -0.88f;lx <= 0.88f;lx += 0.26f) {
        // Vertical pole
        glColor3ub(120, 120, 130); glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(lx, ROAD_TOP);
        glVertex2f(lx, VIADUCT_BOT + 0.04f);
        glEnd();
        // Horizontal arm
        glBegin(GL_LINES);
        glVertex2f(lx, VIADUCT_BOT + 0.04f);
        glVertex2f(lx + 0.04f, VIADUCT_BOT + 0.04f);
        glEnd();

        float hx = lx + 0.04f, hy = VIADUCT_BOT + 0.04f;

        if (on) {
            // Radial warm glow — layered circles (original approach)
            blendOn();
            for (int r = 6;r >= 1;r--) {
                float rad = r * 0.025f;
                float alpha = 0.12f / r;
                glColor4f(1.0f, 0.82f, 0.40f, alpha);
                drawCircle(hx, hy, rad, 18);
            }
            blendOff();
            // Bright lamp bulb
            glColor3f(1.0f, 0.90f, 0.60f);
            drawCircle(hx, hy, 0.012f, 10);
        }
        else {
            // Daytime: dim yellow dot
            glColor3ub(200, 180, 100);
            drawCircle(hx, hy, 0.010f, 10);
        }
    }
}

// ============================================================
// Trees
// ============================================================
static void drawBroadleaf(float cx, float gy, float th, float cr,
    unsigned char tr, unsigned char tg, unsigned char tb) {
    glColor3ub(90, 58, 28);
    glRectf(cx - 0.010f, gy, cx + 0.010f, gy + th);
    blendOn(); glColor4f(0, 0, 0, 0.14f);
    drawEllipse(cx + 0.004f, gy + th + 0.002f, cr * 0.90f, cr * 0.26f, 14); blendOff();
    float puffs[][3] = { {0.0f,0.55f,1.0f},{-0.55f,0.20f,0.78f},{0.55f,0.20f,0.78f},{0.0f,0.10f,0.70f} };
    for (int p = 0;p < 4;p++) {
        glColor3ub((unsigned char)clampb(tr - p * 6), (unsigned char)clampb(tg - p * 5), (unsigned char)clampb(tb - p * 4));
        drawCircle(cx + puffs[p][0] * cr, gy + th + puffs[p][1] * cr, puffs[p][2] * cr, 18);
    }
}

static void drawPine(float cx, float gy, float th, float cr,
    unsigned char tr, unsigned char tg, unsigned char tb) {
    glColor3ub(82, 52, 22);
    glRectf(cx - 0.009f, gy, cx + 0.009f, gy + th * 0.45f);
    for (int t = 0;t < 3;t++) {
        float base = gy + th * 0.30f + t * cr * 0.65f;
        float w = cr * (1.0f - t * 0.25f), h = cr * 1.25f * (1.0f - t * 0.15f);
        glColor3ub((unsigned char)clampb(tr - t * 10), (unsigned char)clampb(tg - t * 8), (unsigned char)clampb(tb - t * 6));
        glBegin(GL_TRIANGLES);
        glVertex2f(cx - w, base); glVertex2f(cx + w, base); glVertex2f(cx, base + h);
        glEnd();
        glColor3ub((unsigned char)clampb(tr - t * 10 + 16), (unsigned char)clampb(tg - t * 8 + 14), (unsigned char)clampb(tb - t * 6 + 10));
        glBegin(GL_TRIANGLES);
        glVertex2f(cx - w * 0.35f, base + h * 0.25f);
        glVertex2f(cx + w * 0.08f, base + h * 0.25f);
        glVertex2f(cx + w * 0.04f, base + h * 0.80f);
        glEnd();
    }
}

struct TS { float x;bool pine;float th, cr;unsigned char r, g, b; };

// Trees between viaduct pillars only (drawn before cars)
static void drawTreesUnderViaduct() {
    TS under[] = {
        {-0.780f,false,0.040f,0.036f,30,118,42},{-0.660f,true ,0.038f,0.030f,24,105,35},
        {-0.560f,false,0.042f,0.034f,36,124,48},{-0.450f,true ,0.036f,0.028f,28,112,38},
        {-0.340f,false,0.040f,0.032f,32,120,44},{-0.230f,true ,0.038f,0.030f,26,108,36},
        {-0.120f,false,0.042f,0.036f,38,126,50},{-0.010f,true ,0.036f,0.028f,22,104,33},
        { 0.100f,false,0.040f,0.034f,34,122,46},{ 0.210f,true ,0.038f,0.032f,28,114,40},
        { 0.320f,false,0.042f,0.036f,30,118,42},{ 0.430f,true ,0.036f,0.028f,24,106,35},
        { 0.540f,false,0.040f,0.034f,36,124,48},{ 0.650f,true ,0.038f,0.030f,28,112,38},
        { 0.760f,false,0.042f,0.036f,32,120,44},{ 0.860f,true ,0.036f,0.028f,26,108,36},
    };
    for (auto& t : under) {
        if (t.pine) drawPine(t.x, PILLAR_BOT, t.th, t.cr, t.r, t.g, t.b);
        else       drawBroadleaf(t.x, PILLAR_BOT, t.th, t.cr, t.r, t.g, t.b);
    }
}

// Roadside trees — drawn AFTER cars so trees are always in front
static void drawTreesRoadside() {
    TS road[] = {
        {-0.920f,false,0.032f,0.028f,38,128,52},{-0.760f,true ,0.030f,0.024f,30,115,40},
        {-0.600f,false,0.034f,0.026f,42,132,56},{-0.440f,true ,0.030f,0.022f,28,112,38},
        {-0.280f,false,0.032f,0.026f,36,124,50},{-0.120f,true ,0.030f,0.024f,32,118,44},
        { 0.040f,false,0.034f,0.028f,40,130,54},{ 0.200f,true ,0.030f,0.022f,28,110,38},
        { 0.360f,false,0.032f,0.026f,38,126,52},{ 0.520f,true ,0.030f,0.024f,34,120,46},
        { 0.680f,false,0.034f,0.028f,42,134,56},{ 0.840f,true ,0.030f,0.022f,30,114,40},
    };
    for (auto& t : road) {
        if (t.pine) drawPine(t.x, ROAD_BOT + 0.012f, t.th, t.cr, t.r, t.g, t.b);
        else       drawBroadleaf(t.x, ROAD_BOT + 0.012f, t.th, t.cr, t.r, t.g, t.b);
    }
}

// ============================================================
// Platform
// ============================================================
static void drawPlatform() {
    if (!showPlatform) return;
    float px = -0.20f, pw = 0.40f, py = VIADUCT_TOP, ph = 0.072f;
    glColor3ub(75, 90, 108); glRectf(px, py - ph, px + pw, py);
    glColor3ub(255, 200, 0);
    for (float tx = px;tx < px + pw;tx += 0.022f)
        glRectf(tx, py - 0.010f, tx + 0.013f, py - 0.004f);
    glColor3ub(28, 55, 95); glRectf(px - 0.020f, py, px + pw + 0.020f, py + 0.018f);
    glColor3ub(60, 80, 100);
    for (float cx = px;cx <= px + pw;cx += 0.095f)
        glRectf(cx - 0.006f, py - ph, cx + 0.006f, py + 0.018f);
    float ppxs[] = { -0.14f,-0.07f,0.00f,0.09f,0.16f };
    for (float ppx : ppxs) {
        float phy = py - 0.005f;
        glColor3ub(40, 38, 52);
        drawCircle(ppx, phy - 0.026f, 0.011f, 10);
        glRectf(ppx - 0.008f, phy - 0.055f, ppx + 0.008f, phy - 0.026f);
        glRectf(ppx - 0.007f, phy - 0.070f, ppx - 0.001f, phy - 0.055f);
        glRectf(ppx + 0.001f, phy - 0.070f, ppx + 0.007f, phy - 0.055f);
    }
    glColor3ub(0, 35, 90); glRectf(px + 0.06f, py + 0.001f, px + pw - 0.06f, py + 0.014f);
    glColor3f(1, 1, 1);
    drawText(px + 0.067f, py + 0.004f, "MOTIJHEEL  MRT-6", GLUT_BITMAP_HELVETICA_10);
}

// ============================================================
// Traffic — simple clean car style (original)
// ============================================================
static void drawTrafficCars() {
    if (!showTraffic) return;
    static const unsigned char CC[][3] = {
        {200,45,45},{45,105,210},{215,175,35},{50,165,80},
        {195,100,30},{160,55,205},{45,180,185},{205,80,120}
    };
    float lanes[] = { ROAD_TOP - 0.028f, ROAD_MID + 0.012f, ROAD_BOT + 0.060f };
    bool nightOn = faisal_isNight || cityLights;

    for (int i = 0;i < MAX_CARS;i++) {
        float cx = cars[i].x;
        float cy = lanes[cars[i].lane % 3];
        bool  rt = cars[i].dir;
        const unsigned char* c = CC[cars[i].color % 8];

        float cw = 0.10f, ch = 0.038f;

        // Main body
        glColor3ub(c[0], c[1], c[2]);
        glRectf(cx, cy, cx + cw, cy + ch);

        // Roof (smaller rect centred on body)
        glColor3ub((unsigned char)clampb(c[0] - 30), (unsigned char)clampb(c[1] - 30), (unsigned char)clampb(c[2] - 30));
        glRectf(cx + cw * 0.15f, cy + ch, cx + cw * 0.85f, cy + ch * 1.55f);

        // Windows
        glColor3ub(100, 140, 180);
        glRectf(cx + cw * 0.17f, cy + ch * 1.06f, cx + cw * 0.46f, cy + ch * 1.50f);
        glRectf(cx + cw * 0.54f, cy + ch * 1.06f, cx + cw * 0.83f, cy + ch * 1.50f);

        // Wheels
        glColor3ub(20, 20, 25);
        drawCircle(cx + cw * 0.20f, cy + 0.004f, 0.013f, 10);
        drawCircle(cx + cw * 0.80f, cy + 0.004f, 0.013f, 10);

        // Headlights
        float hx = rt ? cx + cw : cx;
        glColor3f(nightOn ? 1.0f : 0.88f, nightOn ? 0.95f : 0.88f, 0.65f);
        glRectf(hx - (rt ? 0.005f : 0), cy + ch * 0.50f, hx + (rt ? 0 : 0.005f), cy + ch * 0.85f);
        if (nightOn) {
            blendOn(); glColor4f(1.0f, 0.92f, 0.65f, 0.22f);
            drawCircle(hx, cy + ch * 0.65f, 0.045f, 12); blendOff();
        }

        // Tail lights
        float tx2 = rt ? cx : cx + cw;
        glColor3ub(200, 18, 18);
        glRectf(tx2 - (rt ? 0 : 0.005f), cy + ch * 0.50f, tx2 + (rt ? 0.005f : 0), cy + ch * 0.85f);
    }
}

// ============================================================
// Train Body — drawn BEFORE headlight
// ============================================================
static void drawTrainBody(float tx, float dir) {
    float tw = 0.92f, th = 0.155f;
    float trainBot = RAIL_TOP - 0.044f;  // bottom of train body
    float ty = trainBot + th;      // top of train body
    float bx = tx - (dir > 0 ? 0 : tw);

    // Cast shadow on viaduct
    blendOn(); glColor4f(0, 0, 0, 0.20f);
    glRectf(bx + 0.008f, VIADUCT_TOP - 0.006f, bx + tw + 0.008f, VIADUCT_TOP); blendOff();

    // Under-carriage
    glColor3ub(28, 30, 40);
    glRectf(bx + 0.025f, trainBot, bx + tw - 0.025f, trainBot + 0.022f);
    glColor3ub(45, 47, 58);
    for (float bp = 0.10f;bp < 0.90f;bp += 0.22f)
        glRectf(bx + tw * bp - 0.020f, trainBot, bx + tw * bp + 0.020f, trainBot + 0.022f);

    // Wheels sit ON the rail
    float wheelR = 0.022f;
    float wheelY = RAIL_TOP - 0.028f;   // centre of wheel = rail surface - wheelR + small fudge
    float wpos[] = { 0.09f,0.26f,0.64f,0.81f };
    for (float wp : wpos) {
        float wx = bx + tw * wp;
        glColor3ub(18, 18, 24);  drawCircle(wx, wheelY, wheelR * 1.06f, 16); // flange
        glColor3ub(28, 28, 36);  drawCircle(wx, wheelY, wheelR, 16);
        glColor3ub(95, 96, 108); drawCircle(wx, wheelY, wheelR * 0.42f, 12);
    }

    // Main body
    glColor3ub(178, 181, 194);
    glRectf(bx, trainBot + 0.022f, bx + tw, ty);
    glColor3ub(215, 218, 228);
    glRectf(bx, ty - th * 0.18f, bx + tw, ty);

    // MRT-6 green band + white borders
    glColor3ub(0, 155, 65);
    glRectf(bx, ty - th * 0.52f, bx + tw, ty - th * 0.40f);
    glColor3ub(240, 245, 240);
    glRectf(bx, ty - th * 0.405f, bx + tw, ty - th * 0.395f);
    glRectf(bx, ty - th * 0.525f, bx + tw, ty - th * 0.515f);

    // Blue accent
    glColor3ub(0, 90, 210);
    glRectf(bx, ty - th * 0.65f, bx + tw, ty - th * 0.60f);

    // Windows
    for (int i = 0;i < 5;i++) {
        float wx = bx + 0.035f + i * 0.170f;
        float wy = ty - th * 0.38f, wh = th * 0.30f, ww = 0.130f;
        glColor3ub(48, 52, 68); glRectf(wx, wy, wx + ww, wy + wh);
        glColor3ub(12, 18, 48); glRectf(wx + 0.005f, wy + 0.004f, wx + ww - 0.005f, wy + wh - 0.004f);
        if (faisal_isNight || cityLights) {
            blendOn(); glColor4f(1.0f, 0.88f, 0.60f, 0.14f);
            glRectf(wx + 0.006f, wy + 0.005f, wx + ww - 0.006f, wy + wh - 0.005f); blendOff();
        }
        blendOn(); glColor4f(1, 1, 1, 0.10f);
        glRectf(wx + 0.006f, wy + wh - 0.016f, wx + 0.042f, wy + wh - 0.005f); blendOff();
    }

    // Door seams
    glColor3ub(88, 92, 108); glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = 0;i < 4;i++) {
        float dlx = bx + 0.170f + i * 0.170f;
        glVertex2f(dlx, trainBot + 0.022f); glVertex2f(dlx, ty);
    }
    glEnd();

    // Pantograph + catenary shoe
    float pcx = bx + tw * 0.50f;
    glColor3ub(110, 112, 125); glLineWidth(1.8f);
    glBegin(GL_LINES);
    glVertex2f(pcx - 0.055f, ty); glVertex2f(pcx, ty + 0.026f);
    glVertex2f(pcx + 0.055f, ty); glVertex2f(pcx, ty + 0.026f);
    glVertex2f(pcx - 0.065f, ty + 0.026f); glVertex2f(pcx + 0.065f, ty + 0.026f);
    glEnd();
    glColor3ub(200, 180, 50);
    glRectf(pcx - 0.012f, ty + 0.024f, pcx + 0.012f, ty + 0.028f);

    // Destination board
    float dbx = (dir > 0) ? bx + tw - 0.145f : bx + 0.012f;
    glColor3ub(0, 18, 0); glRectf(dbx, ty - 0.052f, dbx + 0.132f, ty - 0.016f);
    glColor3ub(0, 235, 65);
    drawText(dbx + 0.006f, ty - 0.042f, (dir > 0) ? "MOTIJHEEL" : "UTTARA N", GLUT_BITMAP_HELVETICA_10);
}

// Redraws viaduct top surface + rails — called after train body so headlight
// cone (drawn last) appears to sit ON the rail, not behind it.
static void redrawRailSurface() {
    // Viaduct top cap (covers any body/wheel bleed below deck)
    glColor3ub(90, 94, 110);
    glRectf(-1.0f, VIADUCT_TOP - 0.008f, 1.0f, VIADUCT_TOP);
    // Ballast
    glColor3ub(62, 64, 74);
    glRectf(-1.0f, RAIL_TOP - 0.052f, 1.0f, RAIL_TOP - 0.006f);
    // Sleepers
    glColor3ub(72, 56, 38);
    for (float sx = -1.0f;sx < 1.0f;sx += 0.038f)
        glRectf(sx, RAIL_TOP - 0.050f, sx + 0.020f, RAIL_TOP - 0.010f);
    // Rails on top
    glLineWidth(3.0f); glColor3ub(150, 152, 165);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, RAIL_TOP - 0.013f); glVertex2f(1.0f, RAIL_TOP - 0.013f);
    glVertex2f(-1.0f, RAIL_TOP - 0.043f); glVertex2f(1.0f, RAIL_TOP - 0.043f);
    glEnd();
    // Power rail
    glColor3ub(180, 140, 40);
    glRectf(-1.0f, RAIL_TOP - 0.006f, 1.0f, RAIL_TOP - 0.002f);
}

// ============================================================
// Train Headlight — drawn LAST, always on top
// ============================================================
static void drawTrainHeadlight(float tx, float dir) {
    float tw = 0.92f, th = 0.155f;
    float trainBot = RAIL_TOP - 0.044f;
    float bx = tx - (dir > 0 ? 0 : tw);
    float midY = trainBot + th * 0.42f;   // slightly below centre = aimed at track
    float hx = (dir > 0) ? bx : bx + tw;
    float d = (dir > 0) ? 1.0f : -1.0f;

    // Outer wide diffuse cone (aimed slightly down)
    blendOn();
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 0.90f, 0.55f, 0.38f); glVertex2f(hx, midY);
    int steps = 20;
    for (int i = 0;i <= steps;i++) {
        float frac = (float)i / steps;
        float a = -0.32f + 0.64f * frac;          // half-angle ~18 deg
        float ex = hx + d * cosf(a) * 0.45f;
        float ey = midY + sinf(a) * 0.45f - 0.04f * frac; // tilt downward
        glColor4f(1.0f, 0.90f, 0.55f, 0.0f);
        glVertex2f(ex, ey);
    }
    glEnd();

    // Inner tight bright cone
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 0.97f, 0.85f, 0.55f); glVertex2f(hx, midY);
    for (int i = 0;i <= steps;i++) {
        float frac = (float)i / steps;
        float a = -0.13f + 0.26f * frac;
        float ex = hx + d * cosf(a) * 0.26f;
        float ey = midY + sinf(a) * 0.26f - 0.025f * frac;
        glColor4f(1.0f, 0.97f, 0.85f, 0.0f);
        glVertex2f(ex, ey);
    }
    glEnd();
    blendOff();

    // Ground light spill ellipse on rail ahead
    blendOn();
    float spx = hx + d * 0.10f;
    glColor4f(1.0f, 0.92f, 0.60f, 0.28f);
    drawEllipse(spx, RAIL_TOP - 0.025f, 0.16f, 0.022f, 16);
    blendOff();

    // Two physical lens circles
    float ld = d * -0.005f;
    glColor3f(1.0f, 0.97f, 0.85f);
    drawCircle(hx + ld, midY + 0.030f, 0.014f, 14);
    drawCircle(hx + ld, midY - 0.024f, 0.010f, 12);
    // Bright inner hotspot
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(hx + ld, midY + 0.030f, 0.006f, 8);
    drawCircle(hx + ld, midY - 0.024f, 0.004f, 8);
    // Lens ring
    blendOn(); glColor4f(0.8f, 0.8f, 1.0f, 0.35f);
    glLineWidth(1.2f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0;i < 14;i++) { float a = TWO_PI * i / 14;glVertex2f(hx + ld + cosf(a) * 0.014f, midY + 0.030f + sinf(a) * 0.014f); }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int i = 0;i < 12;i++) { float a = TWO_PI * i / 12;glVertex2f(hx + ld + cosf(a) * 0.010f, midY - 0.024f + sinf(a) * 0.010f); }
    glEnd();
    blendOff();
}

// ============================================================
// Market Stalls under the viaduct bridge
// ============================================================
static void drawMarketStalls() {
    // The space under the bridge runs from VIADUCT_BOT (-0.150) down to PILLAR_BOT (-0.440)
    // Pillars are at x = -0.88, -0.66, -0.44, -0.22, 0.00, 0.22, 0.44, 0.66, 0.88
    // We place stalls in the gaps between pillars

    // Stall definitions: centre-x, awning colour R/G/B, goods colour
    struct Stall {
        float cx;
        unsigned char ar, ag, ab;   // awning colour
        unsigned char gr, gg, gb;   // goods/sign colour
        const char* label;
    };
    Stall stalls[] = {
        {-0.77f, 220, 60, 60,  255,200, 80, "FOOD"},
        {-0.55f,  60,140,220,  200,255,200, "BOOKS"},
        {-0.33f, 200,120, 40,  255,160, 60, "FRUIT"},
        {-0.11f,  80,180, 80,  255,255,100, "VEG"},
        { 0.11f, 200, 60,160,  255,200,220, "CLOTH"},
        { 0.33f,  60,180,200,  160,230,255, "PHONE"},
        { 0.55f, 220,160, 40,  255,220,100, "SPICE"},
        { 0.77f, 100, 60,200,  200,160,255, "TOYS"},
    };

    float stallW = 0.130f;   // half-width of stall
    float groundY = PILLAR_BOT;       // -0.440  (stall bottom)
    float wallH = 0.120f;          // stall back-wall height
    float awningY = groundY + wallH; // top of back wall = awning attachment
    float awningD = 0.025f;          // awning droop below attachment

    for (auto& s : stalls) {
        float lx = s.cx - stallW;
        float rx = s.cx + stallW;

        // --- Back wall of stall ---
        glColor3ub((unsigned char)clampb(s.ar * 0.4f),
            (unsigned char)clampb(s.ag * 0.4f),
            (unsigned char)clampb(s.ab * 0.4f));
        glRectf(lx, groundY, rx, awningY);

        // --- Counter / table ---
        glColor3ub(140, 110, 70);
        glRectf(lx + 0.008f, groundY + 0.040f, rx - 0.008f, groundY + 0.055f);
        // table legs
        glColor3ub(100, 78, 45);
        glRectf(lx + 0.012f, groundY, lx + 0.020f, groundY + 0.042f);
        glRectf(rx - 0.020f, groundY, rx - 0.012f, groundY + 0.042f);

        // --- Goods on counter (colourful rectangles) ---
        for (int g = 0;g < 4;g++) {
            float gx = lx + 0.018f + g * 0.026f;
            unsigned char dr = (unsigned char)clampb(s.gr + (g % 2) * 20);
            unsigned char dg = (unsigned char)clampb(s.gg - (g % 3) * 15);
            unsigned char db = (unsigned char)clampb(s.gb + (g % 2) * 10);
            glColor3ub(dr, dg, db);
            glRectf(gx, groundY + 0.055f, gx + 0.018f, groundY + 0.078f);
        }

        // --- Awning (slanted trapezoid) ---
        glColor3ub(s.ar, s.ag, s.ab);
        glBegin(GL_QUADS);
        glVertex2f(lx - 0.010f, awningY);
        glVertex2f(rx + 0.010f, awningY);
        glVertex2f(rx + 0.018f, awningY - awningD);
        glVertex2f(lx - 0.018f, awningY - awningD);
        glEnd();
        // Awning stripe
        glColor3ub((unsigned char)clampb(s.ar + 40), (unsigned char)clampb(s.ag + 40), (unsigned char)clampb(s.ab + 40));
        glBegin(GL_QUADS);
        glVertex2f(lx + 0.010f, awningY);
        glVertex2f(lx + 0.030f, awningY);
        glVertex2f(lx + 0.035f, awningY - awningD);
        glVertex2f(lx + 0.005f, awningY - awningD);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(s.cx - 0.008f, awningY);
        glVertex2f(s.cx + 0.008f, awningY);
        glVertex2f(s.cx + 0.010f, awningY - awningD);
        glVertex2f(s.cx - 0.010f, awningY - awningD);
        glEnd();
        // Awning fringe (short dangling lines)
        glColor3ub((unsigned char)clampb(s.ar - 20), (unsigned char)clampb(s.ag - 20), (unsigned char)clampb(s.ab - 20));
        glLineWidth(1.2f);
        glBegin(GL_LINES);
        for (float fx = lx - 0.010f; fx <= rx + 0.010f; fx += 0.016f) {
            float fbase = awningY - awningD;
            glVertex2f(fx, fbase);
            glVertex2f(fx, fbase - 0.010f);
        }
        glEnd();

        // --- Hanging light bulb under awning ---
        if (faisal_isNight || cityLights) {
            float bx2 = s.cx, by2 = awningY - awningD - 0.012f;
            // wire
            glColor3ub(60, 60, 60); glLineWidth(1.0f);
            glBegin(GL_LINES);
            glVertex2f(bx2, awningY - awningD);
            glVertex2f(bx2, by2 + 0.006f);
            glEnd();
            // glow
            blendOn();
            for (int h = 4;h >= 1;h--) {
                glColor4f(1.0f, 0.90f, 0.50f, 0.10f * h * 0.5f);
                drawCircle(bx2, by2, h * 0.020f, 14);
            }
            blendOff();
            glColor3f(1.0f, 0.95f, 0.70f);
            drawCircle(bx2, by2, 0.008f, 10);
        }

        // --- Sign board above counter ---
        glColor3ub(30, 30, 40);
        glRectf(lx + 0.020f, awningY - 0.005f, rx - 0.020f, awningY + 0.018f);
        glColor3ub(s.gr, s.gg, s.gb);
        drawText(lx + 0.024f, awningY + 0.003f, s.label, GLUT_BITMAP_HELVETICA_10);

        // --- Shopkeeper silhouette ---
        float px2 = s.cx, py2 = groundY;
        glColor3ub(35, 32, 42);
        drawCircle(px2, py2 + 0.095f, 0.014f, 10);      // head
        glRectf(px2 - 0.010f, py2 + 0.040f, px2 + 0.010f, py2 + 0.090f); // body
    }
}


static void drawRain() {
    if (!isRaining) return;
    blendOn(); glLineWidth(1.1f);
    glBegin(GL_LINES);
    for (int i = 0;i < MAX_RAIN;i++) {
        glColor4f(0.72f, 0.78f, 1.0f, 0.30f + 0.22f * rainSpeedMult);
        glVertex2f(rain[i].x, rain[i].y);
        glColor4f(0.72f, 0.78f, 1.0f, 0.0f);
        glVertex2f(rain[i].x - 0.010f * rainSpeedMult, rain[i].y - 0.048f * rainSpeedMult);
    }
    glEnd(); blendOff();
}

static void drawSnow() {
    if (!isSnow) return;
    blendOn();
    for (int i = 0;i < MAX_SNOW;i++) {
        float alpha = 0.70f + 0.30f * sinf(frameCount * 0.03f + i);
        glColor4f(0.92f, 0.95f, 1.0f, alpha);
        drawCircle(snow[i].x, snow[i].y, 0.005f + sinf((float)i * 2.3f) * 0.002f, 6);
    }
    blendOff();
}

static void drawFog() {
    if (fogDensity <= 0.01f) return;
    blendOn();
    glColor4f(0.76f, 0.79f, 0.84f, fogDensity * 0.65f);
    glRectf(-1.0f, -0.28f, 1.0f, 0.22f);
    glColor4f(0.76f, 0.79f, 0.84f, fogDensity * 0.35f);
    glRectf(-1.0f, -1.0f, 1.0f, -0.28f);
    blendOff();
}

// ============================================================
// HUD
// ============================================================
static void drawHUD() {
    blendOn(); glColor4f(0, 0, 0, 0.48f);
    glRectf(-1.0f, -1.0f, 1.0f, -0.86f); blendOff();
    glColor3f(1, 1, 1);
    char buf[80]; sprintf(buf, "Speed: %d km/h", (int)(metroSpeed * 385.0f));
    drawText(-0.98f, -0.96f, buf, GLUT_BITMAP_HELVETICA_12);
    char wx[80] = "";
    if (isRaining)strcat(wx, "[RAIN] ");
    if (isSnow)   strcat(wx, "[SNOW] ");
    if (isFog)    strcat(wx, "[FOG] ");
    strcat(wx, faisal_isNight ? "[NIGHT]" : "[DAY]");
    glColor3f(0.80f, 0.92f, 1.0f);
    drawText(-0.98f, -0.91f, wx, GLUT_BITMAP_HELVETICA_10);
    glColor3f(0.72f, 0.72f, 0.72f);
    drawText(0.05f, -0.96f, "R=Rain  N=Night  M=Day  F=RainSpd  G=Fog", GLUT_BITMAP_HELVETICA_10);
    drawText(0.05f, -0.91f, "K=Snow  L=Lights  P=Platform  T=Train2  B=Cars  W/S=Speed", GLUT_BITMAP_HELVETICA_10);
}

// ============================================================
// Display — DRAW ORDER IS CRITICAL FOR LAYERING
// ============================================================
void displayfaisal() {
    drawSky();
    drawStars();
    drawMoon();
    drawSun();
    drawCloud(-0.82f, 0.76f, 1.05f);
    drawCloud(-0.18f, 0.83f, 0.78f);
    drawCloud(0.32f, 0.79f, 1.18f);
    drawCloud(0.70f, 0.87f, 0.68f);
    drawBuildings();
    drawInfrastructure();        // viaduct + pillars + road
    drawMarketStalls();          // stalls + ground fill under bridge
    drawStreetLamps();
    drawTreesUnderViaduct();     // trees between pillars (before cars is fine)
    drawPlatform();
    drawTrafficCars();           // cars on road
    drawTreesRoadside();         // roadside trees AFTER cars — always in front

    // Train body (on rails, above viaduct deck)
    drawTrainBody(metroX, 1.0f);
    if (showMetro2) drawTrainBody(metro2X, -1.0f);

    // Redraw rail surface on top of train body bottom edge
    // This makes the wheels look embedded in the rail and fixes
    // the headlight-behind-rail issue by giving headlight a clean surface
    redrawRailSurface();

    drawRain();
    drawSnow();
    drawFog();

    // Headlights LAST — drawn over everything including redrawn rails
    drawTrainHeadlight(metroX, 1.0f);
    if (showMetro2) drawTrainHeadlight(metro2X, -1.0f);

    drawHUD();
    //glutSwapBuffers();
}

// ============================================================
// Update
// ============================================================
void updatefaisal(int value) {
    frameCount++;
    updateWindowStates();  // slowly refresh window lit states
    sunAngle += 0.12f;
    cloudOff += 0.00028f; if (cloudOff > 2.2f)cloudOff = -2.2f;
    metroX += metroSpeed; if (metroX > 1.68f)metroX = -1.68f;
    if (showMetro2) { metro2X -= metroSpeed * 0.82f; if (metro2X < -1.68f)metro2X = 1.68f; }
    if (isRaining) {
        for (int i = 0;i < MAX_RAIN;i++) {
            rain[i].y -= rain[i].speed * rainSpeedMult;
            if (rain[i].y < -1.0f) { rain[i].y = 1.0f;rain[i].x = frand(-1.0f, 1.0f); }
        }
    }
    if (isSnow) {
        for (int i = 0;i < MAX_SNOW;i++) {
            snow[i].y -= snow[i].speed;
            snow[i].x += sinf(frameCount * 0.018f + i * 0.7f) * 0.0009f;
            if (snow[i].y < -1.0f) { snow[i].y = 1.0f;snow[i].x = frand(-1.0f, 1.0f); }
        }
    }
    fogDensity += (fogTarget - fogDensity) * 0.022f;
    if (showTraffic) {
        for (int i = 0;i < MAX_CARS;i++) {
            cars[i].x += cars[i].speed * (cars[i].dir ? 1.0f : -1.0f);
            if (cars[i].x > 1.25f)cars[i].x = -1.25f;
            if (cars[i].x < -1.25f)cars[i].x = 1.25f;
        }
    }
    /*glutPostRedisplay();
    glutTimerFunc(16, updatefaisal, 0);*/
}

// ============================================================
// Keyboard
// ============================================================
void keyboardfaisal(unsigned char key, int, int) {
    switch (key) {
    case 'r':case 'R': isRaining = !isRaining; break;
    case 'n':case 'N': faisal_isNight = true;  break;
    case 'm':case 'M': faisal_isNight = false; break;
    case 'f':case 'F': rainSpeedMult = (rainSpeedMult >= 3.0f) ? 1.0f : rainSpeedMult + 1.0f; break;
    case 'g':case 'G': isFog = !isFog; fogTarget = isFog ? 0.52f : 0.0f; break;
    case 'k':case 'K': isSnow = !isSnow; break;
    case 'l':case 'L': cityLights = !cityLights; break;
    case 'p':case 'P': showPlatform = !showPlatform; break;
    case 't':case 'T': showMetro2 = !showMetro2; if (showMetro2)metro2X = 1.68f; break;
    case 'b':case 'B': showTraffic = !showTraffic; break;
    case 'w':case 'W': metroSpeed = fminf(metroSpeed + 0.003f, 0.042f); break;
    case 's':case 'S': metroSpeed = fmaxf(metroSpeed - 0.003f, 0.002f); break;
    case 27: exit(0);
    }
}

void initFaisal()
{
    initRain();
    initSnow();
    initStars();
    initCars();
    initFlicker();
}

// ============================================================
// Entry
// ============================================================


//int main(int argc, char** argv) {
//    srand((unsigned)time(nullptr));
//    initRain(); initSnow(); initStars(); initCars(); initFlicker();
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowSize(1280, 720);
//    glutCreateWindow("Dhaka MRT-6 Metro Scene v3");
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glutDisplayFunc(displayfaisal);
//    glutKeyboardFunc(keyboardfaisal);
//    glutTimerFunc(16, updatefaisal, 0);
//    glutMainLoop();
//    return 0;
//}
