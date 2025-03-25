#include "montecarlo.h"
#include "combine.h"
#include "vary_beta.h"      
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

    vary_beta vary_beta(number_atoms, beta_values, num_steps, num_configurations);
    vary_beta.run_all_betas("1d_vary_beta");

    return 0;
 
}
