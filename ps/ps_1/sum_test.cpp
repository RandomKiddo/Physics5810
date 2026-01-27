//  file: sum_test.cpp
//
//  Tests the differences in summing up and down due to round-off error.
//
//  Programmer:  Neil Ghugare ghugare.1@osu.edu
//
//  Revision history:
//      01-23-2026 Original version for PS1
//
//  Notes:  
//   * compile with:  "g++ -o sum_test.x sum_test.cpp"
//
//*********************************************************************//

/*
Interpreting the graph for 2(c):
For the small N region for log10(N)<4, the relative error oscillates around 
a "floor" near 1e-7. This corresponds to being close to machine precision for
floats, and because N is small, the number of operations is insufficient to 
show a clear trend, errors dominated by rounding fluctuations. Then there is 
a power law region from about 4<log10(N)<7, where we get a power law relationship
approximately growing as N^2. Then at the large N region log10(N)>7, as N increases,
the errors start to plateau or saturate. This likely occurs since S(up) effectively
stops adding new values when 1/n because smaller than the precision gap of the 
current sum. Mathematically, S(up)=S(down), but due to how floating point numbers
are stored, they behave differently in a computer. When calculating S(up), you start
with large numbers, but as the sum grows, we eventually are added very tiny values 
of 1/n to a relatively large running total. Because of a float's lesser precision, 
these values are eventually rounded to zero and lost. While, with S(down), we start 
with the small values first, allowing them to accumulate to a significant subtotal
as we add the larger numbers at the end of the loop (e.g., 0.5 and 1.0). This helps
preserve the final result better, or leads to better accuracy, which is why the
downward sum is considered more precise.
*/

#include <iostream>
#include <iomanip> // for setprecision function
#include <fstream> // for files
#include <cmath> // for log10

// function declarations
float sum_up(int N);
float sum_down(int N);

int main(int argc, char **argv) {
    // get the maximum number of iterations, a.k.a. the maximum N for the sum
    int N = -1;
    do {
        std::cout << "Enter loop max N: ";
        std::cin >> N;
    } while (N < 0);

    // open a file
    std::ofstream fout("sum_test.dat");
    fout << "#    log(N)    S(up)    S(down)    Relative Error\n";

    // loop through the sums as a function of N
    for (float j = 1.0f; j < (float)N; j *= 1.01f) {  // logarithmic-style loop to allow for better usage of N=1e8 or greater
        // current integer
        int i = (int)j;

        // calculate the sums
        float up = sum_up(i);
        float down = sum_down(i);

        // calculate the relative error
        float error = 2.0*std::abs(up-down)/(std::abs(up)+std::abs(down));

        // no error, same value, undefined for log-log we'll use later
        if (error == 0.0f) {
            continue;
        }

        // output them to the file
        fout << std::setprecision(12) << std::log10(i) << " "
             << std::setprecision(12) << up << " "
             << std::setprecision(12) << down << " "
             << std::setprecision(12) << std::log10(error) << "\n";
    
        // safety check, check if i doesn't change due to casting
        if ((int)(j*1.01f) == i) {
            j += 1.0f;
        }
    }

    // close the file
    fout.close();

    return 0;
}

// function that sums 1/n upwards from 1 to N
float sum_up(int N) {
    float sum = 0.0;
    for (int n = 1; n <= N; ++n) {
        sum += (1.0f/n);
    }

    return sum;
}

// function that sums 1/n downwards from N to 1
float sum_down(int N) {
    float sum = 0.0;
    for (int n = N; n >= 1; --n) {
        sum += (1.0f/n);
    }

    return sum;
}