#pragma once

struct obj{
    float mx;
    float my;
    float jx;
    float jy;
    float jx_d;
    float my_d;
    float thetaM;
};

extern obj state;
// float PI = 3.14159265f;

void render(obj& state);
void physics(float dx, float dy);