#include "montecarlo.h"
#include <iostream> // Include header and library.

Montecarlo::Montecarlo(int number_atoms, double beta) 
    : combine(number_atoms), beta(beta) {}
// Initializes the function with the beta value and the number of atoms.

void Montecarlo::run_simulation(int num_steps) {
    for (int step = 0; step < num_steps; step = step + 1) { 
        combine.randomise_energy_step(beta); 
    }
} // This simply runs the randomise energy step for every step in the 
// simulation.

double Montecarlo::get_current_energy() const {
    return combine.calculate_total_energy();
}

int Montecarlo::get_current_magnetization() const {
    return combine.magnetization_calculation();
}
// Both these functions are very simple and use the combine functions to get
// the energy and magnetization using the logic from the combine object.