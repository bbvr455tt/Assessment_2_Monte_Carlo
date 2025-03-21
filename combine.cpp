#include "Chain.h"
#include <iostream>
#include <cmath> 
#include <cstdlib> 


Chain::Chain(int number_atoms) : interaction_energy(1.0) {
    atoms.resize(number_atoms); 
}