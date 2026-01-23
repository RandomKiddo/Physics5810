//  file: J0_test.cpp
//
//  C++ Program to demonstrate use of the J0 Bessel function from
//   the gsl numerical library.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      12/26/03  original C++ version, modified from C version
//      01/03/05  switched to <cmath>
//      01/12/16  upgraded notes
//
//  Notes:  
//   * Example taken from the GNU Scientific Library Reference Manual
//      for GSL Version 2.1.  URL: http://www.gnu.org/software/gsl/manual/
//   * Compile and link with the GSL libraries using:
//       g++ -Wall -o J0_test.x J0_test.cpp -lgsl -lgslcblas
//   * GSL routines have built-in 
//       extern "C" {
//          <header stuff>
//       }
//      so they can be called from C++ programs without modification
//   * The answer should be J0(5) = -1.775967713143382920e-01 
//
//*********************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#include <gsl/gsl_sf_bessel.h>  // gsl Bessel special function header file

int
main ()
{
  double x = 3.0;   // just a random test value

  double y = gsl_sf_bessel_J0 (x);   // see the GSL manual for details

  std::cout << "J0(" << x << ") = " 
            << std::setprecision(18) << std::setw(20) << y << std::endl;

  return 0;
}
