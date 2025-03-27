#ifndef TWOD_MODEL_H  
#define TWOD_MODEL_H
#include "montecarlo.h"
#include "vary_beta.h"
#include <vector>
#include <string>

class model_2d {

private:
    std::vector<std::vector<int>> grid;
    double beta;
    int size;
    

public:
    model_2d(int grid_dimensions, double beta);
    void random_grid();
    double calculate_average_magnetization() const;
    void monte_carlo_step();
    double calculate_energy() const;

    void simulate_grid(int num_steps, const std::string& file_name);

    void set_spin(int row, int col, int value);
    int get_spin(int row, int col) const;
    void test_2x2_system();

};
    

#endif

