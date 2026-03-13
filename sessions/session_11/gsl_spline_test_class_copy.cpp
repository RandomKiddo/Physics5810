//  file: gsl_spline_test_class.cpp
// 
//  Test program for the gsl spline routines using the Spline class
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/10/09 -- created from gsl_cubic_spline_test.cpp
//
//  Notes:
//   * uses the GSL interpolation functions (see online documentation) 
//
//*****************************************************************
// include files
#include <iostream>    // cout and cin
#include <iomanip>     // manipulators like setprecision
#include <cmath>
#include <string>     // C++ strings                                 
using namespace std;    
#include "GslSpline.h"  // Header file for the GSL Spline class
#include <fstream>
#include <gsl/gsl_integration.h>

inline double sqr (double z) {return z*z;}  // inline function for z^2

inline double u(double r) { return 2*r*exp(-r); }
inline double u1(double r) { return 2*(1-r)*exp(-r); }
inline double u4(double r) { return 2*(r-4)*exp(-r); }

// GSL wrapper for problem 4F
double spline_integral_function(double r, void *params);

int
main (void)
{
  cout << "--- Derivative Accuracy --- \n";

  // A cubic spline is bounded by the fourth derivative
  // For u(r) = 2re^-r, u^(4)(r) = 2(r-4)e^(-r)
  // The error is bounded by h^2 u^(4)(r)

  double r_min = 0.9;
  double r_max = 4.1;
  double max_error = 1e-4;

  // The h is bounded by the following: max_error = h^2 |u^(4)(r)|
  // Hence we can calculate h by rearranging that using our inline functions
  double h = sqrt(max_error / max(abs(u4(r_min)), abs(u4(r_max))));
  cout << "Calculated h: " << h << "\n";

  // The number of points N is based on h and the range we are using
  int N = static_cast<int>((r_max-r_min)/h) + 1;
  cout << "Calculated N: " << N << "\n";
  
  // We define step sizes and two new arrays to hold r and u(r)
  // We then populate the arrays
  double dr = (r_max-r_min)/(N-1);
  double *x_values = new double[N];
  double *y_values = new double[N];
  for (int i = 0; i < N; ++i) {
    double r = r_min + i*dr;

    x_values[i] = r;
    y_values[i] = u(r);
  }

  // Our cubic spline
  Spline spline(x_values, y_values, N, "cubic");

  // The output file with headers
  // We can inspect this later and see the 1e-4 absolute tolerance
  ofstream fout("radial_data.dat");
  fout << "# r      Exact       Approx       Abserr\n";

  // Iterate over our range and calculate the first derivative
  // We compare it to the spline value and return the absolute error
  for (double r = r_min; r <= r_max; r += dr) {
    double exact = u1(r);
    double approx = spline.yp(r);

    fout << setprecision(8) << r << " "
         << setprecision(8) << exact << " "
         << setprecision(8) << approx << " "
         << setprecision(8) << abs(exact-approx) << "\n";
  }

  // Close the file
  cout << "Data outputted to radial_data.dat\n";
  fout.close();

  // Delete the dynamic arrays
  delete[] x_values;
  delete[] y_values;

  // Now we do the integration portion
  cout << "\n--- Integration Accuracy --- \n";

  r_min = 0.0;
  r_max = 15.0;
  max_error = 1e-4;  // 0.01%

  // Starting N=10 and massive initial relative error
  N = 10;
  double relative_error = 1.0;

  // Output data file
  ofstream fout2("radial_data_integral.dat");
  fout2 << "# N       Result       Relerr\n";

  // Loop while we're not at the tolerance
  while (relative_error > max_error) {
    // The spacing for our given N and dynamics arrays
    double dr = (r_max-r_min) / (N-1);
    double *x = new double[N];
    double *y = new double[N];

    // Populate the arrays with r and u(r) values
    for (int i = 0; i < N; ++i) {
      x[i] = r_min + i*dr;
      y[i] = u(x[i]);
    }

    // Create the spline
    Spline spline(x, y, N, "cubic");

    // Greate the GSL workspace and put in the spline inteagral function
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
    double result, abs_err;
    gsl_function F;
    F.function = &spline_integral_function;
    F.params = &spline;

    // Integrate via QAGS
    gsl_integration_qags(&F, r_min, r_max, 0, 1e-7, 1000, w, &result, &abs_err);

    // calculate the new relative error
    // we know by normalization that the integral should be 1.0
    relative_error = abs(1.0-result)/1.0;

    // Output the relative error to data file
    fout2 << N << " " << setprecision(8) << result << " " << setprecision(8) << relative_error << "\n";

    // If we are at the tolerance threshold, stop
    if (relative_error <= max_error) {
      break;
    }

    // Delete the dynamic arrays and free the workspace
    // Increment the N value, since we are not at the tolerance yet
    delete[] x;
    delete[] y;
    gsl_integration_workspace_free(w);
    N += 10;

    // Some max value to prevent infinite iterations to stop trying
    if (N > 10000) {
      cerr << "Could not reach specified tolerance in 10,000 iterations.\n";
      break;
    }
  }

  // Output the calculated values
  cout << "Calculated N: " << N << "\n";
  cout << "Calculated h: " << (r_max-r_min) / (N-1) << "\n";

  // Close the file
  cout << "Data outputted to radial_data_integral.dat\n";
  fout2.close();

  return (0);      // successful completion 
}

// GSL wrapper for problem 4F that returns u(r)^2 
double spline_integral_function(double r, void *params) {
  Spline *s = static_cast<Spline*>(params);

  double val = s->y(r);
  return val*val;
}
