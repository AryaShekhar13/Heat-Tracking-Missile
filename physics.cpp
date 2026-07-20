#include <iostream>
#include <cmath>
#include "header.h"
using namespace std;

void physics(float dx, float dy, float& time){
    float dist = std::sqrt(dx * dx + dy * dy);

    float speed_missile = 120.f;
    float speed_jet = 100.f;
    float A = 100;
    float dt = 0.01f;
    time += dt;
    float phi = PI/4;

    state.jx += speed_jet * dt;
    state.jy = A * sin(phi * time);
    state.my -= speed_missile * dy/dist * dt;
    state.mx += speed_missile * dx / dist * dt;

    state.jx_d = speed_jet;
    state.jy_d = A * phi * std::cos(phi * time);

    state.thetaJ = atan2(state.jy_d, state.jx_d);
    state.thetaM = atan2(dy,dx);

    state.dist = dist;
}