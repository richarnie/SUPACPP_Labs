#include <iostream>
#include<math.h>

void mag_calc(){
    float x;
    float y;
    std::cout << "Enter the x value: " << std::endl;
    std::cin >> x;
    std::cout << "Enter the y value: " << std::endl;
    std::cin >> y;
    float magnitude = sqrt(x*x + y*y);
    std::cout << magnitude << std::endl;
}

int main(){
std::cout << "Hello World!" << std::endl;

float x = 7.5;
float y = 3.4;

float magnitude = sqrt(x*x + y*y);

std::cout << magnitude << std::endl;
mag_calc();
}