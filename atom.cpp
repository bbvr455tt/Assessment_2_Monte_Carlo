#include "atom.h" 
#include <cstdlib> // Include libraries and header file 

Atom::Atom() {
    int random_num = rand() % 2; 
    spin = (random_num == 1) ? 1 : -1; 
} // Generates a random spin, either + or -1

void Atom::flip_spin() {
    spin = -spin;
} // An operation to flip the spin state of an atom.


int Atom::current_spin() const {
    return spin;
} // Allows the spin of the atom to be found and read.