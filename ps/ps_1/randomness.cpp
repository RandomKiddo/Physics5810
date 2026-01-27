/**
 * file: randomness.cpp
 * 
 * Randomness of round-off errors via N samples of numbers between 1.0
 * and 10.0. The scheme is as follows: Using a step size, calculate a 
 * number x. Take the square root of that number and save a casted float 
 * version of that number as well. Find the relative error epislon via
 * (float z - double z) / double z. The data is outputted to a file. 
 * 
 * Programmer:  Neil Ghugare  ghugare.1@osu.edu
 * 
 * Revision history:
 *      27-Jan-2026  Created initial version for PS1
 * 
 * Notes:
 *      Compile with: "g++ randomness.cpp -o randomness.x"
 *      Adapted from "Projects in Computational Physics" by Landau and Paez
 *      Data saved as: Iteration Epsilon 
 */

/*
Exploring the results:

When making a histogram plot with GNUPlot, we get this "shelf" of uniform
errors. The distribution is symmetric around zero (no systematic bias) and
the shape is relatively uniform. It's not a perfect square because we aren't
just looking at one ronuding event, but a combination of the initial representation
error and the rounding error of the operation itself. Also the Central Limit
Theorem applies here, causing this triangular/trapezoidal distribution. Since 
machine precision for floats is about 1e-7, we expect a range of [-5e-8, 5e-8],
which is exactly what we get. So, we back up the claim from Landau and Paez.
*/

#include <iostream>
#include <cmath>    // for math functionality
#include <fstream>  // for file output
#include <iomanip>  // for setting precision

int main(int argc, char** argv) {
    const int N = 1000000;              // number of samples
    const double start = 1.0;           // the start number 
    const double end = 10.0;            // the stop number
    const double step = (end-start)/N;  // calculated step size

    // open the output file 
    std::ofstream fout("randomness.dat");
    fout << "#    i    epsilon";

    for (int i = 0; i < N; ++i) {
        // calculate the current number from the current step
        double x = start + i*step;

        // get the double-precision square root and the single-precision version
        double z_true = std::sqrt(x);
        float z_approx = static_cast<float>(std::sqrt(static_cast<double>(x)));

        // calculate the epsilon between the two
        double epsilon = (static_cast<double>(z_approx) - z_true)/z_true;

        // output to the file
        fout << i << " " << std::scientific << std::setprecision(10) << epsilon << "\n";
    }

    // close the file and output to the terminal where the data is stored
    fout.close();
    std::cout << "Data written to randomness.dat" << "\n";
    
    return 0;
}