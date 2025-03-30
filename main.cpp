#include "montecarlo.h"
#include "combine.h"
#include "vary_beta.h"  
#include "2d_model.h"    
#include <cstdlib>
#include <fstream>       
#include <time.h>
#include <iostream> // Include every header file with directly used
// functions and all necessary libraries.     

int main() {

    std::cout << "2x2 test" << std::endl;
    model_2d::test_2x2_system();
// This is the test line for the 2x2 gris, so goes at the start
// It returns the results in the terminal and runs the test function.
    srand(time(0));
// Seeds the random number geneator to geneerate differenet random number each time.
    const int number_atoms = 100; 
    const double constant_beta = 1.0;      
    const int num_steps = 10000; 
    const int num_configurations = 2000;   
    // All the key variables are defined here with their values to be changed if necessary for 
    // the first chain of atoms step.
    std::ofstream data_file("constant_beta_1D.csv");
    data_file << "energy,magnetization\n";
// Writes the results of the constant_beta 1d chain simulation into a csv file.
    for (int i=0; i < num_configurations; i = i+1) {
        Montecarlo full_sim(number_atoms, constant_beta);
        full_sim.run_simulation(num_steps);
 // Runs a simple for loop of the number of configurations that are to be ran to get
 // the energies and magnetizations for each configuiration, and these are wirtten
 // into a file so the distribution of these values can be seen.
        data_file << full_sim.get_current_energy() << ","
                  << full_sim.get_current_magnetization() << "\n";
 
    }
              
    data_file.close();

    std::vector<double> beta_values;
    for (double beta=0.05; beta<=2.5; beta=beta+0.05){
        beta_values.push_back(beta);
    } // This sets up a 1D vector of the range of different beta values to be ran
    //through in the coming simulations.

    vary_beta vary_beta(number_atoms, num_steps, num_configurations, beta_values);
    vary_beta.run_all_betas("1d_vary_beta.csv");
 // Vary_beta contains all needed to run the 1D simulation at different Beta values
 // The vary beta function includes all the parameters defined above and the filename
 // then writes all the data into a csv file.

    const int grid_dimensions = 100;
    const int stab_steps = 20000;
    const int steps_2d = 10000;
    int interval = 100;
// These are more new variables which are needed for the 2D grid and their value can be 
// set out here. Grid dimensions is the size of the gris, stab_steps in the number of steps
// to allow the system to reach an equilrium, then steps_2d are the steps where the measurements
// take place. Interval is used to decide how often measurements are taken.
    std::ofstream data_file_2d("2d_vary_beta.csv");
    data_file_2d << "beta,energy,magnetization\n";
// Lays out the files headers' and sets it up to be written out as a csv.
    for (double beta=0.05; beta <= 2.0; beta = beta + 0.05) {
        model_2d beta_model_2d(grid_dimensions, beta);
        beta_model_2d.random_grid();
// This loop runs through the range of values of beta used in the simulation, and at each value
// the random grid to the size of the grid dimensions.
        for (int step = 0; step < stab_steps; step = step + 1) {
            beta_model_2d.monte_carlo_step();
        } // This short loop is the equilibrating step, where the gris is ran through
        // the spin flip test many times at each beta value to reach some form of equilibrium.

        double tot_energy = 0.0;
        double tot_mag = 0.0;
        int samples = 0;
        // These set up the inital variables to be returned in the file.
        for (int i = 0; i < steps_2d; i = i+1) {
            beta_model_2d.monte_carlo_step();
            // This now runs the monte carlo spin flip steps once the thermal equilbrium is reached.
            // It goes for as many 2d_steps (measurement steps) as are decided in the vaariables before.
            tot_energy = tot_energy + beta_model_2d.calculate_energy(); // This line calculates the energy for each step
            // using the calculate energy function in 2d_model.cpp.
            if (i % interval == 0) {
                tot_mag = tot_mag + std::abs(beta_model_2d.calculate_average_magnetization());
                samples =  samples + 1;
            } // This takes and updates the total_magnetisation and the number of samples for 
            // every interval of steps.
        }

        data_file_2d << beta << "," << tot_energy/steps_2d << "," << std::abs(tot_mag/samples) << "\n";

    }    
    data_file_2d.close();

    return 0;
 // Finally the results are written in the csv file, the file is closed and the entire main fucntion is returned in the terminal.
}
