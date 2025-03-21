#include "combine.h"
#include <iostream>
#include <cmath> 
#include <cstdlib> 


Combine::Combine(int number_atoms) : interaction_energy(1.0) {
    atoms.resize(number_atoms); 
}

void Combine::randomise_energy_step(double beta) {
    
    int index = rand() % atoms.size();
    int spin_left = atoms[(index - 1 + atoms.size()) % atoms.size()].current_spin();
    int spin_right = atoms[(index + 1) % atoms.size()].current_spin();
    int new_spin = atoms[index].current_spin();
    double energy_change = 2 * interaction_energy * new_spin * (spin_left + spin_right);


    if (energy_change < 0 || (rand() / (double)RAND_MAX) < exp(-beta * energy_change)) {
        atoms[index].flip_spin(); 
    }
}

double Combine::calculate_total_energy() const {
    double total_energy = 0.0;
    for (size_t i = 0; i < atoms.size(); i=i+1) {
        int spin_left = atoms[(i - 1 + atoms.size()) % atoms.size()].current_spin();
        int spin_right = atoms[(i + 1) % atoms.size()].current_spin();
        total_energy = total_energy - (interaction_energy * atoms[i].current_spin() * (spin_left + spin_right));
    }
    return total_energy;
}

