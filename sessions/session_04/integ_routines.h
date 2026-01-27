//  file: integ_routines.h
// 
//  Header file for integ_routines.cpp
//
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//               Ralf Bundschuh (bundschuh.2@osu.edu)
//
//  Revision History:
//    05-Jan-2004 --- original version, based on C version
//    08-Jan-2005 --- function to be integrated now passed, changed names
//    09-Jan-2011 --- changed function names
//    11-Jan-2018 --- replaced float by macro
//
//  To do:
//
//************************************************************************

//  begin: function prototypes 
 
extern FLOAT trapezoid_rule ( int num_pts, FLOAT x_min, FLOAT x_max, 
                         FLOAT (*integrand) (FLOAT x) );    // trapezoid rule 
extern FLOAT simpsons_rule ( int num_pts, FLOAT x_min, FLOAT x_max, 
                       FLOAT (*integrand) (FLOAT x) );    // Simpson's rule 
extern FLOAT gauss_quadrature( int num_pts, FLOAT x_min, FLOAT x_max, 
                       FLOAT (*integrand) (FLOAT x) );    // Gauss' rule 
   
extern void gauss(int npts, int job, double a, double b, 
                  double x[], double w[]);              // from gauss.cpp 

extern FLOAT three_eight_rule(int num_pts, FLOAT x_min, FLOAT x_max, FLOAT (*integrand) (FLOAT x)); // Three-Eight Rule

//  end: function prototypes 
