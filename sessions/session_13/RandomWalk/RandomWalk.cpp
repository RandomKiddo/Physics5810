//  file: RandomWalk.cpp
// 
//  Member functions for RandomWalk class that generates random walks
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      05/24/04  switched random_walk.cpp to define a RandomWalk class
//
//  Notes:
//   * implements method 2 from the list in section 6.10
//      of the Landau/Paez text.
//   * random numbers are generated uniformly from a to b
//   * uses the GSL random number functions
//   * both the gsl_rng.h and gsl_randist.h header files are needed
//   * the current version uses the gsl_rng_taus random number
//      generator.  There are many other choices (just change
//      the name in the gsl_rng_alloc statement).  See the GSL
//      manual for a list of generators and their properties.
//
//******************************************************************

// include files
#include <cmath>

#include "RandomWalk.h"

// function prototypes
extern unsigned long int random_seed ();	// routine to generate a seed

//********************************************************************

// Constructor for RandomWalk
RandomWalk::RandomWalk (gsl_rng *r, double x0, double y0)
{
  rng_ptr = r;

  npts = 1;			// start with one point

  // initialize step size
  lower_limit = -sqrt (2.);	// lower limit of uniform range 
  upper_limit = sqrt (2.);	// upper limit of uniform range 

  x = x0;			// current x 
  y = y0;			// current y 
  delta_x = 0.;			// uniform random number from a to b 
  delta_y = 0.;			// 2nd uniform random number from a to b 
}

// Destructor for RandomWalk
RandomWalk::~RandomWalk ()
{
  //gsl_rng_free (rng_ptr);	// free the random number generator
}

// Take a single random step with lower_limit < delta_x, delta_y < upper_limit
void
RandomWalk::step ()
{
  delta_x = gsl_ran_flat (rng_ptr, lower_limit, upper_limit);
  delta_y = gsl_ran_flat (rng_ptr, lower_limit, upper_limit);

  // increment the current coordinates
  x += delta_x;
  y += delta_y;

  npts++;			// increment the point counter
}

RandomWalk::RandomWalk (double x0, double y0, double low, double high) {
  x = x0;
  y = y0;
  lower_limit = low;
  upper_limit = high;
  npts = 1;

  rng_ptr = gsl_rng_alloc (gsl_rng_taus);
  unsigned long int seed = random_seed ();
  gsl_rng_set (rng_ptr, seed);
}
