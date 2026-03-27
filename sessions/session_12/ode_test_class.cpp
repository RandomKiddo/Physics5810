//  file: ode_test_class.cpp
//
//  C++ Program to test the ode differential equation solver from
//   the gsl numerical library using the Ode class wrapper for gsl.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//     02/10/09  Original version based on ode_test.cpp
//
//  Notes:  
//   * Example taken from the GNU Scientific Library Reference Manual
//      Edition 1.1, for GSL Version 1.1 9 January 2002
//      URL: gsl/ref/gsl-ref_23.html#SEC364
//   * Compile and link with GslOde class files:
//       g++ -Wall -c ode_test_class.cpp 
//       g++ -Wall -c GslOde.cpp
//       g++ -Wall -o ode_test_class ode_test_class.o GslOde.o -lgsl -lgslcblas
//
//********************************************************************

// The following details are taken from the GSL documentation
// 
// The following program solves the second-order nonlinear 
//  Van der Pol oscillator equation (see background notes),
//
//     x"(t) + \mu x'(t) (x(t)^2 - 1) + x(t) = 0
//
// This can be converted into a first order system suitable for 
//  use with the library by introducing a separate variable for 
//  the velocity, v = x'(t).  We assign x --> y[0] and v --> y[1].
//  So the equations are:
// x' = v                  ==>  dy[0]/dt = f[0] = y[1]
// v' = -x + \mu v (1-x^2) ==>  dy[1]/dt = f[1] = -y[0] + mu*y[1]*(1-y[0]*y[0])
//
//*********************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>    // C++ stringstream class (can omit iostream)
#include <cmath>
using namespace std;

#include "GslOde.h"   // Ode class for gsl (include Ode and Rhs)
   
// Class for the right side of the Van der Pol equation.
//  Derived from the Rhs class.
//  The VdP equation depends on one parameter mu.
class Rhs_VdP : public Rhs 
{
  public:
    Rhs_VdP (double mu_passed) {mu = mu_passed; num_eqs = 2;};
    ~Rhs_VdP () {};
    virtual int rhs (double t, const double y[], double f[]);
    virtual int jacobian (double t, const double y[], double *dfdy, 
                          double dfdt[]);
    double get_mu () {return mu;};                        
  private:
    double mu;    // Van der Pol parameter
};

class Rhs_Pendulum : public Rhs {
  public:
    Rhs_Pendulum(double w0, double f, double wext) {
      omega0 = w0;
      f_ext = f;
      omega_ext = wext; 
      num_eqs = 2;
    };
    ~Rhs_Pendulum() {};

    virtual int rhs(double t, const double y[], double f[]);
    virtual int jacobian(double t, const double y[], double *dfdy, double dfdt[]);
  private:
    double omega0, f_ext, omega_ext;
};

// Function to evolve the differential equation and print the output
int evolve_and_print(Ode &vdp_ode,  Rhs_VdP &vdp_rhs, const double x0,
                     const double v0, const double tmin, 
                     const double tmax, const double delta_t);

int evolve_and_print_pendulum(Ode &pend_ode,  Rhs_Pendulum &pend_rhs, const double x0,
                     const double v0, const double tmin, 
                     const double tmax, const double delta_t);


//*************************** main program ****************************
int
main ()
{
  double x0 = 0.0;          // initial conditions
  double v0 = 0.0;

  const double eps_abs = 1.e-8;    // absolute error requested 
  const double eps_rel = 1.e-10;   // relative error requested 

  double tmin = 0.;        // starting t value 
  double tmax = 100.;      // final t value 
  double delta_t = 0.01;   // step size in time
  
  double mu = 2;             // parameter for the diff-eq 
  Rhs_VdP vdp_rhs_1 (mu);    // set up the right side of the diff-eq
    
  Ode vdp_ode_1 (vdp_rhs_1, eps_abs, eps_rel, "rk45");
  x0 = -1.5;
  v0 = 2.0;

  evolve_and_print(vdp_ode_1, vdp_rhs_1, 1.0, 0.0, tmin, tmax, delta_t);
  evolve_and_print(vdp_ode_1, vdp_rhs_1, 0.1, 0.0, tmin, tmax, delta_t);
  evolve_and_print(vdp_ode_1, vdp_rhs_1, x0, v0, tmin, tmax, delta_t);
  
  Rhs_VdP vdp_rhs_2 (3);

  evolve_and_print(vdp_ode_1, vdp_rhs_2, 1.0, 0.0, tmin, tmax, delta_t);
  evolve_and_print(vdp_ode_1, vdp_rhs_2, 0.1, 0.0, tmin, tmax, delta_t);
  evolve_and_print(vdp_ode_1, vdp_rhs_2, x0, v0, tmin, tmax, delta_t);

  Rhs_Pendulum pendulum_rhs(1.0, 0.5, 0.6);
  
  Ode pendulum_ode(pendulum_rhs, eps_abs, eps_rel, "rk45");

  double theta0 = 0.1;
  v0 = 0.0;

  evolve_and_print_pendulum(pendulum_ode, pendulum_rhs, theta0, v0, tmin, tmax, delta_t);

  return 0;
}

//*******************************************************
int
evolve_and_print(Ode &vdp_ode, Rhs_VdP &vdp_rhs, const double x0,
                 const double v0, const double tmin, const double tmax, 
                 const double delta_t)
{
  double y[2];     // current solution vector 
  y[0] = x0;       // initial x value 
  y[1] = v0;       // initial v value 

  double t = tmin;         // initialize t 
  // Set up a file name with the initial values
  ostringstream my_stringstream;  // declare a stringstream object
  my_stringstream << "ode_test_class" << "_mu_" << setprecision(2) 
                  << vdp_rhs.get_mu()
                  << "_x0_" << setprecision(2) << y[0]
                  << "_v0_" << setprecision(2) << y[1] << ".dat";
  ofstream my_out;    // now open a stream to a file for output
  my_out.open(my_stringstream.str().c_str());  

  // print initial values and column headings
  my_out << "# Running ode_test with x0 = " << setprecision(2) << y[0]
         << " and v0 = " << setprecision(2) << y[1] << endl;
  my_out << "#     t            x           v   " << endl;        
  my_out << scientific << setprecision (5) << setw (12) << t << " " 
         << setw (12) << y[0] << " " << setw (12) << y[1] << endl;

  // step to tmax from tmin 
  double h = 1e-6;    // starting step size for ode solver 
  for (double t_next = tmin + delta_t; t_next <= tmax; t_next += delta_t)
  {
    while (t < t_next)  // evolve from t to t_next 
    {
      vdp_ode.evolve ( &t, t_next, &h, y );
    }

    // print at t = t_next
    my_out << scientific << setprecision (5) << setw (12) << t << " " 
            << setw (12) << y[0] << " " << setw (12) << y[1] << endl;
  }
  my_out.close();

  return (0);    // successful completion 
}


//*******************************************************
//*******************************************************
// 
// Define the array of right-hand-side functions y[i] to be integrated.
//  The equations are:
// x' = v                  ==>  dy[0]/dt = f[0] = y[1]
// v' = -x + \mu v (1-x^2) ==>  dy[1]/dt = f[1] = -y[0] + mu*y[1]*(1-y[0]*y[0])
int
Rhs_VdP::rhs (double, const double y[], double f[])
{
  // std::cout << "rhs called with y[0] = " << y[0] << endl;
  // evaluate the right-hand-side functions at t 
  f[0] = y[1];
  f[1] = -y[0] + mu * y[1] * (1. - y[0] * y[0]);

  return 0;    // successful completion
}

//
// Define the Jacobian matrix of df_i/dy_j for i,j = {0,1}
int
Rhs_VdP::jacobian (double, const double y[], double *, double dfdt[])
{
  // fill the Jacobian matrix
  set_jacobian (0, 0, 0.0);                            // df[0]/dy[0] = 0 
  set_jacobian (0, 1, 1.0);                            // df[0]/dy[1] = 1 
  set_jacobian (1, 0, -2.0 * mu * y[0] * y[1] - 1.0);  // df[1]/dy[0] 
  set_jacobian (1, 1, -mu * (y[0] * y[0] - 1.0));      // df[1]/dy[1] 

  // set explicit t dependence of f[i] (none here)
  dfdt[0] = 0.0;
  dfdt[1] = 0.0;

  return 0;    // successful completion
}

int Rhs_Pendulum::rhs(double t, const double y[], double f[]) {
  f[0] = y[1];
  f[1] = -pow(omega0, 2) * sin(y[0]) + f_ext*cos(omega_ext*t);

  return 0;
}

int Rhs_Pendulum::jacobian(double t, const double y[], double *dfdy, double dfdt[]) {
  set_jacobian(0, 0, 0.0);
  set_jacobian(0, 1, 1.0);
  set_jacobian(1, 0, -pow(omega0, 2)*cos(y[0]));
  set_jacobian(1, 1, 0.0);

  dfdt[0] = 0.0;
  dfdt[1] = -f_ext*omega_ext*sin(omega_ext*t);

  return 0;
}

int evolve_and_print_pendulum(Ode &pend_ode,  Rhs_Pendulum &pend_rhs, const double x0,
                     const double v0, const double tmin, 
                     const double tmax, const double delta_t) {
  double y[2] = {x0, v0};
  double t = tmin;
  double h = 1e-6;

  ofstream out("pendulum_results.dat");
  out << "# t          theta        omega\n";

  for (double t_next = tmin+delta_t; t_next <= tmax; t_next+=delta_t) {
    while (t<t_next) {
      pend_ode.evolve(&t, t_next, &h, y);
    }
    out << fixed << setprecision(6) << setw(10) << t << " " 
        << setw(12) << y[0] << " " << setw(12) << y[1] << "\n";
  }

  out.close();
  return 0;
}