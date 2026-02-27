//  file: ArmadilloHamiltonian.cpp
// 
//  Definitions for the ArmadilloHamiltonian C++ class. 
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/07/16  Original version using GSLHamiltonian.cpp as a guide.
//
//  Notes:
//    * Documentation, including examples, is at http://arma.sourceforge.net/docs.html
//
//*****************************************************************
// include files
#include "ArmadilloHamiltonian.h"      // include the header for this class
using namespace arma;   // so we can use Armadillo functions without arma prefix

//********************************************************************

Hamiltonian::Hamiltonian (const int dim) // Constructor for Hamiltonian
{
  dimension = dim;

  // initialize the Hamiltonian matrix with zeros;  
  //  [alternative in  two steps:  Hmat = mat(dimension,dimension);   Hmat.zeros(); ]
  Hmat = zeros<mat>(dimension,dimension);
}

Hamiltonian::~Hamiltonian () // Destructor for Hamiltonian
{
  // No additional Armadillo destructor is needed (build into mat)
}

void Hamiltonian::set_element(const int i, const int j, const double value)
{
  // The i,j element of the Hamiltonian matrix is stored in i-1,j-1
  Hmat(i-1,j-1) = value;  
}

void Hamiltonian::find_eigenstuff()
{
  // Find the eigenvalues (vec) and eigenvectors (mat) of the real, symmetric
  //  matrix Hmat.  eig_sym is a standard Armadillo function.  
  //  Eigenvalues are in ascending order.
  eig_sym(eigenvalues, eigenvectors, Hmat);
}

double Hamiltonian::get_eigenvalue(int i)
{
  // The i'th eigenvalue (starting at 1) is the (i-1)'th element of vec eigenvalues
  // Assumes find_eigenstuff() has been invoked.
  return eigenvalues (i-1);
}

double Hamiltonian::get_eigenvector(int i, int j)
{
  // The j'th element of the eigenvector corresponsing to the i'th eigenvalue
  // Assumes find_eigenstuff() has been invoked.
  return eigenvectors (j-1, i-1);
}

//********************************************************************
