#pragma once

struct obj{
    float mx;
    float my;
    float jx;
    float jy;

    float thetaM;
    float thetaJ;

    float thetaM_d;
    float thetaJ_d;

    float thetaM_dd;
    float thetaJ_dd;

    float jx_d;
    float jy_d;
    float mx_d;
    float my_d;

    float jx_dd;
    float jy_dd;
    float mx_dd;
    float my_dd;

    float dist;
};

struct control{
    float a;
    float alpha;
};
extern obj state;
extern control u;
constexpr float PI = 3.14159265f;
extern char choice;

void render(obj& state);
void physics(float dx, float dy, float& t);
void dynamics(obj& state, float dt);
void rk4(float dt, float dval, float val);
void PurePursuit(obj& state,float time, float dx, float dy, float dist);
void PN(obj& state,control& u, float dt, float dx,float dy,float dist);