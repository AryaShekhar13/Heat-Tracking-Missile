#include <iostream>
#include <Eigen/Dense>
#include <spdlog/spdlog.h>
#include <math.h>
#include <cmath>
#include "header.h"
using namespace std;

char choice = '1';

int main(){
    cout<<"Enter Which Controller You Want: "<<endl;
    cout<<"1 -> Pure Pursuit"<<endl;
    cout<<"2 -> Proportional Navigation"<<endl;
    cin>>choice;
    render(state);
}