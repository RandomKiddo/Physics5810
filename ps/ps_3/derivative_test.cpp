//  file: derivative_test.cpp
// 
//  Program to study the error in differentiation rules
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//               Neil Ghugare    ghugare.1@osu.edu
//
//  Revision history:
//      01/14/04  original version, translated from derivative_test.c
//      01/14/07  modified to be consistent with derivative_test_simple.cpp
//      03/06/26  modified version to use more precise extrap_diff, extrap_diff2, and created adaptive_central_diff
//
//  Notes:
//   * Based on the discussion of differentiation in Chap. 8
//      of "Computational Physics" by Landau and Paez.
//   * Use the adaptive gsl_diff_central function as well.
//      Output from this with e^(-x) at x=1 is:
//  gsl_diff_central(1) = -3.6787944117560983e-01 +/- 6.208817e-04
//   actual relative error: 1.13284386e-11 
//
//*****************************************************************

/**
 * Comments on Problem 2:
 * We confirm the slopes in the regions for extrap_diff and extrap_diff2.
 * For small h, we see that the round-off error dominates for both methods,
 * with a slope of about -1, showing that rounding error grows as 1/h. 
 * For larger h, we see a slope of +4 for extrap_diff, confirming the O(h^4)
 * dependence on the truncation error, and for extrap_diff2, we get the next
 * order error (since we call extrap_diff in extrap_diff2) for O(h^6).
 */

/**
 * Comments on Problem 4 (Bonus):
 * We created the function adaptive_central_diff to find the optimal h. We
 * do this by iterating for some max number of iterations over values of h
 * until we reach the round-off error regime (error starts increasing again),
 * by comparing relative errors between each step of the central difference. 
 * If we don't find an optimal h in the iterations, we return the last h value
 * and output a message to the terminal that states as such. By looking at the
 * output derivative_test.dat for the central difference, we see that the round-off
 * to truncation error turnaround occurs at roughly log(h)=-5. Our adaptive code 
 * picks a value of log(h)=-4.91, which is exactly what we'd expect. We do not
 * use the exact value, since we don't know it.
 */

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
using namespace std;		// we need this when .h is omitted
#include <gsl/gsl_math.h>
#include <gsl/gsl_diff.h>

// function prototypes 
double test_function (double x, void *params_ptr);
double test_function_derivative (double x, void *params_ptr);

double forward_diff (double x, double h,
		     double (*f) (double x, void *params_ptr),
		     void *params_ptr);
double central_diff (double x, double h,
		     double (*f) (double x, void *params_ptr),
		     void *params_ptr);
double extrap_diff (double x, double h,
		    double (*f) (double x, void *params_ptr),
		    void *params_ptr);
double extrap_diff2(double x, double h,
		    double (*f) (double x, void *params_ptr),
		    void *params_ptr);
double adaptive_central_diff(double x, double (*f)(double x, void *params_ptr),
                             void *params_ptr, double &h_opt, int max_iter); // For the bonus 

typedef struct			// define a type to hold parameters 
{
  double alpha;
  double beta;
}
function_params;

//************************** main program ***************************
int
main (void)
{
  void *params_ptr;		// void pointer passed to functions 

  const double hmin = 1.e-10;	// minimum mesh size 
  double x = 2.;		// find the derivative at x 
  //double alpha = 1.;		// a parameter for the function 
  double diff_cd, diff_fd;	// central, forward difference 
  double diff_extrap;		// extrapolated derivative 
  double diff_extrap2; // extrapolated derivative 2
  double diff_gsl_cd;		// gsl adaptive central derivative 
  gsl_function My_F;		// gsl_function type 
  double abserr;                // absolute error

  ofstream out ("derivative_test.dat");	// open the output file 

  function_params my_coefficients;

  // set up values in the osu_parameters structure 
  my_coefficients.alpha = 2.0;
  my_coefficients.beta = 3.0/2.0;

  params_ptr = &my_coefficients;

  // exact answer for test 
  double answer = test_function_derivative (x, params_ptr);	

  My_F.function = &test_function;	// set up the gsl function 
  My_F.params = params_ptr;
  gsl_diff_central (&My_F, x, &diff_gsl_cd, &abserr);	// gsl calculation

  cout << "gsl_diff_central(" << x << ") = " << scientific
    << setprecision (16) << diff_gsl_cd << " +/- "
    << setprecision (6) << abserr << endl;
  cout << " actual relative error: " << setprecision (8)
    << fabs((diff_gsl_cd - answer)/answer) << endl;

  // add headers
  out << "# log10(h)  Relative Error (Forward)  Relative Error (Central)  Relative Error (Extrapolated)  Relative Error (Extrapolated 2)" << endl;
  
  double h = 0.5;		// initialize mesh spacing, increasing for problem 2
  while (h >= hmin)
  {
    diff_fd = forward_diff (x, h, &test_function, params_ptr);
    diff_cd = central_diff (x, h, &test_function, params_ptr);
    diff_extrap = extrap_diff (x, h, &test_function, params_ptr);
    diff_extrap2 = extrap_diff2(x, h, &test_function, params_ptr);

    // print relative errors to output file 
    out << scientific << setprecision (8)
      << log10 (h) << "   "
      << log10 (fabs ((diff_fd - answer) / answer)) << "   "
      << log10 (fabs ((diff_cd - answer) / answer)) << "   "
      << log10 (fabs ((diff_extrap - answer) / answer)) << "   "
      << log10 (fabs ((diff_extrap2 - answer) / answer)) << endl;

    h /= 2.;		// reduce mesh by 2 
  }

  out.close ();         // close the output stream

  double h_automagic;
  double diff_adaptive = adaptive_central_diff(x, &test_function, params_ptr, h_automagic, 100);

  cout << "Adaptive Central Diff = " << scientific << setprecision(16) << diff_adaptive << endl;
  cout << "Optimal h chosen automagically: " << h_automagic << " (log10(h) = " << log10(h_automagic) << ")" << endl;
  cout << "Adaptive relative error: " << fabs((diff_adaptive - answer)/answer) << endl;

  return (0);		// successful completion 
}

//************************** funct ***************************
double
test_function (double x, void *params_ptr)
{
  function_params *passed_ptr;
  passed_ptr = (function_params *) params_ptr;

  double alpha = passed_ptr->alpha;
  double beta = passed_ptr->beta;

  return alpha*pow(x, beta);
}

//************************** funct_deriv *********************
double
test_function_derivative (double x, void *params_ptr)
{
  function_params *passed_ptr;
  passed_ptr = (function_params *) params_ptr;

  double alpha = passed_ptr->alpha;
  double beta = passed_ptr->beta;

  return alpha*beta*pow(x, beta-1);
}

//************************** forward_diff *********************
double
forward_diff (double x, double h,
	      double (*f) (double x, void *params_ptr), void *params_ptr)
{
  return ( f(x + h, params_ptr) - f(x, params_ptr) ) / h;
}

//************************** central_diff *********************
double
central_diff (double x, double h,
	      double (*f) (double x, void *params_ptr), void *params_ptr)
{
  return ( f(x + h/2., params_ptr) - f(x - h/2., params_ptr) ) / h;
}

//************************** extrap_diff *********************
double
extrap_diff (double x, double h,
	     double (*f) (double x, void *params_ptr), void *params_ptr)
{
  /*
  return ( 8.*(f(x + h/4., params_ptr) - f(x - h/4., params_ptr))
	  - (f(x + h/2., params_ptr) - f(x - h/2., params_ptr)) ) 
	  / (3.*h);
  */

  // Updated extrap_diff to utilize central_diff
  return (4.0 * central_diff(x, h/2.0, f, params_ptr) - central_diff(x, h, f, params_ptr)) / 3.0;
}

//************************** extrap_diff2 *********************
// Combining extrap_diff to get an even better result
double
extrap_diff2 (double x, double h,
        double (*f) (double x, void *params_ptr), void *params_ptr)
{
  double D_h   = extrap_diff(x, h, f, params_ptr);
  double D_h2  = extrap_diff(x, h/2., f, params_ptr);
  
  return (16.0 * D_h2 - D_h) / 15.0;
}

//************************** adaptive_central_diff *********************
// Adapative central difference for Problem 4 (Bonus)
double adaptive_central_diff(double x, double (*f) (double x, void *params_ptr), void *params_ptr, double &h_opt, int max_iter) {
  double h = 0.1;  // starting h
  double current_diff = central_diff(x, h, f, params_ptr);
  double prev_error = 1e30;  // some large starting error so we actually iterate

  for (int i = 0; i < max_iter; ++i) {
    double next_h = h/2.0; // Get the next h value
    double next_diff = central_diff(x, next_h, f, params_ptr); // Calculate the next diff

    // Check the current error
    double current_error = fabs(next_diff - current_diff);

    // If the current error is larger than the previous, then we're hitting the round-off floor
    // Thus, we should return the current h and stop iterating
    if (current_error > prev_error) {
      h_opt = h;
      cout << "Found optimal h in " << i+1 << " iterations.\n";
      return current_diff;
    }

    // Otherwise, we update the h, diff, and error values, and keep iterating
    h = next_h;
    current_diff = next_diff;
    prev_error = current_error;
  }

  // If we reach max iterations, we need to return the last h
  h_opt = h;
  cout << "Reached maximum iterations, returning last h value.\n";
  return current_diff; 
}