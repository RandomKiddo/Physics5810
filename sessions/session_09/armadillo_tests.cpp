//  file: other_armadillo_tests.cpp
//
//  This is a test program for basic Armadillo functionality.               
//                                                                     
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      18-Feb-2016  original version, modifying example from M. Hjorth-Jensen
//
//  Notes:
//    * Armadillo documentation, including examples, is at 
//          http://arma.sourceforge.net/docs.html
// 
//************************************************************************
#include <iostream> 
#include <armadillo>

using namespace std;
using namespace arma;     // so we can use Armadillo functions without arma prefix

int main()
 {
   // Print out the version of the Armadillo library
   cout << "Armadillo version: " << arma_version::as_string() << endl << endl;

   // You declare (create) a matrix object with "mat" 
   mat A_mat;

   // One way to load the matrix is with an initializer list
   A_mat = {
             {0.165300 , 0.454037 , 0.995795 , 0.124098 , 0.047084 },
             { 0.688782 , 0.036549 , 0.552848 , 0.937664 , 0.866401 },
             { 0.348740 , 0.479388 , 0.506228 , 0.145673 , 0.491547 },
             { 0.148678 , 0.682258 , 0.571154 , 0.874724 , 0.444632 },
             { 0.245726 , 0.595218 , 0.409327 , 0.367827 , 0.385736 }
           };

   // Two methods:  .n_rows = number of rows  and  .n_cols = number of columns
   cout << "A_mat.n_rows = " << A_mat.n_rows << endl;
   cout << "A_mat.n_cols = " << A_mat.n_cols << endl;

   // Print the matrix A_mat with another method (the argument is a string)
   A_mat.print("A_mat =");
   cout << endl;

   // Calculate the determinant
   cout << "determinant det(A_mat) = " << det(A_mat) << endl << endl;
   
   // Calculate the inverse of the matrix two ways
   cout << "inv(A_mat) = " << endl << inv(A_mat) << endl;
   cout << "A_mat.i() = "  << endl << A_mat.i() << endl;

   // Check a simple matrix multiplication (why are there non-zero entries?)
   cout << "A_mat * inv(A_mat) = " << endl << A_mat * inv(A_mat) << endl;
   cout << "A_mat * A_mat.i() = "  << endl << A_mat * A_mat.i()  << endl;

   // Save the matrix to a file
   A_mat.save("A_mat_save.txt", raw_ascii);

   // Define a new matrix B_mat which reads A_mat from file
   mat B_mat;
   B_mat.load("A_mat_save.txt");
   B_mat += 3.0*A_mat;  // add 3 times A_mat to B_mat 
   B_mat.print("The matrix B_mat:");

   // Transpose of B
   cout << "trans(B_mat) =" << endl;
   cout << trans(B_mat) << endl;

   // trace = sum along diagonal
   cout << "trace(B_mat) = " << trace(B_mat) << endl;

   // Create an identity matrix
   mat C_mat = eye<mat>(5,5);
   C_mat.print("\nThe 5x5 identity matrix:");
   cout << endl;

   // random matrix -- values are uniformly distributed in the [0,1] interval 
   mat D_mat = randu<mat>(5,5);
   D_mat.print("Random matrix D_mat:");
   cout << endl;

   // sum of four matrices (no temporary matrices are created)
   mat E_mat = A_mat + B_mat + C_mat + D_mat;
   E_mat.print("E_mat = A_mat + B_mat + C_mat + D_mat:");

   // Solving linear equation A x = b 
   vec b_vec, x_vec;
   b_vec = { 1.0 , 2.0 , 3.0 , 4.0 , 5.0 };
   x_vec = inv(A_mat) * b_vec;
   x_vec.print("\nSolution vector x_vec:");
   cout << "Check the result of A_mat * x_vec: " << endl 
        << A_mat * x_vec 
        << " compared to b_vec" << endl
        << b_vec << endl;
   // We can also do it directly with solve:
   vec x_vec_alt = solve(A_mat,b_vec);
   cout << "Using solve to find x_vec: " << endl << x_vec_alt << endl;

  cout << "Now for Question 7" << endl;
  A_mat = {
    {1.0, 2.0, 3.0},
    {2.0, -3.0, 4.0},
    {1.0, 4.0, -2.0}
  };
  b_vec = { 2.0, 5.0, -2.0 };
  x_vec = inv(A_mat)*b_vec;
  x_vec.print("\nSolution vector x_vec:");
  cout << "Check the result of A_mat * x_vec: " << endl 
        << A_mat * x_vec 
        << " compared to b_vec" << endl
        << b_vec << endl;

   return 0; 
}
