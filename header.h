#pragma once

struct obj{
    float mx;
    float my;
    float jx;
    float jy;
    float jx_d;
    float my_d;
};

extern obj state;

void render(obj& state);
void physics(float dx, float dy);