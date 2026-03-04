//  file: Circle.cpp
// 
//  Definitions for the Circle C++ class. 
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/05/09  Original version.
//
//*****************************************************************
// include files
#include "Circle.h"      // include the header for this class

//********************************************************************

#include <iostream>

const double pi = 3.1415926535897932385;	// define pi 

Circle::Circle (const double rad) // Constructor for Circle
{
  radius = rad;    // set the internal (private) radius to the passed value
  
  // For debugging, print a message when we make a circle
  std::cout << "A circle of radius " << radius
            << " is created ..." << std::endl;
}

Circle::~Circle () // Destructor for Circle (not much to do here!)
{
  // For debugging, print a message when a circle goes out of scope
  std::cout << "A circle of radius " << radius 
            << " is destroyed ..." << std::endl;  
}

void Circle::set_radius(const double rad)
{
  radius = rad;
}

double Circle::get_radius()
{
  return radius;
}

double Circle::area()
{
  return pi * sqr(radius);
}

// Circumference function added
double Circle::circumference() {
  return 2*pi*radius;
}

//********************************************************************
