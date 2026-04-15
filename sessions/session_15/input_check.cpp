//  file: input_check.cpp
// 
//  Program to test what happens when you input non-integers when
//   asking for integers.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/18/10  original version
//
//  Notes:
//   * adapted from http://www.arachnoid.com/cpptutor/student1.html
//
//  To do:
//
//******************************************************************
#include <iostream>
#include <string>

using namespace std;

int 
main (void)
{
  int x = 0;

  do 
  {
    cout << "Enter a number (-1 = quit): ";
    cin >> x;
    
    if (x != -1) 
    {
      cout << "You entered " << x << endl << endl;
    }
  }
  while(x != -1);
  
  cout << "Quitting program." << endl;
  
  return (0);
}
