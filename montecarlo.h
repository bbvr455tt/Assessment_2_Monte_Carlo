#ifndef MONTECARLO_H
#define MONTECARLO_H
#include "combine.h"
#include "atom.h" // Has necesarry header files and guards

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
// Once again, the object defined (Montecarlo) and its useful
// functions are defined publicly to be used throughout the code, and the
// combine and beta variables are used only within this code, so
// are private.
#endif