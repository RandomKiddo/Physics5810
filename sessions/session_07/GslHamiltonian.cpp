//  file: GslHamiltonian.cpp
// 
//  Definitions for the GslHamiltonian C++ class. 
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      01/25/09  Original version using eigen_tridiagonal.cpp as a guide.
//
//*****************************************************************
// include files
#include <gsl/gsl_eigen.h>	// include the appropriate GSL header file 
#include "GslHamiltonian.h"      // include the header for this class

//********************************************************************

Hamiltonian::Hamiltonian (const int dim) // Constructor for Hamiltonian
{
  dimension = dim;
  
  //  Allocate space for the vectors, matrices, and workspace 
  Hmat_ptr = gsl_matrix_alloc (dimension, dimension);  // Hamiltonian 
  Eigval_ptr = gsl_vector_alloc (dimension);  // eigenvalue vector	
  Eigvec_ptr = gsl_matrix_alloc (dimension, dimension); // eigenvector matrix	
  worksp= gsl_eigen_symmv_alloc (dimension);  // workspace	
  eigenvector_ptr = gsl_vector_alloc (dimension);  // one eigenvector	
}

Hamiltonian::~Hamiltonian () // Destructor for Hamiltonian
{
  // free the space used by the vector and matrices  and workspace 
  gsl_matrix_free (Eigvec_ptr);
  gsl_vector_free (Eigval_ptr);
  gsl_matrix_free (Hmat_ptr);
  gsl_vector_free (eigenvector_ptr);
  gsl_eigen_symmv_free (worksp);
}

void Hamiltonian::set_element(const int i, const int j, const double value)
{
  // The i,j element of the matrix is stored as the i-1,j-1 element of
  //  the GSL matrix
  gsl_matrix_set (Hmat_ptr, i-1, j-1, value);  
}

void Hamiltonian::find_eigenstuff()
{
  // Find the eigenvalues and eigenvectors of the real, symmetric
  //  matrix pointed to by Hmat_ptr.  It is partially destroyed
  //  in the process. The eigenvectors are pointed to by 
  //  Eigvec_ptr and the eigenvalues by Eigval_ptr.
  gsl_eigen_symmv (Hmat_ptr, Eigval_ptr, Eigvec_ptr, worksp);

  // Sort the eigenvalues and eigenvectors in ascending order by default 
  gsl_eigen_symmv_sort (Eigval_ptr, Eigvec_ptr, GSL_EIGEN_SORT_VAL_ASC);
}

double Hamiltonian::get_eigenvalue(int i)
{
  return gsl_vector_get (Eigval_ptr, i-1);
}

double Hamiltonian::get_eigenvector(int i, int j)
{
  gsl_matrix_get_col (eigenvector_ptr, Eigvec_ptr, i-1);
  return gsl_vector_get (eigenvector_ptr, j-1);
}

//********************************************************************
