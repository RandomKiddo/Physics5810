// Sphere implementation for part 5

// include files
#include "Sphere.h"      // include the header for this class
#include <iostream>

Sphere::Sphere (const double rad) // Constructor for Circle
{
  radius = rad;    // set the internal (private) radius to the passed value
}

void Sphere::set_radius(const double rad)
{
  radius = rad;
}

double Sphere::get_radius()
{
  return radius;
}
