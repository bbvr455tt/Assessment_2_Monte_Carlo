#ifndef TWOD_MODEL_H  
#define TWOD_MODEL_H
#include "montecarlo.h"
#include "vary_beta.h"
#include <vector>
#include <string> // Inlcudes header guards, all other header files needed and the libraries for the code. 

class model_2d {

private:
    std::vector<std::vector<int>> grid;
    double beta;
    int size;
// These private variables like size, a substitute for the grid dimensions, the grid
// vector and these specific beta values will all be kept within this class.    

public:
    model_2d(int grid_dimensions, double beta);
    void random_grid();
    double calculate_average_magnetization() const;
    void monte_carlo_step();
    double calculate_energy() const;

    void simulate_grid(int num_steps, const std::string& file_name);

    void set_spin(int row, int col, int value);
    int get_spin(int row, int col) const;
    
    static void test_2x2_system();

};
    // This object has many helpful functions to be implemented in main.cpp to 
    // calculate the values at different betas in the grid. It includes the test function.

#endif

