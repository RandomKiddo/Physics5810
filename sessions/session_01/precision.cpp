//  file: precision.cpp
//
//  This program determines machine precision e 
//   (the smallest e for which 1 + e does not equal 1)
//  Be careful when interpreting the output!                     
//                                                                     
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      02-Jan-2005  changed name from limit to precision for clarity,
//                    added test and made one a const
//      01-Jan-2007  added file output so usable on Windows
//
//  Notes:  
//   * compile with:  "g++ -o precision.x precision.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez  
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau                           
//   * comment: very crude program which produces lots of output
//  
//*************************************************************************

// include files
#include <iostream>		// basic input/output functions
#include <iomanip>		// manipulators like setprecision
#include <fstream>
using namespace std;	

//*********************************************************************
const int max_iterations = 600;

int
main ()
{
  double eps = 1.0;		// starting value
  const double one = 1.0; 

  ofstream my_out ("precision.out");   // open a "stream" to precision.out
  for (int i = 0; i < max_iterations; i++)
  {
    eps /= 1.1;		// divide by a fixed factor 
    double test = one + eps;	// is "test" different from 1.0?

    // output 12 digits in "test" to file 
    my_out << setprecision (20) << test << "  " << eps  << endl;

  }

  my_out.close();               // close the output stream
  return 0;			// successful completion
}
