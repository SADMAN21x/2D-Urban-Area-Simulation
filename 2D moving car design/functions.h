#pragma once

void CC(float x, float y, float ra, int r, int g, int b);
void drawSun(float cx, float cy, float r);
void drawRect(float x, float y, float width, float height, float r, float g, float b);
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b);
void drawQuads(float x1, float y1, float x2, float y2, double r, double g, double b);
void drawCircle(float center_x, float center_y, float radius, int segments);
void drawEllipse(float cx, float cy, float rx, float ry, int seg = 24);