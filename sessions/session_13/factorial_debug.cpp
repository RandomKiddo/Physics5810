//  file: factorial.cpp
// 
//  Program to try out a recursive implementation of factorial
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/18/10  original version
//
//  Notes:
//   * Based on http://www.cprogramming.com/debugging/segfaults.html
//
//******************************************************************

// include files
#include <iostream>     
#include <iomanip>      
#include <cmath>
using namespace std;    

// function prototypes
int factorial (int n);

//*************************** main program ***************************
int
main (void)
{
  const int n_max = 5;
  int stored_factorials[n_max] = {0};

  for (int i=0; i < n_max; i++)
  {
    stored_factorials[i] = factorial(i);
  }
  
  // int j = 2; 
  // int k = 3;
  
  cout << stored_factorials[0] << " " << stored_factorials[n_max-1] << endl; 

  int dynamic_max = 0;
  cout << "Input maximum integer: ";
  cin >> dynamic_max;
  int *dynamic_factorials = new int [dynamic_max + 1];
  
  for (int i=0; i <= dynamic_max; i++)
  {
    dynamic_factorials[i] = factorial(i);
    cout << i << "! = " << dynamic_factorials[i] << endl;
  }
    
  return (0);                  // successful completion 
}

//*************************************************************

//************************* factorial *******************************
//
// Calculate n! recursively.
//
//****************************************************************
int
factorial (int n)
{
  if (n == 0)
  {
     return 1;
  } 
  else
  {
     return n * factorial(n-1);
  }   
}
