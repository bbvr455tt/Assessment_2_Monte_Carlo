#include "vary_beta.h"
#include <fstream>
#include <iostream>
#include <cmath> // Included the necessary libraries and the header file.

vary_beta::vary_beta(int number_atoms, int num_steps, int num_configurations, const std::vector<double>& beta_values)
    : number_atoms(number_atoms),
      num_steps(num_steps),
      num_configurations(num_configurations),
      beta_values(beta_values) {}
      // This initializes the object with each of the parameters
      // being outlined and initialized.

void vary_beta::run_all_betas(const std::string& filename) {
    std::ofstream data_file_2(filename);
    data_file_2 << "beta,avg_energy,avg_magnetization\n";
    // This writes the following function all into a separate file to keep the data
    // as the results.

    for (double beta : beta_values) {
        double total_energy = 0.0;
        double total_magnetization = 0.0;
        // This loops over all the values in the range of betas in the beta values lists
        // and initializes the energy and magnetisation before the calculation.

        for (int i = 0; i < num_configurations; i=i+1) {
            Montecarlo full_sim(number_atoms, beta);  
            full_sim.run_simulation(num_steps);
            // This bit loops again through the number of configurations and runs the full 
            // montecarlo simulation in the previous object to use the random generation to 
            // run through the simulate the energies at each random configuration.

            total_energy = total_energy + full_sim.get_current_energy();
            total_magnetization = total_magnetization + std::abs(full_sim.get_current_magnetization());
        }
        

        double average_energy = total_energy / num_configurations;
        double average_magnetization = total_magnetization / num_configurations;
        
        data_file_2 << beta << "," << average_energy << "," << average_magnetization << "\n";

    }
    // // The loop then gets the total energies and mag from all configurations and divides by how 
    // many configurations there are to get an average value at each beta, and then writes that
    // value into a data file.
    data_file_2.close();
}
