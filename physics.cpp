#include <iostream>
#include <cmath>
#include "header.h"
using namespace std;

float speed_missile = 120.f;
float speed_jet = 100.f;
float A = 100;
float dt = 0.01f;
float phi = PI/4;

void PurePursuit(obj& state,float time, float dx, float dy, float dist){
    state.jx += speed_jet * dt;
    state.jy = A * sin(phi * time);
    state.my -= speed_missile * dy/dist * dt;
    state.mx += speed_missile * dx / dist * dt;

    state.jx_d = speed_jet;
    state.jy_d = A * phi * cos(phi * time);

    state.thetaJ = atan2(state.jy_d, state.jx_d);
    state.thetaM = atan2(dy,dx);
}

void PN(obj& state,control& u, float dt, float dx,float dy,float dist){
    float Vc;
    float los_d;
    float Rx = dx;
    float Ry = dy;
    float R = dist;

    float relVx = state.jx_d - state.mx_d;
    float relVy = state.jy_d - state.my_d;

    los_d = (Rx*relVy - Ry*relVx)/(R*R);

    Vc = -1*(Rx*relVx + Ry*relVy)/R;

    const float N = 4.0f;

    float a_cmd = N * Vc * los_d;

    float omegaDesired =a_cmd / sqrt(state.mx_d*state.mx_d + state.my_d*state.my_d);
    float error = omegaDesired - state.thetaM_d;

    float alpha = 1.0f * error;

    u.a = a_cmd;
    u.alpha = alpha;
} 

void physics(float dx, float dy, float& time){
    float dist = sqrt(dx * dx + dy * dy);
    time += dt;

    switch(choice){
        case '1':
            PurePursuit(state,time,dx,dy,dist);
            break;
        case '2':
            PN(state,u,time,dx,dy,dist);
            break;
    }

    state.dist = dist;
}