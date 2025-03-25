#include "2d_model.h"
#include <fstream>
#include <cmath>
#include <cstdlib>

2d_model::2d_model(int grid_dimensions, double beta) 
    : size(grid_dimensions), 
      beta(beta)        
{        
    grid.resize(size);          
    for (int i = 0; i < size; i=i+1) {
        grid[i].resize(size, 1); 
    }
}

void 2d_model::monte_carlo_step() {
    int x = rand() % size;
    int y = rand() % size;

    
    int left = grid[x][(y-1 + size) % size];
    int right = grid[x][(y+1) % size];
    int above = grid[(x-1 + size) % size][y];
    int below = grid[(x+1) % size][y];
    int spin = grid[x][y];
    double energy_change = 2 * spin * (left + right + above + below);
}