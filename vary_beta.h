#ifndef VARY_BETA_H 
#define VARY_BETA_H
#include "montecarlo.h"
#include "combine.h"
#include <string>
#include <vector>

class vary_beta {

private:
    int number_atoms;
<<<<<<< HEAD
    std::vector<double> beta_values;
=======
    std::vector<ouble> beta_values;
>>>>>>> vary_beta
    int num_configurations
    int num_steps

public:
    vary_beta(int number_atoms, const std::vector<double>& beta_values, int num_steps, int num_configurations);

    void run_all_betas(const std::string& "1d_vary_beta");
};




#endif