//  file: ArmadilloHamiltonian.h
//
//  Header file for the ArmadilloHamiltonian C++ class.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      01/25/09  original version of GSLHamiltonian
//      02/07/16  first version of ArmadilloHamiltonian
//
//  Notes:
//   * Uses standard Armadillo matrix and vector objects and functions
//   * Documentation, including examples, is at http://arma.sourceforge.net/docs.html
//
//  To do:
//   * check that find_eigenstuff has been run before get_eigenvalue
//      and get_eigenvector.
//   * make get_eigenvector more efficient
//
//*****************************************************************

// The ifndef/define macro ensures that the header is only included once
#ifndef ARMADILLOHAMILTONIAN_H
#define ARMADILLOHAMILTONIAN_H

// include files
#include <armadillo>	// include the Armadillo header file

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
    int dimension;            // the matrix dimension
    arma::mat Hmat;           // Armadillo matrix for the Hamiltonian  
    arma::vec eigenvalues;    // vector of eigenvalues
    arma::mat eigenvectors;   // matrix of eigenvectors
};

#endif
