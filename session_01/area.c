/* 
************************************************************************
*  area.c: Area of a circle, sample program                            *
*                                                                      *
*  taken from: "Projects in Computational Physics" by Landau and Paez  * 
*              copyrighted by John Wiley and Sons, New York            *      
*                                                                      *
*  written by: students in PH465/565, Computational Physics,           *
*              at Oregon State University                              *
*              code copyrighted by RH Landau                           *
*  supported by: US National Science Foundation, Northwest Alliance    *
*                for Computational Science and Engineering (NACSE),    *
*                US Department of Energy                               *
*                                                                      *
*  UNIX (DEC OSF, IBM AIX): cc area.c -lm                              *
*                                                                      *
************************************************************************
*/
#include <stdio.h> 

#define PI 3.1415926535897932385E0

main()
{ 
   double radius, area;                           /* define variables */

   printf("Enter the radius of a circle \n");     /* ask for radius */
   scanf("%lf", &radius);                         /* read in radius  */

   area = radius * radius * PI;                   /* area formula */

   printf("radius=%f, area=%f\n", radius, area);  /* print results */    
} 

