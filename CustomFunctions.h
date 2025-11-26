#pragma once

std::vector<float> magnitude(std::ifstream&);
std::vector<std::vector<float>> read_file(std::ifstream&);
void print_file(std::ifstream&);
std::string least_squares(std::ifstream&, std::ifstream&);
std::vector<float> power(std::vector<std::vector<float>>, float n, int i, std::vector<float>, float counter);
void write_file(std::vector<float>, std::string);
void write_file(std::string, std::string);
void print_output(std::vector<float>);
void print_output(std::string);