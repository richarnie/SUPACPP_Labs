#include <iostream>
#include "FiniteFunctions.h"
#include "CustomFunctions.h"
#include <random>
#include <vector>

int main(){
    std::string val;
    std::vector<double> input_vals;
    std::ifstream data("/workspaces/SUPACPP_Labs/Data/MysteryData20000.txt");

    while (getline(data, val)){
        input_vals.push_back(std::stod(val));
    }

    data.close();

    FiniteFunction init_func(-10,10,"out_file1");
    init_func.integral(10000);
    init_func.plotFunction();
    init_func.plotData(input_vals, 100, true);
    init_func.printInfo();

    gaussian func_1(-10, 10, "out_file2", -2, 1);
    func_1.integral(10000);
    func_1.plotFunction();
    std::vector<double> sampled_data = func_1.sampling(10000);
    func_1.plotData(sampled_data, 100, false);
    func_1.plotData(input_vals, 100, true);
    func_1.printInfo();

    cauchy func_2(-10, 10, "out_file3", -2, 0.9);
    func_2.integral(10000);
    func_2.plotFunction();
    std::vector<double> sampled_data2 = func_2.sampling(10000);
    func_2.plotData(sampled_data2, 100, false);
    func_2.plotData(input_vals, 100, true);
    func_2.printInfo();

    crystal_ball func_3(-10, 10, "out_file4", -2, 1, 3, 2);
    func_3.integral(10000);
    func_3.plotFunction();
    std::vector<double> sampled_data3 = func_3.sampling(10000);
    func_3.plotData(sampled_data3, 100, false);
    func_3.plotData(input_vals, 100, true);
    func_3.printInfo();


}