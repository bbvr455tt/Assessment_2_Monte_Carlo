#include "montecarlo.h"
#include "combine.h"
#include "vary_beta.h"  
#include "2d_model.h"    
#include <cstdlib>
#include <fstream>       
#include <time.h>
#include <iostream>      

int main() {
    
    srand(time(0));

    const int number_atoms = 100; 
    const double constant_beta = 1.0;      
    const int num_steps = 10000; 
    const int num_configurations = 2000;   
    
    std::ofstream data_file("constant_beta_1D.csv");
    data_file << "energy,magnetization\n";

    for (int i=0; i < num_configurations; i = i+1) {
        Montecarlo full_sim(number_atoms, constant_beta);
        full_sim.run_simulation(num_steps);
 
        data_file << full_sim.get_current_energy() << ","
                  << full_sim.get_current_magnetization() << "\n";
 
    }
              
    data_file.close();

    std::vector<double> beta_values;
    for (double beta=0.05; beta<=2.5; beta=beta+0.05){
        beta_values.push_back(beta);
    }

    vary_beta vary_beta(number_atoms, num_steps, num_configurations, beta_values);
    vary_beta.run_all_betas("1d_vary_beta.csv");

    const int grid_dimensions = 100;
    const int stab_steps = 2000;
    const int steps_2d = 10000;
    
    std::ofstream data_file_2d("2d_vary_beta.csv");
    data_file_2d << "beta,energy,magnetization\n";

    for (double beta=0.05; beta <= 2.0; beta = beta + 0.05) {
        model_2d beta_model_2d(grid_dimensions, beta);
        beta_model_2d.random_grid();

        for (int step = 0; step < stab_steps; step = step + 1) {
            beta_model_2d.monte_carlo_step();
        }

        double tot_energy = 0.0;
        double tot_mag = 0.0;
        for (int i = 0; i < steps_2d; i = i+1) {
            beta_model_2d.monte_carlo_step();
            tot_energy = tot_energy + beta_model_2d.calculate_energy();
            tot_mag = tot_mag + std::abs(beta_model_2d.calculate_average_magnetization());

        }


        data_file_2d << beta << "," << tot_energy/steps_2d << "," << tot_mag/steps_2d << "\n";

    }    
    data_file_2d.close();

    return 0;
 
}
