#include "combine.h"
#include <iostream>
#include <cmath> 
#include <cstdlib> 


Combine::Combine(int number_atoms) : interaction_energy(1.0) {
    atoms.resize(number_atoms); 
}
// Sets up the object using the Atom objects, with a "number_atoms" amount of Atom objects.

void Combine::randomise_energy_step(double beta) {
    
    int index = rand() % atoms.size();
    // This picks a random atom to potentially be flipped.

    int spin_left = atoms[(index - 1 + atoms.size()) % atoms.size()].current_spin();
    int spin_right = atoms[(index + 1) % atoms.size()].current_spin();
    int new_spin = atoms[index].current_spin();
    double energy_change = 2 * interaction_energy * new_spin * (spin_left + spin_right);
    // This checks the spin of an atoms neighbours and calculates the energy change if the spin 
    // were to be flipped

    if (energy_change < 0 || (rand() / (double)RAND_MAX) < exp(-beta * energy_change)) {
        atoms[index].flip_spin(); 
    } // This is statement generates a random number between 0 and 1 and compares it to the exponential
    // and looks at if energy change is less than zero. If either are true, the spin is flipped.
}

double Combine::calculate_total_energy() const {
    double total_energy = 0.0;

    for (size_t i = 0; i < atoms.size(); i=i+1) {
        // This loop sums over all the atoms in the arrangement.
        int spin_left = atoms[(i - 1 + atoms.size()) % atoms.size()].current_spin();
        int spin_right = atoms[(i + 1) % atoms.size()].current_spin();
        total_energy = total_energy - (interaction_energy * atoms[i].current_spin() * (spin_left + spin_right));
        // This checks the neighbour spins and adds the contribution against energy of the
        // positive interactions with the neighbours. Then the total energy is returned.
    }
    return total_energy;
}

int Combine::magnetization_calculation() const {
    int total_magnetization = 0;
    for (int i = 0; i < atoms.size(); i=i+1) {
        total_magnetization = total_magnetization + atoms[i].current_spin();
    }
    return total_magnetization;
} // This function is similar to the one above but calculates the magnetisation by summing
// the spins in the system so is much simpler.