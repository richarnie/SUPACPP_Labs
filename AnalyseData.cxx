//Richarnie Burrows-Chambers   26/11/2025
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "/workspaces/SUPACPP_Labs/CustomFunctions.h"

int main(){
    std::string chosenFunc;
    std::cout << "What function would you like to use?" << std::endl;
    std::cout << "MAG for calculating magnitude, LEAST: to get a least squares fit to the data, PRINT: to list a chosen number of entries, POWER: to get x^y for all x. Input exit to close the program " << std::endl;
    std::cin >> chosenFunc;

    while (chosenFunc != "exit"){
    std::ifstream data("/workspaces/SUPACPP_Labs/Exercises/Lab1and2/input2D_float.txt");
    std::ifstream err("/workspaces/SUPACPP_Labs/Exercises/Lab1and2/error2D_float.txt");
    if (chosenFunc == "MAG"){
            std::vector<float> magnitudes = magnitude(data);
            write_file(magnitudes, "magnitude.txt");
    }
    else if(chosenFunc == "PRINT"){
        print_file(data);
    }
    else if(chosenFunc == "LEAST"){
        std::string line_fit = least_squares(data, err);
        write_file(line_fit, "line_fit.txt");
    }
    else if(chosenFunc == "POWER"){
        std::vector<float> exponents = power(read_file(data), 1., 0, {}, 0.);
        write_file(exponents, "power.txt");
    }

    else{
        std::cout << "Invalid input, please try again" << std::endl;
    }
    std::cout << "MAG for calculating magnitude, LEAST: to get a least squares fit to the data, PRINT: to list a chosen number of entries, POWER: to get x^y for all x. Input exit to close the program " << std::endl;
    std::cin >> chosenFunc;
}


    return 0;
}
