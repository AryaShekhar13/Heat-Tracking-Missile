#include <iostream>
#include <cmath>
#include "header.h"
using namespace std;

void physics(float dx, float dy){
    float dist = pow((dx*dx+dy*dy),0.5);

    float speed = 1.3;
    state.jx += 1;
    state.my -= speed * dy/dist;
    state.mx += speed * dx / dist;
}