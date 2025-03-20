#ifndef ATOM_H
#define ATOM_H

class Atom {
    
public:
    Atom();
    int current_spin() const;  
    void flip_spin(); 
    

private:
    int spin;
};

#endif