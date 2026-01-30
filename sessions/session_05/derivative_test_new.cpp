//  file: derivative_test_new.cpp
// 
//  Program to study the error in differentiation rules
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      01/15/07 --- modified from derivative test to change function
//      01/23/09 --- fixed typos 
//
//*****************************************************************
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
struct parameters
{
  double alpha;
  double beta;
};
//************************** main program ***************************
int
main (void)
{
  void *params_ptr;		// void pointer passed to functions 

  const double hmin = 1.e-10;	// minimum mesh size 
  double x = 2.;		// find the derivative at x 
  double alpha = 2.;		// a parameter for the function
  double beta = 3./2.; 
  double answer, diff_cd, diff_fd;	// answer, central, forward difference 
  double diff_extrap;		// extrapolated derivative 
  double diff_gsl_cd;		// gsl adaptive central derivative 
  gsl_function My_F;		// gsl_function type 
  double abserr;
  struct parameters my_parameters;  // structure with parameters
  
  // load the structure
  my_parameters.alpha = alpha;
  my_parameters.beta = beta;

  ofstream out ("derivative_test.dat");	// open the output file 

  params_ptr = &my_parameters;		// structure to pass to function 

  answer = test_function_derivative (x, params_ptr);	// exact answer 

  My_F.function = &test_function;	// set up the gsl function 
  My_F.params = params_ptr;
  gsl_diff_central (&My_F, x, &diff_gsl_cd, &abserr);	// gsl calculation

  cout << "gsl_diff_central(" << x << ") = " << scientific
    << setprecision (16) << diff_gsl_cd << " +/- "
    << setprecision (6) << abserr << endl;
  cout << " actual relative error: " << setprecision (8)
    << fabs ((diff_gsl_cd - answer) / answer) << endl;

  double h = 0.1;		// initialize mesh spacing 
  while (h >= hmin)
    {
      diff_fd = forward_diff (x, h, &test_function, params_ptr);
      diff_cd = central_diff (x, h, &test_function, params_ptr);
      diff_extrap = extrap_diff (x, h, &test_function, params_ptr);

      // print relative errors to output file 
      out << scientific << setprecision (8)
	<< log10 (h) << "   "
	<< log10 (fabs ((diff_fd - answer) / answer)) << "   "
	<< log10 (fabs ((diff_cd - answer) / answer)) << "   "
	<< log10 (fabs ((diff_extrap - answer) / answer)) << endl;

      h /= 2.;			// reduce mesh by 2 
    }
  out.close ();  
  return (0);			// successful completion 
}
//************************** funct ***************************
double
test_function (double x, void *params_ptr)
{
  struct parameters *passed_ptr;
  passed_ptr = (struct parameters *) params_ptr;  
  double alpha = passed_ptr->alpha;
  double beta = passed_ptr->beta;

  return (alpha*pow(x,beta));
}
//************************** funct_deriv *********************
double
test_function_derivative (double x, void *params_ptr)
{
  struct parameters *passed_ptr;
  passed_ptr = (struct parameters *) params_ptr;  
  double alpha = passed_ptr->alpha;
  double beta = passed_ptr->beta;

  return (beta*alpha*pow(x,beta-1.));
}
//************************** forward_diff *********************
double
forward_diff (double x, double h,
	      double (*f) (double x, void *params_ptr), void *params_ptr)
{
  return (f (x + h, params_ptr) - f (x, params_ptr)) / h;
}
//************************** central_diff *********************
double
central_diff (double x, double h,
	      double (*f) (double x, void *params_ptr), void *params_ptr)
{
  return (f (x + h / 2., params_ptr) - f (x - h / 2., params_ptr)) / h;
}
//************************** extrap_diff *********************
double
extrap_diff (double x, double h,
	     double (*f) (double x, void *params_ptr), void *params_ptr)
{
  return (8. * (f (x + h / 4., params_ptr) - f (x - h / 4., params_ptr))
	  - (f (x + h / 2., params_ptr) -
	     f (x - h / 2., params_ptr))) / (3. * h);
}
