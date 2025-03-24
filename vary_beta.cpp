#include vary_beta.h
#include <fstream>
#include <iostream>
#include <cmath>

varybeta::varybeta(int number_atoms, int num_steps, int num_configurations, const std::vector<double>& beta_values)
    : number_atoms(number_atoms),
      beta_values(beta_values)
      num_steps(num_steps)
      num_configurations(num_configurations) {}

void vary_beta::run(const std::string& output_filename) {
    std::ofstream data_file_2(vary_beta_1D);
    data_file << "beta,avg_energy,avg_magnetization\n";
    
    for (double beta : beta_values) {
        double total_energy = 0.0;
        double total_magnetization = 0.0;
        }
}