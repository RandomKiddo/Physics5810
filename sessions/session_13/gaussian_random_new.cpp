//  file: gaussian_random_new.cpp
// 
//  Program to illustrate how to generate uniformly distributed
//   and gaussian distributed random numbers using GSL routines
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      20-Feb-2004  original version (gaussian_random.cpp)
//      05-Mar-2004  added seeding of random number generators 
//                    (see random_seed.cpp)
//      06-Mar-2004  added histrogramming and commented out output
//      19-Feb-2005  minor changes to variable names and comments
//      13-Feb-2006  tidied up the code, moved declarations
//
//  Notes:
//   * uses the GSL random number functions
//   * both the gsl_rng.h and gsl_randist.h header files are needed
//   * the current version uses the gsl_rng_taus random number
//      generator.  There are many other choices (just change
//      the name in the gsl_rng_alloc statement).  See the GSL
//      manual for a list of generators and their properties.
//   * The Gaussian random variate has mean zero and standard deviation
//      sigma.  Its probability distribution is
//        p(x)dx = 1/Sqrt[2 Pi sigma^2] Exp[-x^2/(2 sigma^2)]
//
//******************************************************************

// include files
#include <iostream>		// cout and cin
#include <iomanip>		// manipulators like setprecision
#include <fstream>		// file input and output
using namespace std;		// we need this when .h is omitted

#include <gsl/gsl_rng.h>	// GSL random number generators
#include <gsl/gsl_randist.h>	// GSL random distributions

// function prototypes
extern unsigned long int random_seed ();	// routine to generate a seed
int histogram_bin (const double value, const int num_bins, 
  const double bin_min, const double bin_max);  // routine to find bins
void histogram_x (double x_bins[], const int num_bins, 
  const double bin_min, const double bin_max);  // find x values of bins

//********************************************************************
int
main ()
{
  gsl_rng *rng_ptr;		// pointer to random number generator (rng) 
  rng_ptr = gsl_rng_alloc (gsl_rng_taus);	// allocate the rng 

  unsigned long int seed;	// "seed" for the random number generators
  cout << "Enter a long integer as a seed or 0 to generate one: ";
  cin >> seed;
  if (seed == 0)
    {				// generate a seed from /dev/random
      seed = random_seed ();
    }

  cout << " Using " << seed << " to seed the RNG" << endl;
  gsl_rng_set (rng_ptr, seed);	// seed the rng 

  // output file for numbers [commented out]
  // ofstream out;
  // out.open ("random_numbers.dat");

  // generate uniform and gaussian distributed random numbers

  int npts = 100;		// number of random numbers to generate 
  cout << "How many random numbers? ";
  cin >> npts;

  double lower = 0.;		// lower limit for uniform region
  double upper = 1.;		// upper limit for uniform region
  double sigma = 1.;		// standard deviation of gaussian distribution 

  // set up histogram bins
  const int num_bins = 50;
  int my_bin = 0;
  int uniform1_bins[num_bins] = {0};
  int uniform2_bins[num_bins] = {0};
  double uniform_x[num_bins] = {0.};
  histogram_x(uniform_x,num_bins,lower,upper);
  
  int gaussian1_bins[num_bins] = {0};
  int gaussian2_bins[num_bins] = {0};
  double gaussian_min = -3.*sigma;
  double gaussian_max = 3.*sigma;
  double gaussian_x[num_bins] = {0.};
  histogram_x(gaussian_x,num_bins,gaussian_min,gaussian_max);

  // out << "# uniform1 uniform2 gaussian1 gaussian2" << endl;
  for (int i = 0; i < npts; i++)
    {
      // uniform random numbers from [lower,upper]
      double uniform1 = gsl_ran_flat (rng_ptr, lower, upper);
      my_bin = histogram_bin(uniform1,num_bins,lower,upper);
      uniform1_bins[my_bin]++;
      
      double uniform2 = gsl_ran_flat (rng_ptr, lower, upper);
      my_bin = histogram_bin(uniform2,num_bins,lower,upper);
      uniform2_bins[my_bin]++;

      // random numbers distributed as gaussians
      double gaussian1 = gsl_ran_gaussian (rng_ptr, sigma);
      my_bin = histogram_bin(gaussian1,num_bins,gaussian_min,gaussian_max);
      gaussian1_bins[my_bin]++;

      double gaussian2 = gsl_ran_gaussian (rng_ptr, sigma);
      my_bin = histogram_bin(gaussian2,num_bins,gaussian_min,gaussian_max);
      gaussian2_bins[my_bin]++;

      //  out << "  " << fixed << uniform1 << " " << uniform2 << " "
      //	<< gaussian1 << " " << gaussian2 << endl;
    }

  gsl_rng_free (rng_ptr);	// free the random number generator 
  // out.close ();			// close the output file
   
  ofstream hist;
  hist.open ("random_histogram.dat");

  hist << "# bin x_uniform uniform1 uniform2 x_gaussian gaussian1 gaussian2 "
       << endl;
  for (int i = 0; i < num_bins; i++)
  {
    hist << "  " << setw(3) << i+1 << "    " 
         << setw(5) << uniform_x[i] << " "
         << setw(7) << uniform1_bins[i] << " "
         << setw(7) << uniform2_bins[i] << "     "
         << setw(5) << gaussian_x[i] << "   "
         << setw(7) << gaussian1_bins[i] << " "
         << setw(7) << gaussian2_bins[i] << endl;  
  }

  cout << "Histogrammed " << npts 
       << " random numbers in random_histogram.dat." << endl; 
       
  hist.close ();                // close the histogram file

  return 0;
}


//*********************************************************************
//
//  histogram_bin returns an integer from 0 to num_bins-1, which is the
//   bin number that value falls into.
//  histogram_x returns an array of the values of the bins
//
//   value --- number whose bin we're identifying
//   num_bins --- total number of bins
//   bin_min --- least value
//   bin_max --- greatest value
//
//  Revision history:
//   06-Mar-2004  original version 
//
//**********************************************************************   
int
histogram_bin (const double value, const int num_bins, 
  const double bin_min, const double bin_max)
{
  int bin_number = 0;
    
  if (value < bin_min) {
    bin_number = 0;
  } else if (value > bin_max) {
    bin_number = num_bins-1;
  }
  
  // bin_number is fraction of interval * number of bins
  bin_number = int(double(num_bins)*(value - bin_min)/(bin_max - bin_min));
    
  return bin_number;
}

void
histogram_x (double x_bins[], const int num_bins, 
  const double bin_min, const double bin_max)
{
  double delta_x = (bin_max-bin_min)/(double(num_bins));
  
  for (int i=0; i < num_bins; i++)
  {
    x_bins[i] = bin_min + (double(i)+0.5)*delta_x;
  } 
}
