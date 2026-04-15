//  file: VariationalMC.h
//
//  Header file for the VariationalMC C++ class.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/21/06  original version
//      03/07/09  fixed max_step bug (thanks to Kyle Wendt)
//
//*****************************************************************
#ifndef VARIATIONALMC_H
#define VARIATIONALMC_H

// include files
#include <iostream>
#include <gsl/gsl_rng.h>	// gsl random number generators
#include <gsl/gsl_randist.h>	// gsl random distributions

// structure
typedef struct
{
  double a;
  double b;
}
var_params;


class VariationalMC
{
 public:
  VariationalMC ( const double lower, const double upper, 
      double (*Psi_passed)(const double &x, const var_params &my_params),
      double (*E_local_passed)(const double &x, const var_params &my_params) );   
      // constructor
  ~VariationalMC ( );  //destructor

  // accessor functions --- these set and get private variables
  void set_limits (const double lower, const double upper)
                  {lower_limit = lower; upper_limit = upper;};
  void set_MC_steps (const int MCS) {MC_steps = MCS;};
  void set_max_step (const double step) {max_step = step;};
  void set_var_params (const var_params new_params) 
      {psi_params = new_params;  max_step = -1.; }  // reset max_step 
  double get_energy () {return energy;};
  double get_error ()  {return error;};
  double get_success_rate () {return success_rate;}
  
  int take_steps ();  // do the Monte Carlo steps

 private:
   gsl_rng *rng_ptr;  // pointer to GSL random number generator (rng)
   
   int MC_steps;      // number of Monte Carlo steps
   int initial_skip;  // thermalization skip
   int num_walkers;   // number of independent random walkers
   int num_steps;     // number of steps taken by each walker
   double max_step;   // -max_step < delta_x < max_step
   
   double lower_limit;   // lower bound of x
   double upper_limit;   // upper bound of x
   
   var_params psi_params;  // parameters for wave function psi
   
   double energy;          // average energy
   double energy_squared;  // average of energy squared
   double error;           // 
   double success_rate;    // calculated Metropolis success percentage
   
   inline double sqr (double x) {return (x*x);};
   
   int rng_init();         // initialize the random number generator
   double get_random();    // get a random number between 0 and 1
   
   // Supplied pointer to functions for wavefunction and local energy
   double (*Psi)(const double &x, const var_params &my_params);
   double (*E_local)(const double &x, const var_params &my_params);

   double rho_PDF (double x_now);  // wave function squared at current x
};   // don't forget the ; here!

#endif


