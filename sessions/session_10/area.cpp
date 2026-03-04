//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2010  updates to "To do" wishlist
//
//  Notes:  
//   * compile with:  "g++ -o area area.cpp"
//
//  To do:
//   1. output the answer with higher precision (more digits)
//   2. use the "predefined" value of pi or atan
//   3. define an inline square function
//   4. split the calculation off into a function (subroutine)
//   5. output to a file (and/or input from a file)
//   6. rewrite using a Circle class
//
//*********************************************************************// 

// include files
#include <iostream>	 // this has the cout, cin definitions
using namespace std;     // if omitted, then need std::cout, std::cin

//*********************************************************************//

const double pi = 3.1415926535897932385;   // define pi as a constant 

int
main ()
{
  double radius;    // every variable is declared as int or double or ...

  cout << "Enter the radius of a circle: ";	// ask for radius
  cin >> radius;

  double area = pi * radius * radius;	// area formula

  cout << "radius = " << radius << ",  area = " << area;

  return 0;			// "0" for successful completion
}

//*********************************************************************//
