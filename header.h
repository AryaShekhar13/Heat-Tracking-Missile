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
    float mx_d;
    float my_d;

    float jx_dd;
    float jy_dd;
    float mx_dd;
    float my_dd;


    float dist;

    float missileTurnRate;
    float jetTurnRate;
};
extern obj state;
constexpr float PI = 3.14159265f;

void render(obj& state);
void physics(float dx, float dy, float& t);
void dynamics(obj& state, float dt);
void rk4(float dt, float dval, float val);