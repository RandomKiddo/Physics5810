//  file: bessel.cpp 
//
//  Spherical Bessel functions via up and down recursion      
//                                                                     
//
//  Programmer:  Neil Ghugare  ghugare.1@osu.edu
//
//  Revision history:
//      02-Jan-2011  new version, for 780.20 Computational Physics
//      16-Jan-2026  retrieved latest version
//      23-Jan-2026  modified for ps1
//
//  Notes:  
//   * compile with:  "g++ -o bessel.x bessel.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez  
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau  
//   * data saved as: x y1 y2 y3 y4           
//      
//************************************************************************

/*
Answer to 3(b) from PS1

Using log scale on the plot allowued us to see the results.
From this, we can see that the relative error is the worst (most disagreement
between the up and down recursion methods) for small x (x<1) and larger x (x>30).
This means there are 3 regions of the graph. The first region of x<1 is a high
error regime, likely due to the initial conditions of the recursive method,
as the function tries to apprixmate the Bessel function. Then there is an accurate
regime between x=1 and x=30 where the relative error gets smaller than machine
precision for floats. This doesn't mean necessarily that the function is correct, 
but that both methods agree. Then as x continues to increase for x>30, the error 
increases once again, meaning the two methods disagree once more. The image is 
"bessel.pdf".
*/

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
#include <gsl/gsl_sf_bessel.h>  // for the GSL j10 calculaiton
using namespace std;		// we need this when .h is omitted

// function prototypes 
double down_recursion (double x, int n, int m);	// downward algorithm 
double up_recursion (double x, int n);	        // upward algorithm 

// global constants  
const double xmax = 100.0;	// max of x  
const double xmin = 0.1;	// min of x >0  
const double step = 0.1;	// delta x  
const int order = 10;		// order of Bessel function 
const int start = 50;		// used for downward algorithm 

//********************************************************************
int
main ()
{
  // define our variables
  double ans_down, ans_up, rel_error, ans_gsl, rel_error_down_gsl;

  // open an output file stream
  ofstream my_out ("bessel.dat");

  my_out << "# Spherical Bessel functions via up and down recursion" 
         << endl;
  // data file header
  my_out << "# x    Down    Up    Rel. Error    GSL    Rel. Error GSL" << endl;

  // step through different x values
  for (double x = xmin; x <= xmax; x += step)
    {
      ans_down = down_recursion (x, order, start);
      ans_up = up_recursion (x, order);
      
      // relative error calculation
      rel_error = abs(ans_down-ans_up) / (abs(ans_down) + abs(ans_up));
      
      // comparison to GSL
      ans_gsl = gsl_sf_bessel_jl(10, x);
      rel_error_down_gsl = abs(ans_gsl-ans_down) / (abs(ans_gsl) + abs(ans_down));

      // output the data
      my_out << fixed << setprecision (6) << setw (8) << x << " "
	<< scientific << setprecision (6)
	<< setw (13) << ans_down << setprecision(15) << " "
	<< setw (13) << ans_up << setprecision(15) << " "
	<< setw(13) << rel_error << setprecision(15) << " "
	<< setw(13) << ans_gsl << setprecision(15) << " "
	<< setw(13) << rel_error_down_gsl << setprecision(15)
        << endl;
    }
  cout << "data stored in bessel.dat." << endl;

  // close the output file
  my_out.close ();
  return (0);
}


//------------------------end of main program----------------------- 

// function using downward recursion  
double
down_recursion (double x, int n, int m)
{
  double j[start + 2];		// array to store Bessel functions 
  j[m + 1] = j[m] = 1.;		// start with "something" (choose 1 here) 
  for (int k = m; k > 0; k--)
    {
      j[k - 1] = ((2.* double(k) + 1.) / x) * j[k] - j[k + 1];  // recur. rel.
    }
  double scale = (sin (x) / x) / j[0];	// scale the result 
  return (j[n] * scale);
}


//------------------------------------------------------------------ 

// function using upward recursion  
double
up_recursion (double x, int n)
{
  double term_three = 0.;
  double term_one = (sin (x)) / x;	// start with lowest order 
  double term_two = (sin (x) - x * cos (x)) / (x * x);	// next order
  for (int k = 1; k < n; k += 1)	// loop for order of function     
    { // recurrence relation
      term_three = ((2.*double(k) + 1.) / x) * term_two - term_one;	       
      term_one = term_two;
      term_two = term_three;
    }
  return (term_three);
}
