#ifndef VARY_BETA_H 
#define VARY_BETA_H
#include "montecarlo.h"
#include "combine.h"
#include <string>
#include <vector> //  Includes necessary inbuilt libraries, header guards and other header files.

class vary_beta {

private:
    int number_atoms;
    std::vector<double> beta_values;
    int num_configurations;
    int num_steps;

public:
    vary_beta(int number_atoms, const std::vector<double>& beta_values, int num_steps, int num_configurations);

    void run_all_betas(const std::string& file_name);
};

// Has many private variables, the numbers of steps and configurations and the betas e.t.c are
// are only used in this class, so can remain provate. THe function of vary_beta and the running of
// this are public to be implemented in main.cpp.


#endif