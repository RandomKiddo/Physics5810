//  file: area_files.cpp
//
//  This program calculates the area of a circle, given the radius.
//   This version reads in input from a file and outputs to another file.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      28-Dec-2010  original version, from area.cpp
//
//  Notes:  
//   * compile with:  "g++ -o area_files area_files.cpp"
//   * this version has hardwired filenames; we could also allow
//      optionally to pass them as command-line arguments
//
//*********************************************************************// 

// include files
#include <iostream>	 // this has the cout, cin definitions
#include <iomanip>       // manipulators like setprecision
#include <fstream>	 // file input and output
#include <cmath>         // M_PI lives here
#include <string>        // strings and things
#include <stdlib.h>      // this has exit
using namespace std;     // if omitted, then need std::cout, std::cin

//*********************************************************************//

const double pi = M_PI;   // define pi using the cmath pre-defined version 
double area (double radius);   // separate out the area calculation

int
main (void)       // no command-line arguments here
{
  ifstream input_file ("area_files.inp", ios::in);  // open for input only
  if (input_file.bad())   // check if the file is there and can be read
  {
    cerr << "Unable to open area_files.inp. " << endl;
    exit(1);   // bail out
  }
  
  // open the output file so that old versions are overwritten ("trunc")
  ofstream output_file ("area_files.out", ios::out|ios::trunc);
  output_file << "#  radius      area      integer   " << endl;

  // print radii to the output file
  string line;   // entire line from the input file
  while (getline(input_file,line))
  {
    if (line[0] == '#')   // skip line if the first character is "#"
    {
      cout << "comment line: " << line << endl;
    } 
    else   // we assume this is a real line
    {    
      double radius;
      int integer;
      sscanf(line.c_str(),"%lf %d",&radius, &integer);  // find a double (%lf) in line

      output_file << setw(8) << fixed << setprecision(2) << radius << "  " 
                  << setw(12) << setprecision(3) << area(radius) <<  " " << integer << endl;
    }  
  }

  input_file.close();
  output_file.close();

  return 0;			// "0" for successful completion
}

//*********************************************************************//

double
area (double radius)
{
  return pi * radius * radius;  // area formula
}

//*********************************************************************//
