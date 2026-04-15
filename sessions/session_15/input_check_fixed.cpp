//  file: input_check_fixed.cpp
// 
//  Program to test what happens when you input non-integers when
//   asking for integers.  This is the modified version, that doesn't
//   go crazy when you do this!
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/18/10  original version
//
//  Notes:
//   * adapted from http://www.arachnoid.com/cpptutor/student1.html
//   * cin returns a true or false boolean value (the variable type
//      is "bool") according to whether or not the input was successful.
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
  bool status = true;  // This will be our flag for whether cin was successful

  do 
  {
    cout << "Enter a number (-1 = quit): ";
    
    status = (bool)(cin >> x);
    if (!status) 
    {    // status=false takes us here
      string bad_input;
      cout << "You broke the input stream!" << endl;
      cin.clear();    // This step is necessary, but doesn't fix the stream.
      cin >> bad_input;  // The bad input is still in the stream.  Get it!
      cout << "You typed \"" << bad_input 
           << "\" instead of an integer." << endl;
      cout << "Please try again." << endl << endl;
    }
    else if (x != -1) 
    {
      cout << "You entered " << x << endl << endl;
    }
  }
  while(x != -1);
  
  cout << "Quitting program." << endl;
  
  return (0);
}
