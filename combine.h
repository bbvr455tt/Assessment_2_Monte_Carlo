#ifndef COMBINE_H
#define COMBINE_H
#include <vector> 
#include "atom.h" 

class Combine {
public:
    Combine(int number_atoms);
    void randomise_energy_step(double beta);
    double calculate_total_energy() const;
    int magnetization_calculation() const;

private:
    std::vector<Atom> atoms;
    double interaction_energy;
};

#endif