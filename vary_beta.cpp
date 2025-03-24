#include vary_beta.h
#include <fstream>
#include <iostream>
#include <cmath>

varybeta::varybeta(int number_atoms, int num_steps, int num_configurations, const std::vector<double>& beta_values)
    : number_atoms(number_atoms),
      beta_values(beta_values)
      num_steps(num_steps)
      num_configurations(num_configurations) {}