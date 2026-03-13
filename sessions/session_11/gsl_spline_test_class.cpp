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

inline double sqr (double z) {return z*z;}  // inline function for z^2

double Breit_Wigner(double E); // function for exact calculation

int
main (void)
{
  // We comment this out to change the table.
  /*
  const int NMAX = 300;   // maximum number of array points 
  double x_values[NMAX], y_values[NMAX];

  // Test: interpolate y = sin(x^2) from xmin to xmax with npts points 
  double xmin = 1.;
  double xmax = 3.;
  int npts = 20;
  double deltax = (xmax - xmin)/double(npts-1);
  for (int i = 0; i < npts; i++)
  {
    double x_temp = xmin + double(i) * deltax;   // grid of x points
    x_values[i] = x_temp;
    y_values[i] = sin (x_temp * x_temp);
  }
  */

  int npts = 9;
  double x_values[9] = {0.0, 25.0, 50.0, 75.0, 100.0, 125.0, 150.0, 175.0, 200.0};
  double y_values[9] = {9.34, 17.9, 41.5, 83.5, 51.5, 21.5, 10.8, 6.29, 4.09};

  // Make the spline object
  string type = "cubic";
  Spline my_cubic_spline (x_values, y_values, npts, type);

  // Evaluate the spline and derivatives
  // We comment this out to change to output files.
  /*
  double y = my_cubic_spline.y (x);
  double y_deriv = my_cubic_spline.yp (x);
  double y_deriv2 = my_cubic_spline.ypp (x);

  double x_sq = sqr(x);

  cout << "    x     y_exact   y_spline   y'_exact  y'_spline";
  cout << "  y''_exact  y''_spline" << endl;
  cout << fixed << setprecision(6) 
       << x << "  " << sin(x_sq) << "  " <<  y << "  "
       <<  2.*x*cos(x_sq) << "  " << y_deriv << "  "
       <<  -4.*x_sq* sin(x_sq) + 2.*cos(x_sq) << "  " <<  y_deriv2
       << endl;
  */

  Spline my_linear_spline(x_values, y_values, npts, "linear");
  Spline my_polynomial_spline(x_values, y_values, npts, "polynomial");

  ofstream fout("spline_data.dat");
  fout << "# E       Cubic      Linear      Polynomial      Exact\n";

  for (double x = 0.0; x < 201.0; x += 5.0) {
    double y = my_cubic_spline.y(x);
    double y_exact = Breit_Wigner(x);
    double y_linear = my_linear_spline.y(x);
    double y_poly = my_polynomial_spline.y(x);

    fout << x << " " << setprecision(8) << y << " " 
         << setprecision(8) << y_linear << " " << setprecision(8) 
         << y_poly << " " << setprecision(8) << y_exact << "\n";
  }

  fout.close();

  return (0);      // successful completion 
}

double Breit_Wigner(double E) {
  double sigma0 = 63900.0;
  double Er = 78.0;
  double gamma = 55.0;

  double denominator = (E-Er)*(E-Er) + (gamma*gamma)/4.0;

  return sigma0 / denominator;
}
