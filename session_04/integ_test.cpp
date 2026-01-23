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

using namespace std;

#include "./integ_routines.h"	// prototypes for integration routines

FLOAT my_integrand (FLOAT x);
FLOAT integrand_brute(FLOAT x);
FLOAT integrand_subtraction(FLOAT x);
FLOAT integrand_transformed(FLOAT u);

const double ME = 2.7182818284590452354E0;	// Euler's number 

//************************************************************************

int
main ()
{
  // set up the integration specifiction
  const int max_intervals = 10000;	// maximum number of intervals
  const FLOAT lower = 0.0;	// lower limit of integration
  const FLOAT upper = 2.0;	// upper limit of integration

  const double answer = 1. - 1. / ME;	// the "exact" answer for the test 
  FLOAT result = 0.;  // approximate answer

  cout << "Brute Force:" << endl;
  cout << "-----------------------------" << endl;
  result = trapezoid_rule(max_intervals, lower, upper, &integrand_brute);
  cout << "Trapezoid: " << setprecision(8) << result << endl;
  result = simpsons_rule(max_intervals, lower, upper, &integrand_brute);
  cout << "Simpson: " << setprecision(8) << result << endl << endl;

  cout << "Subtraction:" << endl;
  cout << "-----------------------------" << endl;
  result = trapezoid_rule(max_intervals, lower, upper, &integrand_subtraction) + 2*sqrt(2);
  cout << "Trapezoid: " << setprecision(8) << result << endl;
  result = simpsons_rule(max_intervals, lower, upper, &integrand_subtraction) + 2*sqrt(2);
  cout << "Simpson: " << setprecision(8) << result << endl << endl;

  cout << "Transformation:" << endl;
  cout << "-----------------------------" << endl;
  result = trapezoid_rule(max_intervals, lower, sqrt(upper), &integrand_transformed);
  cout << "Trapezoid: " << setprecision(8) << result << endl;
  result = simpsons_rule(max_intervals, lower, sqrt(upper), &integrand_transformed);
  cout << "Simpson: " << setprecision(8) << result << endl;

  return (0);
}

//************************************************************************

// the function we want to integrate 
FLOAT
my_integrand (FLOAT x)
{
  return (exp (-x));
}

FLOAT integrand_brute(FLOAT x) {
  if (x == 0) return 0;
  return 1.0 / ((1.0+x) * sqrt(x));
}


FLOAT integrand_subtraction(FLOAT x) {
  if (x == 0) return 0;
  return (1.0/(1.0+x) - 1.0) / sqrt(x);
}

FLOAT integrand_transformed(FLOAT u) {
  return 2.0 / (1.0 + u*u);
}
