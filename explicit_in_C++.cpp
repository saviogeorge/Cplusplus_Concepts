
// C++ program to illustrate default
// constructor without 'explicit'
// keyword
#include <iostream>
using namespace std;
 
class Complex {
private:
    double real;
    double imag;
 
public:
   
    // Default constructor
    // Complex(double r = 0.0,
    //         double i = 0.0) : real(r),
    //                           imag(i)
    // {
    // }

    // If we use the below version 
    // we get compilation error 
    // without explicit conversion
    explicit Complex(double r = 0.0,
            double i = 0.0) : real(r),
                              imag(i)
    {
    }
 
    // A method to compare two
    // Complex numbers
    bool operator == (Complex rhs)
    {
        return (real == rhs.real &&
                imag == rhs.imag);
    }
};
 
// Driver Code
int main()
{
    // a Complex object
    Complex com1(3.0, 0.0);
 
    // if (com1 == 3.0)
    //     cout << "Same";
    // else
    //     cout << "Not Same";
    // return 0;

    // This will work with the explicit
    // as we are explicity type casting
    // it.
    if (com1 == (Complex)3.0)
        cout << "Same";
    else
        cout << "Not Same";
    return 0;
}
// Notes:
// in C++, if a class has a constructor which can be called with a single 
// argument, then this constructor becomes a conversion constructor because 
// such a constructor allows conversion of the single argument to the class 
// being constructed. 
// We can avoid such implicit conversions as these may lead to unexpected 
// results. We can make the constructor explicit with the help of an explicit keyword
// https://www.geeksforgeeks.org/use-of-explicit-keyword-in-cpp/#:~:text=Explicit%20Keyword%20in%20C%2B%2B%20is%20used%20to%20mark%20constructors,can%20be%20used%20in%20typecasting.
