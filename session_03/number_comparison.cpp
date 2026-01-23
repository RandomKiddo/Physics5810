//  file: number_comparison.cpp 
//
//  How to (not) compare floating point numbers    
//                                                                     
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      10-Jan-2006  original version
//
//  Notes:  
//   * compile with:  "g++ -o number_comparison number_comparison.cpp"
//  
//************************************************************************

// include files
#include <iostream>
#include <iomanip>
using namespace std;		// we need this when .h is omitted
#include <cmath>

//********************************************************************
int
main ()
{
  float pi = 3.141592653589793;

  float x1 = cos(pi/4.)/sin(pi/4.);
  float x2 = 1.;
  
  cout << setprecision(15) << fixed;
  
  cout << "x1: " << x1 << endl;
  cout << "x2: " << x2 << endl;
  
  if (x1 == x2)
  {
    cout << " x1 and x2 are equal " << endl;
  }
  else
  {
    cout << " x1 and x2 are not equal " << endl;
  }

  return (0);
}


//------------------------end of main program----------------------- 
