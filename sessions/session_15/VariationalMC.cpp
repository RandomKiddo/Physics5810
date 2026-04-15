//  file: VariationalMC.cpp
//
//  Definitions for the VariationalMC C++ class.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/22/06  original version, based on Variational_SHO_metro.cpp
//      03/03/09  fixed step size and initial skip bugs
//      03/07/09  fixed max_step bug (thanks to Kyle Wendt)
//
//  Notes:
//    * Many upgrades are needed.  max_step needs to be more general.
//    
//*****************************************************************
// include files
#include <cmath>
#include <iostream>

#include "VariationalMC.h"      // header file for VariationalMC class

extern unsigned long int random_seed ();   // routine to generate a seed

//********************************************************************

// Constructor for VariationalMC 
VariationalMC::VariationalMC ( const double lower, const double upper, 
      double (*Psi_passed)(const double &x, const var_params &my_params),
      double (*E_local_passed)(const double &x, const var_params &my_params)  )
{
  lower_limit = lower;
  upper_limit = upper;
  Psi = Psi_passed;
  E_local = E_local_passed;
  
  // Set defaults 
  initial_skip = 2000;
  num_walkers = 50; 
  max_step = -1.;
  
  // initialize random number generator
  rng_init(); 
}
//********************************************************************

// Copy constructor (use default copy constructor for now)
//********************************************************************

// Destructor for VariationalMC
VariationalMC::~VariationalMC ()
{
   // put an appropriate destructor here
}
//********************************************************************

// Initialize the random number generator (rng)
int
VariationalMC::rng_init ( )
{
  //  Use the GSL random number generators (rng's)
  rng_ptr = gsl_rng_alloc (gsl_rng_taus);	// allocate an rng 
  gsl_rng_set (rng_ptr, random_seed ());	// seed the rng 
  
  return (0);
}
//********************************************************************

// Return a random number between 0 and 1
double
VariationalMC::get_random ( )
{
  return ( gsl_ran_flat(rng_ptr, 0., 1.) );
}
//********************************************************************

// Return the Probability Density Function rho evaluated at x_now
double
VariationalMC::rho_PDF (double x_now)
{
  return ( sqr( Psi(x_now,psi_params) ) );
}
//********************************************************************

// Take the Monte Carlo steps and calculate energy and error
int
VariationalMC::take_steps ()
{
  if (max_step < 0.) { max_step = 4./sqrt(psi_params.a); }  // default step size

  // find out how many steps each walker takes and allocate an array
  num_steps = int( double(MC_steps)/double(num_walkers) );
  double *x_walker = new double [num_walkers];
  
  // set initial point for each walker (within max_step of origin)
  for (int j = 0; j < num_walkers; j++)
  {
    x_walker[j] = max_step * (get_random() - 1./2.);
  }
  
  // do Metropolis walk
  int successes = 0;
  double energy_sum = 0;
  double energy_sq_sum = 0;
  for (int i = 0; i < num_steps + initial_skip; i++)  // allow for initial_skip
  {
    for (int j = 0; j < num_walkers; j++)
    {
      // take a trial step
      double x_trial = max_step * (get_random() - 1./2.);
      double ratio = rho_PDF(x_trial) / rho_PDF(x_walker[j]);
      double random = get_random();
      if (ratio >= random)
      {   // accept the step
        x_walker[j] = x_trial;
        if (i >= initial_skip) {successes++;}
      }
      
      // compute energy
      if (i >= initial_skip)
      {
        double E_L = E_local (x_walker[j], psi_params);
        energy_sum += E_L;
        energy_sq_sum += sqr(E_L);
      }        
    }       
  }
  
  double total_points = double(num_walkers * num_steps);
  energy = energy_sum / total_points;
  energy_squared = energy_sq_sum / total_points;
  error = sqrt( (energy_squared - sqr(energy)) / total_points );
  success_rate = double(successes) / total_points;

  delete [] x_walker;

  return (0);
}
//********************************************************************
