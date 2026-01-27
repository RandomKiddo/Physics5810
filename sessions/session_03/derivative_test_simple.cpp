//  file: derivative_test_simple.cpp
// 
//  Program to study the error in differentiation rules using
//   the simplest algorithms.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//               Ralf Bundschuh (bundschuh.2@osu.edu)
//
//  Revision history:
//      01/08/07  original version, extracted from derivative_test.cpp
//      11-Jan-2018  replaced float by macro
//
//  Notes:
//   * Based on the discussion of differentiation in Chap. 8
//      of "Computational Physics" by Landau and Paez.
//
//*****************************************************************

// include files
#include <iostream>		// basic input/output functions
#include <iomanip>		// manipulators like setprecision
#include <fstream>		// to read and write data as file streams 
#include <cmath>
using namespace std;	// so that std::cout --> cout, etc.

// function prototypes 
FLOAT test_function (FLOAT x);
FLOAT test_function_derivative (FLOAT x);

FLOAT forward_diff (FLOAT x, FLOAT h, FLOAT (*f) (FLOAT x));
FLOAT central_diff (FLOAT x, FLOAT h, FLOAT (*f) (FLOAT x));

//************************** main program ***************************
int
main ()
{
  const FLOAT h_min = 1.e-10;	// minimum mesh size 
  FLOAT x = 1.;		// find the derivative at x 
  FLOAT diff_cd, diff_fd;	// central, forward difference 

  ofstream deriv_out ("derivative_test_simple.dat"); // open the output file

  FLOAT exact = test_function_derivative(x);	// exact answer for test 
  
  // print a header to the file
  deriv_out << "# log10(h) log10(forward error) log10(central error)" << endl;

  FLOAT h = 0.1;		// initialize mesh spacing 
  while (h >= h_min)
  {
    diff_fd = forward_diff (x, h, &test_function);
    diff_cd = central_diff (x, h, &test_function);

    // print relative errors to output file 
    deriv_out << scientific << setprecision (8)
      << log10(h) << "   "
      << log10( fabs((diff_fd - exact)/exact) ) << "   "
      << log10( fabs((diff_cd - exact)/exact) ) << "   "
      << endl;

    h /= 2.;		// reduce mesh (x spacing) by 2 before repeating 
  }

  deriv_out.close ();         // close the output stream
  return (0);		// successful completion 
}

//************************** test_function ***************************
FLOAT
test_function (FLOAT x)
{
  FLOAT alpha = 1.;  	// a parameter for the function 
  return (exp (-alpha * x));
}

//********************** test_function_derivative ********************
FLOAT
test_function_derivative (FLOAT x)
{
  FLOAT alpha = 1.;   	// Note that we had to repeat this, which is bad!
  return (-alpha * exp (-alpha * x));
}

//************************* forward_diff ****************************
FLOAT
forward_diff (FLOAT x, FLOAT h, FLOAT (*f) (FLOAT x))
{
  return ( f(x + h) - f(x) ) / h;
}

//************************* central_diff *******************************
FLOAT
central_diff (FLOAT x, FLOAT h, FLOAT (*f) (FLOAT x))
{
  return ( f(x + h/2.) - f(x - h/2.) ) / h;
}

//***********************************************************************

