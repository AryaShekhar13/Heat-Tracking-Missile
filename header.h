#pragma once

struct obj{
    float mx;
    float my;
    float jx;
    float jy;

    float thetaM;
    float thetaJ;

    float jx_d;
    float jy_d;
};

extern obj state;
constexpr float PI = 3.14159265f;

void render(obj& state);
void physics(float dx, float dy, float& t);