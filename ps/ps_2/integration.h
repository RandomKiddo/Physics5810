/**
 * File: integration.h
 * 
 * This program is a header to define external integration routines for testing and numerical analysis.
 * 
 * Programmer: Neil Ghugare ghugare.1@osu.edu
 * 
 * Revision History:
 * 02-18-2026 Created original version
 * 
 * Notes:
 */

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <functional>

// we define the following term for easier-to-understand usage in our integration C++ files
using Integrand = std::function<double(double)>;

// define the external integration routines
extern double integrate_simpson(Integrand f, double a, double b, int n);
extern double integrate_milne(Integrand f, double a, double b, int n);
extern std::pair<double, double> integrate_gsl(Integrand f, double a, double b);

#endif 