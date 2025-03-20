#include "Atom.h"
#include <cstdlib> 

Atom::Atom() {
    int random_num = rand() % 2; 
    spin = (random_num == 1) ? 1 : -1; 
}

