#include "2d_model.h"
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <time.h>

model_2d::model_2d(int grid_dimensions, double beta) 
    : size(grid_dimensions), beta(beta)        {        
    grid.resize(size, std::vector<int>(size, 1));
    std::srand(std::time(0));          
}

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
}


void model_2d::monte_carlo_step() {
    int x = std::rand() % size;
    int y = std::rand() % size;

    
    int left = grid[x][(y-1 + size) % size];
    int right = grid[x][(y+1) % size];
    int above = grid[(x-1 + size) % size][y];
    int below = grid[(x+1) % size][y];
    int spin = grid[x][y];
    double energy_change = 2 * spin * (left + right + above + below);
}

double model_2d::calculate_energy() const {
    double energy = 0.0;
    for (int row = 0; row < size; row = row + 1) {
        for (int col = 0; col < size; col = col + 1) {
            energy = energy - (grid[row][col] * (grid[row][(col+1)%size] + grid[(row+1)%size][col]));
        }
    }
    return energy;
}

double model_2d::calculate_average_magnetization() const {
    double total_magnetization = 0.0;
    
    for (int row = 0; row < size; row = row + 1) {
        for (int col = 0; col < size; col = col + 1) {
            
            total_magnetization = total_magnetization + grid[row][col];
        }
    }
 
    double overall_spins = size * size;
    double average_magnetization = std::abs(total_magnetization) / overall_spins;
    
    return average_magnetization;
}

void model_2d::simulate_grid(int num_steps, const std::string& file_name) {
    std::ofstream file(file_name);
    file << "beta,energy,magnetization\n";

    random_grid();
    for (int step = 0; step < num_steps; step = step + 1) {
        monte_carlo_step();
        if (step % 1000 == 0) { 
            file << beta << "," << calculate_energy() << "," << calculate_average_magnetization() << "\n";
        }
    }
    file.close();
}
