#ifndef ATOM_H
#define ATOM_H // Header guards

class Atom {
    
public:
    Atom();
    int current_spin() const;  
    void flip_spin(); //
// The public section which includes the atom object and the
// various functions of the atom.cpp file.    

private:
    int spin;
};
//Private section stores the atoms spin state only within the 
//object to be obtained by either function.
#endif