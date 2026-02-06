//  file: diffeq_test.cpp
// 
//  Program to study the error in differential equation algorithms
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/07/04  original version, translated from diffeq_test.c
//      01/30/05  comments improved and function names changed
//      01/22/06  improved code organization
//
//  Notes:
//   * Based on the discussion of differential equations in Chap. 9
//      of "Computational Physics" by Landau and Paez
//   * As a convention (advocated in "Practical C++"), we'll append
//      "_ptr" to all pointers.
//
//********************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
using namespace std;		// we need this when .h is omitted
#include <cmath>
#include "diffeq_routines.h"	// diffeq routine prototypes

// function prototypes
double rhs (double t, double y[], int i, void *params_ptr);
double exact_answer (double t, void *params_ptr);

// structures
typedef struct			// define a type to hold parameters 
{
  double alpha;
  double beta;
}
f_parameters;			// now we can define a structure of this type
				//   using the keyword "f_parameters" 


//************************** main program ****************************
int
main (void)
{
  void *params_ptr;		   // void pointer passed to functions 
  f_parameters funct_parameters;   // parameters for the function 

  const int N = 2;		// size of arrays of y functions
  double y_euler[N], y_rk4[N];	// arrays of y functions 

  ofstream out ("diffeq_test6.dat");	// open the output file 

  funct_parameters.alpha = 1.;	// function parameter to be passed 
  funct_parameters.beta = 1.;	// function parameter to be passed
  params_ptr = &funct_parameters;	// structure to pass to function 

  double tmin = 0.;		// starting t value 
  double tmax = 10.;		// last t value 
  y_euler[0] = 1.0;		// initial condition for y(t) 
  y_rk4[0] = 1.0;		// initial condition for y(t) 
  y_euler[1] = 0.0;		// initial condition for y(t) 
  y_rk4[1] = 0.0;

  double y_euler_2[N], y_rk4_2[N];  // arrays for smaller h, (1/10)*h to be precise
  y_euler_2[0] = 1.0;
  y_rk4_2[0] = 1.0;
  y_euler_2[1] = 0.0;		// initial condition for y(t) 
  y_rk4_2[1] = 0.0;

  // print out a header line and the first set of points 
  out << "#      t           y_rk4_0         y_rk4_1       y_exact(t) \n";
  out << scientific << setprecision (9)
    << tmin << "  "
    << y_rk4[0] << "  "
    << y_rk4[1] << "  " << exact_answer (tmin, params_ptr) << endl;

  double h = 0.1;		// initialize mesh spacing 

  for (double t = tmin; t <= tmax; t += h)
  {

    // find y(t+h) and output vs. t+h 
    euler (N, t, y_euler, h, rhs, params_ptr);	// Euler's algorithm 

    runge4 (N, t, y_rk4, h, rhs, params_ptr);	        // 4th order R-K 

    out << scientific << setprecision (9)
      << t + h << "  "
      << y_rk4[0] << "  "
      << y_rk4[1] << "  " << exact_answer (t + h, params_ptr) << endl;
  }

  cout << "data stored in diffeq_test6.dat\n";
  out.close ();			// close the output file 

  ofstream out2 ("diffeq_test7.dat");
  out2 << "#      t           y_rk4_0         y_rk4_1       y_exact(t) \n";
  out2 << scientific << setprecision (9)
    << tmin << "  "
    << y_rk4_2[0] << "  "
    << y_rk4_2[1] << "  " << exact_answer (tmin, params_ptr) << endl;
  
  h /= 10.0;

  for (double t = tmin; t <= tmax; t += h)
  {

    // find y(t+h) and output vs. t+h 
    euler (N, t, y_euler_2, h, rhs, params_ptr);	// Euler's algorithm 

    runge4 (N, t, y_rk4_2, h, rhs, params_ptr);	        // 4th order R-K 

    out2 << scientific << setprecision (9)
      << t + h << "  "
      << y_rk4_2[0] << "  "
      << y_rk4_2[1] << "  " << exact_answer (t + h, params_ptr) << endl;
  }

  cout << "data stored in diffeq_test7.dat\n";
  out2.close ();			// close the output file 

  return (0);			// successful completion 
}

// for number 6
/*
int main (void)
{
  void *params_ptr;
  f_parameters funct_parameters;

  const int N = 1;
  double y_euler[N], y_rk4[N];

  ofstream out ("diffeq_h_scaling3.dat");
  
  funct_parameters.alpha = 1.;
  funct_parameters.beta = 1.;
  params_ptr = &funct_parameters;

  double t_target = 0.25; // Fixed time to check error
  double y_exact = exact_answer(t_target, params_ptr);

  out << "# h             euler_rel_err      rk4_rel_err" << endl;
  out << scientific << setprecision(16); // Increased precision for small h

  //double pi = 3.14159265358979323;

  // Loop over step sizes h from 10^-1 down to 10^-7
  for (double h = 0.1; h >= 1.e-7; h /= 10.0)
  {
    // Reset initial conditions for each new h
    y_euler[0] = 0.0;
    y_rk4[0] = 0.0;
    
    // Integrate from t=0 to t_target using current h
    for (double t = 0; t < t_target - (h/2.0); t += h)
    {
      euler(N, t, y_euler, h, rhs, params_ptr);
      runge2(N, t, y_rk4, h, rhs, params_ptr);
    }

    // Calculate relative errors
    double err_euler = abs((y_euler[0] - y_exact) / (y_exact+1.0e-10));
    double err_rk4 = abs((y_rk4[0] - y_exact) / (y_exact+1.0e-10));

    out << h << "  " << err_euler << "  " << err_rk4 << endl;
  }

  out.close();
  cout << "Scaling data stored in diffeq_h_scaling3.dat" << endl;
  return 0;
}
  */

//************************** rhs ************************************
//
//  * This is the function defining the right hand side of the diffeq
//
//*********************************************************************
double
rhs (double t, double y[], int i, void *params_ptr)
{
  //double a = ((f_parameters *) params_ptr)->alpha;
  // double b = ((f_parameters *) params_ptr)->beta; 

  if (i == 0)
  {
    // return (-a * t * y[0]);
    return y[1];
  }
  if (i == 1) {
    return -y[0];
  }

  return (0);			// something's wrong if we get here 
}

//********************** exact_answer **************************
//
//  * This is the exact answer for y(t)
//
//******************************************************************
double
exact_answer (double t, void *params_ptr)
{
  // recover a and b from the void pointer params_ptr
  //double a = ((f_parameters *) params_ptr)->alpha;
  //double b = ((f_parameters *) params_ptr)->beta;

  //double pi = 3.14159265358979323;

  return cos(t);
}
