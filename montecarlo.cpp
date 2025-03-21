#include "monte_carlo.h"
#include <iostream>

Montecarlo::Montecarlo(int number_atoms, double beta) 
    : combine(number_atoms), beta(beta) {}

void Montecarlo::run_simulation(int num_steps) {
    for (int step = 0; step < num_steps; ++step) { 
        combine.randomise_energy_step(beta); 
    }
}

double Montecarlo::get_current_energy() const {
    return combine.calculate_total_energy();
}

int Montecarlo::get_current_magnetization() const {
    return combine.magnetization_calculation();
}