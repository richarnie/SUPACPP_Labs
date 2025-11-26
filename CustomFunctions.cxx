#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


std::vector<std::vector<float>> read_file(std::ifstream& data){
    //reads the text file into a 2d array with the first column being x data and the second column being y
    int index = 0;
    std::string x_val;
    std::string y_val;
    std::vector<std::vector<float>> input_vals;
    //using a comma delimeter alone doesn't create two separate value
    while (getline(data, x_val, ',') && getline(data, y_val)){
        if (index != 0){
        input_vals.push_back({std::stof(x_val), std::stof(y_val)});
        }
        index++;

    }

    data.close();

    return input_vals;
}
void write_file(std::vector<float> data, std::string filename){
    std::fstream text_file;
    text_file.open(filename, std::ios_base::out);
    for (int i = 0; i < (int)data.size(); i++){
        text_file << data[i] << std::endl;
        std::cout << data[i] << std::endl;
    }
    text_file.close();
}
void write_file(std::string data, std::string filename){
    std::fstream text_file;
    text_file.open(filename, std::ios_base::out);
    text_file << data << std::endl;
    text_file.close();
}
void print_output(std::vector<float> out_arr){
    for(float val: out_arr){
        std::cout << val << std::endl;
    }
}
void print_output(std::string out_string){
    std::cout << out_string << std::endl;
}

void print_file(std::ifstream& data){
    std::vector<std::vector<float>> val_arr = read_file(data);
    int num_lines;
    std::cout << "How many lines do you want printed? " << std::endl;
    std::cin >> num_lines;

    if(num_lines > (int)val_arr.size()){
        std::cout << "more lines than in file" << std::endl;
        for (int i = 0; i < 5; i++){
            std::cout << val_arr[i][0] << " " << val_arr[i][1] << std::endl;
        }
    }
    else if(num_lines <=0){
        std::cout << "zero or less, invalid input";
    }
    else{
        for (int i = 0; i < num_lines; i++){
            std::cout << val_arr[i][0] << " " << val_arr[i][1] << std::endl;
        }
    }
}


std::vector<float> magnitude(std::ifstream& data){
    std::vector<std::vector<float>> val_arr = read_file(data);
    std::vector<float> magnitude;
    float mag_vals;

    for (int i = 0; i < (int)val_arr.size(); i++){
        mag_vals = sqrt(val_arr[i][0]*val_arr[i][0] + val_arr[i][1]*val_arr[i][1]);
        magnitude.push_back(mag_vals);
        }
    print_output(magnitude);

return magnitude;
}


std::string least_squares(std::ifstream& data, std::ifstream& err){
    int index = 0;
    std::string x_val;
    std::string y_val;

    float xx_sum = 0;
    float xy_sum = 0;
    float x_sum = 0;
    float y_sum = 0;
    float pred_y;

    float p_val;
    float q_val;

    std::vector<float> xy_arr;
    std::vector<float> x_arr;
    std::vector<float> y_arr;
    std::vector<float> xx_arr;
    std::vector<float> sigma_vals = magnitude(err);
    int num_data = 0;
    std::fstream fit_result;


    while (getline(data, x_val, ',') && getline(data, y_val)){
        if (index != 0){
            xy_arr.push_back(std::stof(x_val)*std::stof(y_val));
            x_arr.push_back(std::stof(x_val));
            y_arr.push_back(std::stof(y_val));
            xx_arr.push_back(std::stof(x_val)*std::stof(x_val));
        }
        index++;
        num_data++;
    }
    data.close();
    for (int i = 0; i < (int) x_arr.size(); i++){
        x_sum += x_arr[i];
        xy_sum += xy_arr[i];
        xx_sum += xx_arr[i];
        y_sum += y_arr[i];
    }

    p_val = (num_data*x_sum - x_sum*y_sum)/(num_data*xx_sum - x_sum*x_sum);
    q_val = (xx_sum*y_sum - xy_sum*x_sum)/(num_data*xx_sum - x_sum*x_sum);

    float chi_val = 0;
    for (int i = 0; i < (int)x_arr.size(); i++){
        pred_y = p_val*x_arr[i] + q_val;
        chi_val += ((y_arr[i] - pred_y)/sigma_vals[i])*((y_arr[i] - pred_y)/sigma_vals[i]);
    }


    fit_result.open("fit_values.txt", std::ios_base::out);
    fit_result << "y = " << p_val << "x + " << q_val << std::endl << "chi squared = " << chi_val/(x_arr.size()-1);
    fit_result.close();
    std::string results = "y = " + std::to_string(p_val) + "x + " + std::to_string(q_val) + " chi squared = " + std::to_string(chi_val/(x_arr.size()-1));
    print_output(results);
    return results;
}

std::vector<float> power(std::vector<std::vector<float>> data, float n = 1., int i = 0, std::vector<float> vals = {}, float counter = 0.){
    //n is used to hold the current value of x^y, i is a counter to get the position in the y array, counter is used to track if x^y has been reached
    if(i > (int)data.size()-1){
        return vals;
    }
    else if(round(data[i][1]) > round(counter)){
        n=n*data[i][0];
        return power(data, n, i, vals, counter + 1);
    }
    else if (round(data[i][1]) == 0.){
        vals.push_back(1.);
        return power(data, 1, i+1, vals, 0.);

    }
    else if(round(data[i][1]) >= round(counter) && i <= (int)data.size()-1){
        vals.push_back(n);
        return power(data, 1, i+1, vals, 0.);
    }
    else if(i > (int)data.size()-1){
        print_output(vals);
        return vals;
    }

}