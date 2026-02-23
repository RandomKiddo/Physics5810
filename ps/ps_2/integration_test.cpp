/**
 * File: integration_test.cpp
 * 
 * Tests the integration routines for a non-trivial integrand exp(-x)*cos(x).
 * 
 * Programmer: Neil Ghugare ghugare.1@osu.edu
 * 
 * Revision History:
 * 02-18-2026 Created original version
 * 
 * Notes:
 * Answers to questions in PS2 are placed at the *bottom* of this file
 */

// Include libraries
#include "integration.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

// Main function
int main(void) {
    // This is a test function of our non-trivial integrand
    // We use the 'Integrand' definition in integration.h
    // We'll use this in our routines
    Integrand test_func = [](double x) { 
        return std::exp(-x)*std::cos(x);
    };

    // Define the exact values we wish to test
    double a = 0.0;
    double b = M_PI;
    double exact = 0.5*(std::exp(-M_PI) + 1.0);

    // Open an output file stream and add the data headers
    std::ofstream out("errors.dat");
    out << "# ERROR OUTPUTS FOR SIMPSON, MILNE, AND GSL -- PS2\n";
    out << "# n   Simpson_Err   Milne_Err\n";

    // Loop over different values of n, the total number of iterations
    // We need to update the loop by multiplying by 2 by the behavior of our implemented routines
    // Note: We cannot update the iteration amount of the GSL routine, so we don't output that error
    //       It has a static error value that doesn't change during this loop
    for (int n = 4; n <= std::pow(2.0, 20.0); n *= 2) {
        double res_simp = integrate_simpson(test_func, a, b, n);

        double res_milne = integrate_milne(test_func, a, b, n);

        auto [res_gsl, error] = integrate_gsl(test_func, a, b);

        double err_simp = std::abs(res_simp-exact)/std::abs(exact);
        double err_milne = std::abs(res_milne-exact)/std::abs(exact);

        out << n << " " 
            << std::scientific << std::setprecision(10) << err_simp << " "
            << std::scientific << std::setprecision(10) << err_milne << "\n"; 
    }

    // Close the output file
    out.close();
    std::cout << "Data file 'errors.dat' generated.\n\n";

    // Bonus: evaluating an integral using Simpson/Milne and GSL, and then using method in notes.
    // We choose equation 9: integral(0, 2) 1/((1+x)*sqrt(x)) dx = 1.910633236249019

    // The integrand and the transformed version from the Session 4 notes options
    Integrand equation9 = [](double x) { 
        if (x == 0.0) { return 0.0; }
        return 1.0/((1.0+x)*std::sqrt(x));
    };
    Integrand equation9_transformed = [](double u) {
        return 2.0/(1.0+u*u);
    };
    exact = 1.910633236249019;  // Update exact value

    // We choose to use Simpson, and we choose the optimal N from our earlier graph = 10,000 
    // Note: we must update the boudns for the transformed integral from [0, 2] to [0, sqrt(2)]
    double res_simpson = integrate_simpson(equation9, 0.0, 2.0, 10000);
    double res_simpson_transformed = integrate_simpson(equation9_transformed, 0.0, std::sqrt(2.0), 10000);
    double err_simpson = std::abs(res_simpson-exact)/std::abs(exact);
    double err_simpson_transformed = std::abs(res_simpson_transformed-exact)/std::abs(exact);

    // And now with GSL
    auto [res_gsl, err] = integrate_gsl(equation9, 0.0, 2.0);
    auto [res_gsl_transformed, err_transformed] = integrate_gsl(equation9_transformed, 0.0, std::sqrt(2.0));

    // Output to the terminal
    // The discussion for this result is appended at the end of the file in a comment
    std::cout << "Bonus 1: Integrating with singularities:\n"
              << "Actual result: 1.910633236249019\n\n"
              << "Simpson: " << std::setprecision(13) << res_simpson << "\n"
              << "Simpson (transformed): " << std::setprecision(13) << res_simpson_transformed << "\n"
              << "GSL: " << std::setprecision(13) << res_gsl << "\n"
              << "GSL (transformed): " << std::setprecision(13) << res_gsl_transformed << "\n\n"
              << "Error Simpson: " << std::setprecision(13) << err_simpson << "\n"
              << "Error Simpson (transformed): " << std::setprecision(13) << err_simpson_transformed << "\n"
              << "Error GSL: " << std::setprecision(13) << err << "\n"
              << "Error GSL (transformed): " << std::setprecision(13) << err_transformed << "\n\n";

    return 0;
}

/**
 * Answer to Question 1b (on the analysis of the plot returned from plot_errors.plt)
 * 
 * There are two regions for each routine. The left side is truncation error, while the right side is
 * round-off error. From mathematical analysis, we would predict that the truncation error relates to
 * the order/global error of the method. So, for Simpson's rule, which is 2nd order with a cancelled
 * out 3rd order term, we would anticipate the slope to be -4 (which it is, by looking at the exponent
 * of the fit). Likewise, for the Milne integration routine, we would predict a slope of -6 (which it 
 * is). The right side is due to round-off error and should be roughly the same for both methods. This
 * is because N is so large (so h becomes small), that the computer cannot resolve it better than its
 * own machine precision. The slope being close to 0.5 is roughly what we would expect for this
 * region. See the fits and values in the errors.pdf file.
 */

/**
 * Answer to Question 1c (on the analysis of the graph for optimal N)
 * 
 * From looking at the graph, the optimal N to use for Milne integration is about N=1000. Analytically,
 * the truncation error goes as h^6 which means it goes as N^-6. The round-off error should go as rough-
 * ly sqrt(N)*epsilon, where epsilon is the machine precision. So the total error is these two added to-
 * gether. We can differentiate with respect to N, set that to 0, and solve, getting that the optimal N
 * is roughly equal to (12/epsilon)^2/13. This number is roughly 400, meaning our estimate is only a fac-
 * tor of 2-3 off, which is good agreement. The disagreement likely comes from the high-order Milne inte-
 * gration routine allowing the truncation error to stay dominant for longer and also approximations of 
 * both the round-off and truncation errors (i.e., round-off approximately equals epsilon*sqrt(N)).
 */

/**
 * Answer to Question 1d (on the analysis of Simpson/GSL via brute force and substitution)
 * 
 * We integrated equation 9, which has a singularity at x=0 (vertical asymptote). The disparity in accuracy
 * between the original and transformed integrand (via substitution) shows how the convergence of a method
 * like Simpson is limited by the behavior of the integrand. While the original function's singularity at
 * x=0 caused the truncation error to dominate, the u=sqrt(x) transformation removed the singularity, all-
 * owing both methods (GSL/Simpson) to reach the machine precision limit (closer to 1e-16). GSL's better 
 * performance on the original integrand also shows the value of the adaptive division methods when these 
 * kinds of transformations are not possible, with the original error still being relatively small at 2e-9.
 * 
 * Below is the attached terminal output:
    Bonus 1: Integrating with singularities:
    Actual result: 1.910633236249019

    Simpson: 1.892832453911
    Simpson (transformed): 1.910633236249
    GSL: 1.910633236228
    GSL (transformed): 1.910633236249

    Error Simpson: 0.009316692497836
    Error Simpson (transformed): 3.835101276115e-15
    Error GSL: 1.831005159656e-09
    Error GSL (transformed): 2.121229010498e-14
 */