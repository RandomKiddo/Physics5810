//  file: flows.cpp
//
//  This program determines overflow and underflow limits                     
//                                                                     
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2007  added file output so usable on Windows
//
//  Notes:  
//   * compile with:  "g++ -o flows.x flows.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez  
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau                           
//   * comment: very crude program which produces lots of screen output
//       * now generates file flows.out but could also from command
//          line use:  "flows.x > flows2.out"
//   * How can we figure out the limits more accurately?
//  
//*********************************************************************// 

// include files
#include <iostream>		   // note that .h is omitted
#include <fstream>       // for file output
using namespace std;		

//*********************************************************************//
const int max_iterations = 1250;	        // might not be big enough to cause  
                                        // over and underflow 
int
main ()
{
  double under = 1.;    // starting values 
  double over = 1.;	

  ofstream flow_out ("flows.out");   // open a "stream" to flows.out
  for (int i = 0; i < max_iterations; i++)
  {
    under /= 2.;          // divide by two 
    over *= 2.;		  // multiply by two 

    // output both to the screen (cout) and to a file (flow_out)
    cout << i + 1 << ". under: " << under 
      << " over: " << over << endl;
    flow_out << i + 1 << ". under: " << under 
      << " over: " << over << endl;
  }

  flow_out.close();               // close the output stream
  return 0;	  		  // successful completion
}
