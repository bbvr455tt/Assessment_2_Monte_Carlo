#include "atom.h"
#include <cstdlib> 

Atom::Atom() {
    int random_num = rand() % 2; 
    spin = (random_num == 1) ? 1 : -1; 
}

void Atom::flip_spin() {
    spin = -spin;
}


int Atom::current_spin() const {
    return spin;
}