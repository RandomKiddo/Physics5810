#ifndef SPHERE_H
#define SPHERE_H

// Sphere class for part 5
class Sphere
{ 
  public:
    Sphere (const double rad);  // constructor

    // accessor functions
    double get_radius ();
    void set_radius (const double rad);

  private:
    double radius;  // the sphere radius
};

#endif