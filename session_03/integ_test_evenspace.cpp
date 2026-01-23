//  file: integ_test.cpp
//
//  This is a test program for basic integration methods.               
//                                                                     
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//               Ralf Bundschuh (bundschuh.2@osu.edu)
//
//  Revision history:
//      04-Jan-2004  original version, for 780.20 Computational Physics
//      08-Jan-2005  changed functions to pass integrand
//      09-Jan-2011  updated functions
//      11-Jan-2018  replaced float by macro
//
//  Notes:
//   * define with floats to emphasize round-off error  
//   * compile with:  "g++ -Wall -c integ_test.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez  
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau                           
// 
//************************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <gsl/gsl_integration.h>
using namespace std;

#include "./integ_routines.h"	// prototypes for integration routines

// GSL-compatible wrapper
double my_integrand_gsl(double x, void *p) {
    return exp(-x);
}

FLOAT my_integrand (FLOAT x);
double my_integrand_gsl(double x, void *p);

const double ME = 2.7182818284590452354E0;	// Euler's number 

//************************************************************************

int
main ()
{
  // set up the integration specifiction
  const int max_intervals = 501;	// maximum number of intervals
  const FLOAT lower = 0.0;	// lower limit of integration
  const FLOAT upper = 1.0;	// upper limit of integration
  const FLOAT logN_min = log10(3.0);
  const FLOAT logN_max = log10((max_intervals));
  const int n_points = 40;

  const double answer = 1. - 1. / ME;	// the "exact" answer for the test 
  FLOAT result = 0.;  // approximate answer

  // GSL Setup
  gsl_function F;
  F.function = &my_integrand_gsl;
  F.params = NULL;
  double gsl_result, gsl_error;

  // open the output file stream
  ofstream integ_out ("integ4.dat");	// save data in integ.dat
  integ_out << "#  N   trapezoid     Simpsons      Gauss   GSL" << endl;
  integ_out << "#---------------------------------------------" << endl;

  // Simpson's rule requires an odd number of intervals  
  for (int k=0; k <= n_points; ++k)
  {
    FLOAT logN = logN_min + k*(logN_max-logN_min)/(n_points-1);
    int i = static_cast<int>(round(pow(10.0, logN)));

    // Simpson rule needs odd i
    if (i % 2 == 0) { i += 1; }
    if (i > max_intervals) { break; }

    integ_out << setw(8) << log10(i);

    result = trapezoid_rule (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs (result - answer) / answer);

    result = simpsons_rule (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs (result - answer) / answer);

    result = gauss_quadrature (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs (result - answer) / answer);
    
    gsl_integration_workspace * w = gsl_integration_workspace_alloc (i);
    gsl_integration_qag (&F, lower, upper, 0, 1e-12, i, 
                          3, w, &gsl_result, &gsl_error);
    
    integ_out << "  " << scientific << log10(fabs (gsl_result - answer) / answer);
    gsl_integration_workspace_free (w);

    integ_out << endl;
  }

  cout << "data stored in integ.dat\n";
  integ_out.close ();

  return (0);
}

//************************************************************************

// the function we want to integrate 
FLOAT
my_integrand (FLOAT x)
{
  return (exp (-x));
}
