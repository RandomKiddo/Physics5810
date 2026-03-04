//  file: GslHamiltonian.h
//
//  Header file for the GslHamiltonian C++ class.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      01/25/09  original version
//
//  Notes:
//   * We encapsulate GSL matrix eigenvalue functions in this class
//   * The GSL header file is included in GslHamiltonian.cpp and
//      anywhere we want to create GslHamiltonian objects.
//   * Based on the documentation for the GSL library under
//      "Eigensystems" and on Chap. 15 of "Computational Physics"
//      by Landau and Paez.
//   * See the GSL documentation for matrix, vector structures 
//   * Uses the GSL functions for computing eigenvalues
//      and eigenvectors of matrices.  The steps for this part are:
//       * define and allocate space for matrices and vectors we need
//       * load the matrix to be diagonalized (pointed to by Hmat_ptr)
//       * find the eigenvalues and eigenvectors with gsl_eigensymmv
//       * sort the results numerically 
//       * print out the results  
//   * As a convention (advocated in "Practical C++"), we'll append
//      "_ptr" to all pointers.
//   * When sorting eigenvalues,
//      GSL_EIGEN_SORT_VAL_ASC => ascending order in numerical value 
//      GSL_EIGEN_SORT_VAL_DESC => descending order in numerical value 
//      GSL_EIGEN_SORT_ABS_ASC => ascending order in magnitude 
//      GSL_EIGEN_SORT_ABS_DESC => descending order in magnitude
//
//  To do:
//   * check that find_eigenstuff has been run before get_eigenvalue
//      and get_eigenvector.
//   * make get_eigenvector more efficient
//
//*****************************************************************

// The ifndef/define macro ensures that the header is only included once
#ifndef GSLHAMILTONIAN_H
#define GSLHAMILTONIAN_H

// include files
#include <gsl/gsl_eigen.h>	// include the appropriate GSL header file(s) 

class Hamiltonian
{ 
  public:
    Hamiltonian (const int dim);  // constructor
    ~Hamiltonian ();  // destructor

    // accessor functions
    void set_element(const int i, const int j, double value);
    void find_eigenstuff();
    double get_eigenvalue(const int i);
    double get_eigenvector(const int i, const int j);    

  private:
    int dimension;  // the matrix dimension
    gsl_matrix *Hmat_ptr;    // gsl matrix with Hamiltonian  
    gsl_vector *Eigval_ptr;  // gsl vector with eigenvalues  
    gsl_matrix *Eigvec_ptr;  // gsl matrix with eigenvectors 
    gsl_eigen_symmv_workspace *worksp;  // the workspace for gsl	
    gsl_vector *eigenvector_ptr;  // one of the eigenvectors	
};

#endif
