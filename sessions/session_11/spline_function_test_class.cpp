//  file: spline_function_test_class.cpp:  
//
//  Test program for interpolated function using splines  
//                                                                    
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/10/09 -- created from spline_function2_test.cpp and the
//                   Spline class in GslSpline.h,cpp
//
//  Notes:
//   * uses the GSL interpolation functions (see online documentation) 
//
//*******************************************************************

// include files
#include <iostream>		// cout and cin
#include <iomanip>		// manipulators like setprecision
#include <cmath>
using namespace std;		// we need this when .h is omitted

#include "GslSpline.h"  // Header file for the GSL Spline class

//*********************** main ******************************
int
main (void)
{
  const int NMAX = 300;  // maximum size of (x,y) arrays
  double x_array[NMAX], y_array[NMAX], z_array[NMAX];

  // set up the arrays of "data" to be splined 
  int npts = 200;
  for (int i = 0; i < npts; i++)
    {
      double x_temp = double(i) / 10.;
      x_array[i] = x_temp;
      y_array[i] = x_temp * x_temp;
      z_array[i] = sin (x_temp * x_temp);
    }
  
  Spline my_spline (x_array, y_array, npts, "cubic");
  Spline my_other_spline (x_array, z_array, npts, "cubic");

  double x;
  cout << "Enter x: ";
  cin >> x;		// test point 

  // evaluate the first function and derivatives (repeatable) 
  double y = my_spline.y (x);
  double y_deriv = my_spline.yp (x);
  double y_deriv2 = my_spline.ypp (x);

  // evaluate the second function and derivatives (repeatable) 
  double z = my_other_spline.y (x);
  double z_deriv = my_other_spline.yp (x);
  double z_deriv2 = my_other_spline.ypp (x);

  cout << "x = " << x << ", y = " << y << ", y' = " 
    << y_deriv << ", y'' = " << y_deriv2 << endl;
  cout << "x = " << x << ", z = " << z << ", z' = " 
    << z_deriv << ", z'' = " << z_deriv2 << endl;

  return (0);
}

