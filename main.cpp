#include "montecarlo.h"
#include "combine.h"      
#include <cstdlib>
#include <fstream>       
#include <time.h>
#include <iostream>      

int main() {
    
    srand(time(0));

    const int number_atoms = 100; 
    const double beta = 1.0;      
    const int num_steps = 10000; 
    const int num_configurations = 2000;   
    
    std::ofstream data_file("constant_beta_1D.csv");
    data_file << "energy,magnetization\n";

    for (int i=0; i < num_configurations; i = i+1) {
        Montecarlo full_sim(number_atoms, beta);
        full_sim.run_simulation(num_steps);
 
        data_file << full_sim.get_current_energy() << ","
                  << full_sim.get_current_magnetization() << "\n";
    }
              
    data_file.close();
    return 0;
 
}
