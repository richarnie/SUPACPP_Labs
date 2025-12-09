#include "FiniteFunctions.h"
#include "CustomFunctions.h"
#include <cmath>
#include <random>
#include <vector>

gaussian::gaussian(double range_min, double range_max, std::string outfile, double mu, double sigma): FiniteFunction(range_min, range_max, outfile){
    m_mu = mu; //mean of gaussian
    m_sigma = sigma; //standard deviation of gaussian
}

double gaussian::gaussian_func(double x){
    return (1/(m_sigma*pow(M_PI*2, 0.5)))*exp(-0.5*pow(((x-m_mu)/m_sigma),2.));
}
double gaussian::callFunction(double x){return this->gaussian_func(x);};
void gaussian::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "mean: " << m_mu << std::endl;
  std::cout << "standard deviation: " << m_sigma << std::endl;
}

std::vector<double> gaussian::sampling(int num_points){
    std::vector<double> sampled_array;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> distribution(m_RMin,m_RMax);
    std::uniform_real_distribution<double> t_dist(0,1);
    double x_i = distribution(rng);

    while((int)sampled_array.size() < num_points){
        std::normal_distribution<double> distribution_normal(x_i,0.5);
        double gen_y = distribution_normal(rng);

        double t_val = t_dist(rng);
        double A_val = std::min(callFunction(gen_y)/callFunction(x_i), 1.);
        //add a condition so that it doesn't produce values outside of the range which was causing a crash during plotting
        if(t_val < A_val && (gen_y <= m_RMax) && (gen_y >= m_RMin)){
            sampled_array.push_back(gen_y);
            x_i = gen_y;
        }
        else{continue;}
    }
return sampled_array;
}


cauchy::cauchy(double range_min, double range_max, std::string outfile, double x_0, double gamma):FiniteFunction(range_min, range_max, outfile){
    m_x0 = x_0; // centre of distribution
    m_gamma = gamma; //scale parameter
}
double cauchy::cauchy_func(double x){
    return 1/(M_PI*m_gamma*(1+pow(((x-m_x0)/m_gamma),2)));
}
double cauchy::callFunction(double x){return this->cauchy_func(x);};

void cauchy::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "mean: " << m_x0 << std::endl;
  std::cout << "gamma: " << m_gamma << std::endl;
}

std::vector<double> cauchy::sampling(int num_points){
    std::vector<double> sampled_array;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> distribution(m_RMin,m_RMax);
    std::uniform_real_distribution<double> t_dist(0,1);
    double x_i = distribution(rng);

    while((int)sampled_array.size() < num_points){

        std::normal_distribution<double> distribution_normal(x_i,0.5);
        double gen_y = distribution_normal(rng);
        double t_val = t_dist(rng);
        double A_val = std::min(callFunction(gen_y)/callFunction(x_i), 1.);

        if(t_val < A_val  && (gen_y <= m_RMax) && (gen_y >= m_RMin)){
            sampled_array.push_back(gen_y);
            x_i = gen_y;
        }
        else{continue;}
    }
return sampled_array;
}

crystal_ball::crystal_ball(double range_min, double range_max, std::string outfile, double mu, double sigma, double alpha, double n): FiniteFunction(range_min, range_max, outfile){
    m_mu = mu; //mean
    m_sigma = sigma; //standard deviation
    m_alpha = alpha; // switch from gaussian to power law
    m_n = n; //power law tail
}
double crystal_ball::cb_func(double x){
    //crystal ball constants
    double A = pow(m_n/std::abs(m_alpha), m_n) * exp(-pow(abs(m_alpha),2)/2);
    double B = m_n/abs(m_alpha) - abs(m_alpha);
    double C = (m_n/abs(m_alpha)) * (1/(m_n-1)) * (exp(-pow(abs(m_alpha),2)/2));
    double D = pow(M_PI/2, 0.5) * (1 + std::erf(abs(m_alpha)/pow(2,0.5)));
    double N = 1/(m_sigma*(C + D));

    if((x-m_mu)/m_sigma > -m_alpha){
        return N * exp(-(pow((x-m_mu), 2))/2*pow(m_sigma, 2));
    }
    else{
        return N*A*pow((B - (x-m_mu)/m_sigma), -m_n);
    }
}
double crystal_ball::callFunction(double x) {return this->cb_func(x);}; //(overridable)

void crystal_ball::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "mean: " << m_mu << std::endl;
  std::cout << "standard deviation: " << m_sigma << std::endl;
  std::cout << "alpha: " << m_alpha << std::endl;
  std::cout << "n: " << m_n << std::endl;
}

std::vector<double> crystal_ball::sampling(int num_points){
    std::vector<double> sampled_array;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> distribution(m_RMin,m_RMax);
    std::uniform_real_distribution<double> t_dist(0,1);
    double x_i = distribution(rng);

    while((int)sampled_array.size() < num_points){

        std::normal_distribution<double> distribution_normal(x_i,0.5);
        double gen_y = distribution_normal(rng);

        double t_val = t_dist(rng);
        double A_val = std::min(callFunction(gen_y)/callFunction(x_i), 1.);

        if(t_val < A_val  && (gen_y <= m_RMax) && (gen_y >= m_RMin)){
            sampled_array.push_back(gen_y);
            x_i = gen_y;
        }
        else{continue;}
    }
return sampled_array;

}

