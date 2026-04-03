//  file: RandomWalk_test.cpp
// 
//  Test program to for RandomWalk class
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      05/24/04  Original version
//      02/10/06  Updated and switched names of files
//
//******************************************************************

// include files
#include <iostream>		// cout and cin
#include <iomanip>		// manipulators like setprecision
#include <fstream>		// file input and output
using namespace std;		// we need this when .h is omitted

#include "RandomWalk.h"

//********************************************************************
int
main (void)
{
  int npts = 1;			// number of random numbers to generate 

  double x = 0.;		// current x 
  double y = 0.;		// current y 

  gsl_rng *my_rng = gsl_rng_alloc(gsl_rng_mt19937); 
  gsl_rng_set(my_rng, 12345);

  RandomWalk my_random_walk (my_rng, x, y);	// create a random walk starting
                                        //  at (x,y)

  cout << "How many random numbers? ";
  cin >> npts;

  // output file random_walk_test.dat holds a single walk of length npts 
  ofstream out;
  out.open ("RandomWalk_test.dat");

  out << "# (x,y) coordinates of a random walk with " << npts << " points"
    << endl;
  // output the first point 
  out << my_random_walk.get_x () << " " << my_random_walk.get_y () << endl;

  // do the walk and output to a file     
  for (int i = 0; i < npts; i++)
    {
      my_random_walk.step ();	// take a step
      x = my_random_walk.get_x ();
      y = my_random_walk.get_y ();
      out << x << " " << y << endl;
    }

  out.close ();			// close the output file
  cout << endl << "Output " << npts << " random walk coordinates to "
    << "RandomWalk_test.dat." << endl;


  gsl_rng_free(my_rng); // Cleanup happens once at the end

  return (0);
}
