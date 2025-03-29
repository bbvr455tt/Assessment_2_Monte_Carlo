#include "2d_model.h"
#include <fstream>
#include <cmath>
#include <cstdlib> // Includes header file and required libraries.

model_2d::model_2d(int grid_dimensions, double beta) 
    : size(grid_dimensions), 
      beta(beta)     
      // This sets up the model_2d class to take the beta and
      // grid dimension values.   
{        
    grid.resize(size);          
    for (int i = 0; i < size; i=i+1) {
        grid[i].resize(size, 1); 
    }
}
// Grid here is defined in the header file as a 2d vector with
// a size number of rows and loops throuhg to produce the same number
// (size) of columns as well.
void model_2d::random_grid() {
    for (int row = 0; row < size; row = row + 1) {
        for (int col = 0; col < size; col = col +1) {
            int rand_val = rand() % 2;

            if (rand_val == 0) {
                grid[row][col] = -1;
            } else {
                grid[row][col] = 1;
            }
        }
    }
} // This function is very simple and runn through every position in the grid
// andd assigns randomly 0 or 1 and then from this randomly assigns up or down
// spin.

void model_2d::monte_carlo_step() {
    int x = rand() % size;
    int y = rand() % size;
    
    int left = grid[x][(y-1 + size) % size];
    int right = grid[x][(y+1) % size];
    int above = grid[(x-1 + size) % size][y];
    int below = grid[(x+1) % size][y];
    int spin = grid[x][y];
    double energy_change = 2 * spin * (left + right + above + below);
// This is an important function of the code. It randomly selects a place in
// the grid to potentially undergo a spin flip. The neighbouring spins are all
// checked so the energy in the atoms specific configuration is calculated.
    bool to_flip = false;

    if (energy_change < 0) {
        to_flip = true ;
    }
    else {
        double random_chance = (double)rand() / RAND_MAX;
        double flip_chance = exp(-beta*energy_change);

        if (random_chance < flip_chance) {
            to_flip = true;
        }
    }
    if (to_flip) {
        grid[x][y]= grid[x][y]*-1;
    }
// This loop checks if the calculates energy change is less than zero or runs the 
//probability of the spin flip occuring to the probability function by generrating a
//random number between 0 and 1. If either of these are true, the spin is flipped.
}

double model_2d::calculate_energy() const {
    double energy = 0.0;
    for (int row = 0; row < size; row = row + 1) {
        for (int col = 0; col < size; col = col + 1) {
            const int spin_state = grid[row][col];
            energy = energy - (spin_state * ((grid[row][(col+1)%size] + grid[(row+1)%size][col])));
        }

    } 
    return energy;
}
// This is a very simple function that once again runs through each position in the grid
// (with a for loop for the col and row) and looks at the spins of the right and below neighbour.
// This prevents counting places more than once. These neighbouring spins are used to calculate the
// particles contribution to the energy. These energies are combined for the whole grid to give the
// energy of the configuration. 

double model_2d::calculate_average_magnetization() const {
    double total_magnetization = 0.0;
    
    for (int row = 0; row < size; row = row + 1) {
        for (int col = 0; col < size; col = col + 1) {
            
            total_magnetization = total_magnetization + grid[row][col];
        }
    }
 
    double overall_spins = size * size;
    double average_magnetization = total_magnetization / overall_spins;
    
    return average_magnetization;
} // This function returns the average magnetisation of particles within a configuration.
// It loops through each position in the grid and adds up the whole magnetisation by adding up
// all the spins and then finding the average of each position by dividing the total spin
// by the number of particles in the grid.  

void model_2d::simulate_grid(int num_steps, const std::string& file_name) {
    std::ofstream file(file_name);
    file << "beta,energy,magnetization\n"; 
    //This sets up the final function in the class to run the simulation of the grid.
    // It writes the results into a file and sets up the parameters this function
    // can take. 

    random_grid();
    for (int step = 0; step < num_steps; step = step + 1) {
        monte_carlo_step();
        if (step % 1000 == 0) { 
            file << beta << "," << calculate_energy() << "," << calculate_average_magnetization() << "\n";
        }
    }
    file.close();
}
// Then the random grid is ran from above and set up, and the montecarlo step is ran for the number
// of times the simulation is to be ran. Then afterr every 1000 steps it writes the energy and mag
// into the file.