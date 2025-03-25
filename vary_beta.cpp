#include "vary_beta.h"
#include <fstream>
#include <iostream>
#include <cmath>

vary_beta::vary_beta(int number_atoms, const std::vector<double>& beta_values, int num_steps, int num_configurations)
    : number_atoms(number_atoms),
      beta_values(beta_values)
      num_steps(num_steps)
      num_configurations(num_configurations) {}

void vary_beta::run_all_betas(const std::string& file_name) {
    std::ofstream data_file_2(file_name);
    data_file_2 << "beta,avg_energy,avg_magnetization\n";
    
    for (double beta : beta_values) {
        double total_energy = 0.0;
        double total_magnetization = 0.0;
        
        for (int i = 0; i < num_configurations; i=i+1) {
            Montecarlo full_sim(number_atoms, beta);  
            full_sim.run_simulation(num_steps);       

            total_energy = total_energy + full_sim.get_current_energy();
            total_magnetization = total_magnetization + std::abs(full_sim.get_current_magnetization());
        }

        double average_energy = total_energy / num_configurations;
        double average_magnetization = total_magnetization / num_configurations;
        
        data_file_2 << beta << "," << average_energy << "," << average_magnetization << "\n";

    }
    data_file_2.close();
}