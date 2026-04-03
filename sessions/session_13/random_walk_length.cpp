//  file: random_walk_length.cpp
// 
//  Program to check sqrt(N) length of random walks
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      03/06/04  upgrade from random_walk.cpp to figure out how the
//                 average distance scales with the number of random steps
//      02/19/05  added more comments and math.h
//      02/14/06  minor upgrades and output comment
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
#include <iostream>		// cout and cin
#include <iomanip>		// manipulators like setprecision
#include <fstream>		// file input and output
#include <cmath>
using namespace std;		// we need this when .h is omitted

#include <gsl/gsl_rng.h>	// GSL random number generators
#include <gsl/gsl_randist.h>	// GSL random distributions

// function prototypes
extern unsigned long int random_seed ();    // routine to generate a seed

//********************************************************************
int
main (void)
{
  int npts = 100;		// size of random walk 
  int trials;			// number of trials of npts walks 
  unsigned long int seed;       // seed for random number generator

  double lower = -sqrt (2.);	// lower limit of uniform range 
  double upper = sqrt (2.);	// upper limit of uniform range 

  double delta_x;		// uniform random number from [lower,upper]
  double delta_y;		// 2nd random number from [lower,upper] 
  double x = 0.;		// current x 
  double y = 0.;		// current y 

  double R_avg;			// average distance from origin (at end of walk)

  gsl_rng *rng_ptr;		// declare pointer to random number 
                                //   generator (rng) 

  rng_ptr = gsl_rng_alloc (gsl_rng_taus);	// allocate the rng 
  cout << "Enter a long integer as a seed or 0 to generate one: ";
  cin >> seed;
  if (seed == 0)
    {				// generate a seed from /dev/random
      seed = random_seed ();
    }

  cout << " Using " << seed << " to seed the RNG" << endl;
  gsl_rng_set (rng_ptr, seed);	// seed the rng 

  // output file random_walk_length.dat has data on the average R 
  ofstream out;
  out.open ("random_walk_length.dat");

  // go through walks of different lengths
  for (npts = 10; npts <= 100000; npts *= 2)
    {
      trials =  int( sqrt (double(npts)) );  // Sqrt[npts] trials recommended
      R_avg = 0.;		             // reset the average length
      for (int i = 0; i < trials; i++)	     // make "trials" runs and average
	{
	  x = y = 0;		// reset to origin 
	  for (int j = 0; j < npts; j++)
	    {
	      delta_x = gsl_ran_flat (rng_ptr, lower, upper);
	      delta_y = gsl_ran_flat (rng_ptr, lower, upper);
	      x += delta_x;
	      y += delta_y;
	    }
	  R_avg += sqrt (x * x + y * y);	// accumulate final distances
	}
      R_avg /= (double) trials;	        // get the average
      
      out << npts << " " << R_avg << endl;
    }
  cout << "Output random walk length to random_walk_length.dat." << endl; 

  gsl_rng_free (rng_ptr);	// free the random number generator 
  out.close ();			// close the output file

  return 0;
}
