#pragma once

extern float h1x;
extern float h2x;
extern float h3x;
extern float h4x;

extern int h1dir;
extern int h2dir;
extern int h3dir;
extern int h4dir;

extern float h1speed;
extern float h2speed;
extern float h3speed;
extern float h4speed;

void drawHuman(float x, float y);
void drawHuman2(float x, float y);
void drawHuman3(float x, float y);
void drawHuman4(float x, float y);

void CarDesign(int brakeFlag);
void Car2Design(int brakeFlag);
void Car3Design(int brakeFlag);
void Car4Design(int brakeFlag, int lightFlag);
void Car5Design(int brakeFlag);
void Car6Design(int brakeFlag);
void drawHuman(float x, float y);

typedef struct {
    float x;
    float y;
    float speed;
    int brake;
} Car;

#define NUM_LOWER 3
#define NUM_UPPER 3

extern Car lowerLane[NUM_LOWER];
extern Car upperLane[NUM_UPPER];
void initCars();

