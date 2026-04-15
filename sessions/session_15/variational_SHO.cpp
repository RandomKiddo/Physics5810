//  file: variational_SHO.cpp
// 
//  Program to demonstrate variational Monte Carlo applied
//   to a one-dimensional simple harmonic oscillator (SHO).
//   The ground-state energy (exact = 1/2) is calculated as a function of
//   a variational parameter a, using the Metropolis algorithm
//   to evaluate the expectation value of the Hamiltonian.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/21/06  original version, based on Variational_SHO_metro.cpp
//      03/03/09  fixed Psi and E_local 
//      03/07/09  added setting of max_step (thanks to Kyle Wendt)
//
//  Notes:
//   * To use the VariationalMC class, you must create the "Psi"
//      and "E_local" functions.  The wavefunction Psi is assumed
//      to be normalized.  (Why does this matter?  How could this
//      restriction be lifted?)
//   * The probability distribution function (PDF) for the Metropolis
//      algorithm is fixed to be |Psi(x)|^2.
//   * Arguments are declared as const "references" using a & in front.
//      These are like aliases for the variables.
//
//******************************************************************
// include files
#include <iostream>                
#include <iomanip>                
#include <fstream>
#include <cmath>
using namespace std;               

#include "VariationalMC.h"        // Variational Monte Carlo class

// function prototypes
double Psi (const double &x, const var_params &my_params); // Trial wavefunction
double E_local (const double &x, const var_params &my_params); // Local energy
inline double sqr (double x) { return x*x; };        // square a double

// main program
int
main ()
{
  var_params my_params = {0., 0.};  // declare variational parameter structure
  
  // request range of parameters and # of MC steps from user
  double a_min, a_max, a_step;
  cout << "Input a_min, a_max, a_step: " << endl;
  cin >> a_min >> a_max >> a_step;
  if (a_min <= 0.) { a_min = a_step; }   // force a_min >= a_step
  int MC_steps;
  cout << "Number of Monte Carlo steps: ";
  cin >> MC_steps;

  // declare a VariationalMC object and set some properties  
  double lower_limit = -10.;
  double upper_limit = +10.;
  VariationalMC my_VariationalMC (lower_limit, upper_limit, &Psi, &E_local);
  my_VariationalMC.set_MC_steps (MC_steps);
  
  ofstream VMC_out; 
  VMC_out.open ("variational_SHO_2.dat");
  VMC_out << "#  a       energy       error   "  << endl;
  for (double a_loop = a_min; a_loop <= a_max; a_loop += a_step)
  {
    my_params.a = a_loop;   // set the current parameter a
    my_VariationalMC.set_var_params (my_params);  // pass parameters to object
    // set step size based on size of a_loop; goal is 50% success rate
    my_VariationalMC.set_max_step ( 6./sqrt(a_loop) );  

    my_VariationalMC.take_steps ();   // do the Monte Carlo steps
    
    VMC_out << fixed << setprecision(7)
            << a_loop << " " << my_VariationalMC.get_energy() << " "
            << my_VariationalMC.get_error() << endl;
    cout << "Success rate for a = " << a_loop 
         << " is " << my_VariationalMC.get_success_rate() << endl;
  }
  VMC_out.close();
  
  cout << "Output to variational_SHO_2.dat" << endl;

  return (0);
}

/*
// Evaluation of wavefunction at a point x
double
Psi (const double &x, const var_params &my_params)
{
  double a = my_params.a;
  return ( sqrt(a/2.) / cosh(a*x) );        
}

// Local energy function at point x: E_local = (H*Psi)/Psi 
double
E_local (const double &x, const var_params &my_params)
{
  double a = my_params.a;
  return ( sqr(a)*(1./sqr(cosh(a*x)) - sqr(tanh(a*x)))/2. + sqr(x)/2. );
}
*/

//*********************************************************************
// Evaluation of wavefunction at a point x
double
Psi (const double &x, const var_params &my_params)
{
  double a = my_params.a;
  return (1.0/(1.0+a*sqr(x)));     
}
//*********************************************************************

//**********************************************************************
// Local energy function at point x: E_local = (H*Psi)/Psi 
double
E_local (const double &x, const var_params &my_params)
{
  double a = my_params.a;
  double denom = 1.0 + a*sqr(x);
  double k = a*(1.0 - 3.0*a*sqr(x)/denom) / denom;
  return (k + 0.5*sqr(x));
}
//*********************************************************************

