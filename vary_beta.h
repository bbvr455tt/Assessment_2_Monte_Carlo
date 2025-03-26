#ifndef VARY_BETA_H 
#define VARY_BETA_H
#include "montecarlo.h"
#include "combine.h"
#include <string>
#include <vector>

class vary_beta {

private:
    int number_atoms;
    std::vector<double> beta_values;
    int num_configurations;
    int num_steps;

public:
    vary_beta(int number_atoms, int num_steps, int num_configurations, const std::vector<double>& beta_values);

<<<<<<< HEAD
    void run_all_betas(const std::string& filename);
=======
    void run_all_betas(const std::string& file_name);
>>>>>>> 2d_model
};




#endif