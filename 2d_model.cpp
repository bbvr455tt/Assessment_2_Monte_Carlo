#include "2d_model.h"
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

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

}

double model_2d::calculate_energy() const {
    double energy = 0.0;
    for (int row = 0; row < size; row = row + 1) {
        for (int col = 0; col < size; col = col + 1) {
            const int spin_state = grid[row][col];
            energy = energy - (spin_state * ((grid[row][(col+1)%size] + grid[(row+1)%size][col])));
        }
        for (int row = 0; row < size - 1; row = row + 1) {
            const int spin_state = grid[row][size - 1]; 
            energy = energy - (spin_state * (grid[row][0] + grid[row + 1][size - 1])); 
        }
        
        for (int col = 0; col < size - 1; col = col + 1) {
            const int spin_state = grid[size - 1][col];
            energy = energy - (spin_state * (grid[size - 1][col + 1] + grid[0][col]));
        }
        
        
        const int final_spin = grid[size - 1][size - 1];
        energy = energy - (final_spin * (grid[size - 1][0] + grid[0][size - 1]));

    }
    return energy / 2.0;
}

double model_2d::calculate_average_magnetization() const {
    double total_magnetization = 0.0;
    
    for (int row = 0; row < size; row = row + 1) {
        for (int col = 0; col < size; col = col + 1) {
            
            total_magnetization = total_magnetization + grid[row][col];
        }
    }
 
    double overall_spins = size * size;
    double average_magnetization = std::abs(total_magnetization)     / overall_spins;
    
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

void test_2x2_system() {
    const int test_size = 2;
    model_2d test_model(test_size, 1.0);
    
    
    for (int config = 0; config < 16; config = config + 1) {
        
        test_model.grid[0][0] = (config & 1) ? 1 : -1;
        test_model.grid[0][1] = (config & 2) ? 1 : -1;
        test_model.grid[1][0] = (config & 4) ? 1 : -1;
        test_model.grid[1][1] = (config & 8) ? 1 : -1;
        
        double energy = test_model.calculate_energy();
        double mag = test_model.calculate_average_magnetization();
        
        std::cout << "Config " << config << ": Energy = " << energy 
                  << ", Magnetization = " << mag << std::endl;
    }
}
