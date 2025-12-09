class gaussian : public FiniteFunction{
    public:
        gaussian(); //default constructor
        gaussian(double range_min, double range_max, std::string outfile, double mu, double sigma);
        double gaussian_func(double x);
        double callFunction(double x);
        void printInfo(); //Dump parameter info about the current function (Overridable)
        std::vector<double> sampling(int num_points);

    private:
        double m_mu;
        double m_sigma;
};

class cauchy : public FiniteFunction{
    public:
        cauchy();
        cauchy(double range_min, double range_max, std::string outfile, double x_0, double gamma);
        double cauchy_func(double x);
        double callFunction(double x);
        void printInfo(); //Dump parameter info about the current function (Overridable)
        std::vector<double> sampling(int num_points);


    private:
        double m_x0;
        double m_gamma;
};

class crystal_ball : public FiniteFunction{
    public:
        crystal_ball();
        crystal_ball(double range_min, double range_max, std::string outfile, double mu, double sigma, double alpha, double n);
        double cb_func(double x);
        double callFunction(double x);
        void printInfo(); //Dump parameter info about the current function (Overridable)
        std::vector<double> sampling(int num_points);


    private:
        double m_mu;
        double m_sigma;
        double m_alpha;
        double m_n;
};