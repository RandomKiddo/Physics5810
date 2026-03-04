//  file: Circle.h
//
//  Header file for the Circle C++ class.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/05/09  original version
//
//  Notes:
//   * 
//
//  To do:
//   * Add additional methods (e.g., for circumfrence)
//
//*****************************************************************

// The ifndef/define macro ensures that the header is only included once
#ifndef CIRCLE_H
#define CIRCLE_H

// include files

class Circle
{ 
  public:
    Circle (const double rad);  // constructor
    ~Circle ();  // destructor

    // accessor functions
    double get_radius ();
    void set_radius (const double rad);
    double area ();
    double circumference();  // circle circumference function added

  private:
    double radius;  // the circle radius
    inline double sqr (const double x) {return x*x;};  // inline function
};

#endif
