#ifndef MONTECARLO_H
#define MONTECARLO_H
#include "combine.h"
#include "atom.h"

class Montecarlo {

public:

    Montecarlo(int number_atoms, double beta);
    void run_simulation(int num_steps);

    double get_current_energy() const;
    int get_current_magnetization() const;

private:
    Combine combine; 
    double beta;
};

#endif