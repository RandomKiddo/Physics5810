//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Neil Ghugare ghugare.1@osu.edu
//
//  Revision history:
//      01-22-2026 Fetched original version from Dick Furnstahl
//      01-23-2026 Modified for better precision and encapsulation
//
//  Notes:  
//   * compile with:  "g++ -o area.x area.cpp"
//
//  To-do items that are completed in this file:
//   1. output the answer with higher precision (more digits)
//   2. use a "predefined" value of pi or generate it with atan
//   3. define an inline square function
//   4. split the calculation off into a function (subroutine)
//   5. output to a file (and/or input from a file)
//   6. add checks of the input (e.g., for non-positive radii)
//   7. rewrite using a Circle class
//
//*********************************************************************//

#include <iostream>
#include <iomanip> // allows us to control precision of floating-point numbers when printing
#include <fstream> // for files

// part 7, rewrite using a class
// part 7, rewrite using a class
class Circle {
  private:

  double radius; // the radius of the circle

  const double PI = 4.0 * std::atan(1.0); // part 2, generate a value of pi using atan

  public:

  // Constructs a new circle instance of radius r
  Circle(double r) {
    radius = r;
  }
  
  // Calculates the area of the current circle instance
  // parts 3 and 4, an inline function and is split into a function
  inline double area(void) {
    return PI * radius * radius;
  }
};

int main(int argc, char **argv) {
  // Fetch a radius from the terminal input
  // part 6, adds checks to terminal input
  double radius = -1.0;
  do {
    std::cout << "Enter a radius value: ";
    std::cin >> radius; 
  } while(radius < 0);

  // Instantiate a new circle instance
  Circle circle(radius);

  // Calculate the area using the instance's function
  double area = circle.area();

  // Print the output 
  std::cout << "For a circle of radius " << radius << "\n";
  std::cout << "The area is " <<  std::setprecision(10) << area << "\n";

  // part 5, output to file 
  std::ofstream out("area.dat");
  out << "#  radius  area\n";
  out << radius << " " << std::setprecision(10) << area << "\n";
  out.close();

  return 0;
}