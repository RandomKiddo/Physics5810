/**
 * File: integration.cpp
 * 
 * Defines the behavior of the integration routines from integration.h.
 * 
 * Programmer: Neil Ghugare ghugare.1@osu.edu
 * 
 * Revision History:
 * 02-18-2026 Created original version
 * 
 * Notes:
 */

// Includes
#include "integration.h"
#include <cmath>
#include <algorithm>
#include <gsl/gsl_integration.h>

// GSL wrapper function for use with C++ functions
double gsl_wrapper(double x, void *params) {
    auto *f = static_cast<Integrand*>(params);
    return (*f)(x);
}

// Simpson integration routine
double integrate_simpson(Integrand f, double a, double b, int n) {
    if (n % 2 != 0) { ++n; }

    double h = (b-a) / n;
    double sum = f(a)+f(b);

    for (int i = 1; i < n; ++i) {
        double x = a + i*h;
        sum += (i % 2 == 0) ? 2.0*f(x) : 4.0*f(x);
    }

    return (h/3.0) * sum;
}

// Milne integration routine
double integrate_milne(Integrand f, double a, double b, int n) {
    while (n % 4 != 0) { ++n; }

    double h = (b-a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i += 4) {
        double x0 = a + i*h;
        double x1 = x0 + h;
        double x2 = x0 + 2*h;
        double x3 = x0 + 3*h;
        double x4 = x0 + 4*h;

        sum += (4.0*h / 90.0) * (7.0*f(x0) + 32.0*f(x1) + 12.0*f(x2) + 32.0*f(x3) + 7.0*f(x4));
    }

    return sum;
}

// GSL integration routine
// Here we have to keep an eye on GSL integration workspaces and memory allocations
// We chose the QAG routine
std::pair<double, double> integrate_gsl(Integrand f, double a, double b) {
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
    
    double res_gsl, error;
    gsl_function F;
    F.function = &gsl_wrapper;
    F.params = &f;

    gsl_integration_qag(&F, a, b, 0.0, 1.0e-9, 1000, GSL_INTEG_GAUSS61,
                        w, &res_gsl, &error);
    gsl_integration_workspace_free(w);

    return {res_gsl, error};
}