#include <iostream>
#include <Eigen/Dense>
#include <spdlog/spdlog.h>
#include <math.h>
#include <cmath>
#include "header.h"
using namespace std;

int main(){
    obj state;
    state.jx = 0;
    state.my = 0;
    render(state);
}