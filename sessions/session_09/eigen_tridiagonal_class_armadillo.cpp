//  file: eigen_tridiagonal_class.cpp
// 
//  Program to find bound state eigenvalues for a potential by
//  discretizing and then diagonalizing the Hamiltonian in
//  coordinate representation using a Hamiltonian class that
//  is a "wrapper" for the GSL eigenvalue/eigenvector routines.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      01/25/09  modified eigen_tridiagonal.cpp to move the GSL
//                 dependent parts to a Hamiltonian class.
//      02/07/16  switched header to ArmadilloHamiltonian
//
//  Notes:
//   * We follow the Session 5 notes for method 2 of solving the
//      Schrodinger equation by matrix diagonalization in
//      coordinate representation.  This uses a finite difference
//      approximation to the 2nd derivative.
//   * We apply the method to a three-dimensional harmonic oscillator
//      with angular momentum l=0.
//   * We use units in which hbar = 1, k = 1/2, and M = 1/2.  
//     The eigenvalues for the 3d harmonic oscillator are then (l=0)
//       hbar omega (2n + 3/2) = 2n + 3/2 for n = 0,1,2,3,...
//
///*****************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>
#include <cmath>
using namespace std;

#include "ArmadilloHamiltonian.h"	// include the Hamiltonian class definitions

inline double sqr(double x) {return x*x;};
double V_ho(double r);

//************************** main program ***************************
int
main ()
{
  // Choose Rmax (maximum radius)
  double Rmax = 5.;
  cout << "Enter maximum radius (Rmax): ";
  cin >> Rmax;

  // Pick the value of the number of steps N 
  int N = 0;		
  cout << "Enter the number of steps (N): ";
  cin >> N;
  
  // Calculate h = Delta r
  double h = Rmax/double(N);
  double hsq = sqr(h);
  
  // The matrix dimension is N-1 (see the notes).
  int dimension = N-1;

  // Create the Hamiltonian object called my_hamiltonian
  Hamiltonian my_hamiltonian(dimension);

  // Load the Hamiltonian matrix 
  for (int i = 1; i <= dimension; i++)
  {
    for (int j = 1; j <= dimension; j++)
    {
      double Hij;
      if (i == j)                  // diagonal matrix element
      {
        double r = double(i)*h;    // radial coordinate
        Hij = 2./hsq + V_ho(r); 
      }
      else if (i == j+1)          // just above the diagonal
      {
        Hij = -1./hsq;
      }
      else if (i == j-1)          // just below the diagonal
      {
        Hij = -1./hsq;
      }
      else                        // all the other elements
      {
        Hij = 0.;                 
      }
 
      my_hamiltonian.set_element(i,j,Hij);   // set the i,j element to Hij
    }
  }
  
  // Find eigenvalues and eigenvectors in ascending order
  my_hamiltonian.find_eigenstuff();


  // Print out the results   
  for (int i = 1; i <= dimension; i++)
  {
    double eigenvalue = my_hamiltonian.get_eigenvalue(i);

    cout << "eigenvalue " << i << " = " 
         << scientific << eigenvalue << endl;

    // Print out the eigenvector with the lowest eigenvalue to a file
    if (i == 1)
    {
      ofstream eigout ("eigen_tridiagonal_armadillo.dat");  // open an output file
      eigout << "# 3D harmonic oscillator" << endl;
      eigout << "# eigenvalue = " << scientific << eigenvalue << endl;
      eigout << endl << "#   r       u(r)" << endl;
      eigout << fixed << 0.0 << " " << 0.0 << endl;  // first point is u(0)=0.
      for (int j = 1; j <= dimension; j++)
      {
        eigout << fixed << double(j)*h << " "
               << scientific << my_hamiltonian.get_eigenvector(i,j) << endl;
      }
      eigout.close();  // close the output stream
    }
  }

  return (0);			// successful completion 
}

//************************************************************

//************************** V_ho ***************************
//
// Harmonic oscillator potential with k = 1./2.  
//  With m = 1/2 and hbar = 1, this means the energies
//  are 3/2, 7/2, 11/2, ... 
//
//**************************************************************
double
V_ho (double r)
{
  double k = 1./2.;

  return (k*r*r/2.);
}
//**************************************************************
