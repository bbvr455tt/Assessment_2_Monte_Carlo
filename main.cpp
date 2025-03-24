#include "montecarlo.h"
#include "combine.h"      
#include <cstdlib>       
#include <time.h>
#include <iostream>      

int main() {
    
    srand(time(0));

    int number_atoms = 100; 
    double beta = 1.0;      
    int num_steps = 10000;      

     Montecarlo full_sim(number_atoms, beta);

     full_sim.run_simulation(num_steps);
 
     std::cout << "Energy: " << full_sim.get_current_energy() << std::endl;
     std::cout << "Magnetization: " << full_sim.get_current_magnetization() << std::endl;
 
     return 0;
 }