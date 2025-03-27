#ifndef COMBINE_H
#define COMBINE_H
#include <vector> 
#include "atom.h" // Has header file guards, the necessary 
// other header file/object and the vector library.


class Combine {
public:
    Combine(int number_atoms);
    void randomise_energy_step(double beta);
    double calculate_total_energy() const;
    int magnetization_calculation() const;
// Here are the useful functions as defined is the combine.cpp
//file which are made public to be used in other objects and the 
//main code.
private:
    std::vector<Atom> atoms;
    double interaction_energy;
};
// These values are only needed within the combine class.
#endif