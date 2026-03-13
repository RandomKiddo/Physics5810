//*********************************************************************//
//  file: area_cmdline.cpp
//
//  This program calculates the area of a circle, given the radius,
//   with input from the command line.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      28-Dec-2010  original version, from area.cpp
//
//  Notes:  
//   * compile with:  "g++ -o area_cmdline area_cmdline.cpp"
//   * we need to convert argv[1] to a double using atof 
//
//*********************************************************************// 

// include files
#include <iostream>	 // this has the cout, cin definitions
#include <stdlib.h>      // this has atoi and atof and exit
#include <cmath>         // this has atan
using namespace std;     // if omitted, then need std::cout, std::cin

//*********************************************************************//

const double pi = 4.*atan(1.);  

int
main (int argc, char *argv[])   // use the standard, if obscure, names
{
  int again = 1;

  if (argc != 2 && argc != 3)   // check if there is exactly one argument  
  { 
    // argv[0] is the program name
    cout << "usage: " << argv[0] << " <radius> <again>" << endl;
    cout << "Try again!" << endl;
    exit (0);   // quit the program  
  }

  if (argc == 3) {
    again = atoi(argv[2]);
  }

  double radius = atof(argv[1]);    // convert 1st argument to a double

  double area = pi * radius * radius;	// area formula

  for (int i = 0; i < again; ++i) {
    cout << "radius = " << radius << ",  area = " << area << endl;
  }

  return 0;			// "0" for successful completion
}

//*********************************************************************//
