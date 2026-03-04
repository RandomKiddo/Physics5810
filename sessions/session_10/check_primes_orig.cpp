//  check_primes.cpp:  Find primes up to a supplied number
//   *** THIS PROGRAM IS BUGGY!  (AND POORLY WRITTEN!) ***  
//   IT IS MEANT TO BE USED TO DEMONSTRATE THE GDB DEBUGGER.  
//                                                                      
// Original Programmer:  Norman Matloff  matloff@cs.ucdavis.edu
// Adapted by:  Dick Furnstahl  furnstahl.1@osu.edu
//
// Revision history:
//     11/21/02  original C version based on code from web
//     03/01/04  C++ version
//     03/04/06  New C++ version with some of the C errors restored
//     03/07/09  Updated the C++ version with uninitialized pointer
//
// Notes:
//  * The idea is to fill the array Prime[i] with all of
//     the prime numbers from 2 through an upper bound 
//     (called UpperBound), which is input by the user.
//  * Note that the Prime[i] array and the variable UpperBound
//     are global variables, since they are declared outside
//     of any function.
//  * Even after correcting bugs, the style here is terrible!
//  * For the debugging exercise, compile with:
//       g++ -g -O0 -o check_primes check_primes.cpp
//
//******************************************************************

#include <iostream>
using namespace std;

const int MaxPrimes = 50;
int Prime[MaxPrimes];        // Prime[I] will be 1 if I is prime, 0 otherwise 
int UpperBound;              // check up through this number for primeness 

void CheckPrime (int K);

//*********************** main ******************************
main ()
{
  int N;

  cout << "enter upper bound" << endl;
  scanf ("%d", UpperBound);

  int *true_ptr;    // declare a pointer
  *true_ptr = 1;    // set value pointed at 
  Prime[2] = *true_ptr;

  for (N = 3; N <= UpperBound; N += 2)
    CheckPrime (N);
    if (Prime[N]) cout << N << " is a prime" << endl;
}

//*************************************************************

//***************** CheckPrime ***********************
void CheckPrime (int K)
{
  int J;

  //   The plan:  see if J divides K, for all values J that are
  //    (a) themselves prime (no need to try J if it is nonprime) and
  //    (b) less than or equal to sqrt(K) (if K has a divisor larger 
  //        than this square root, it must also have a smaller one,
  //        so no need to check for larger one)
   
  J = 2;

  while (1)
  {
    if (Prime[J] == 1)
      if (K % J == 0)
      {
        Prime[K] = 0;
        return;
      }
    J++;
  }

  // if we get here, then there were no divisors of K, so it is prime 
  Prime[K] = 1;
}

