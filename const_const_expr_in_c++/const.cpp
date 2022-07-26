#include<iostream>

using namespace std;

class MyClass
{

};

class T {
public:
    int SetVal(const int val) {
        _val = val;
        return _val;
    }
private:
    int _val;
};
T CreateT() {
    return T();
}

int main()
{
    // myInt is a constant (read-only) integer
    const int myInt = 26; 

    // same as the above (just to illustrate const is
    // right and also left associative)
    int const myInt1 = 26; 
    
    // a pointer to a constant instance of custom 
    // type MyClass
    const MyClass* myObject = new MyClass();
     
    // a constant pointer to an instance of custom 
    // type MyClass
    MyClass* const myObject1 = new MyClass();
    
    // myInt is a constant pointer to a constant integer
    const int someInt = 26;
    const int* const myInt2 = &someInt;
}

// Notes:
// const vs #define
//     • #define is error prone as it is not enforced by the compiler like const is. 
//       It merely declares a substitution that the preprocessor will perform without any 
//       checks; that is const ensures the correct type is used, whereas #define does not. 
//       “Defines” are harder to debug as they are not placed in the symbol table.
//     • A constant has a scope in C++, just like a regular variable, as opposed to “defined” 
//     names that are globally available and may clash. A constant must also be defined at the
//      point of declaration (must have a value) whereas “defines” can be “empty.”
//     • Code that uses const is inherently protected by the compiler against inadvertent 
//     changes: e.g., to a class’ internal state (const member variables cannot be altered,
//      const member functions do not alter the class state); to parameters being used in 
//     methods (constarguments do not have their values changed within methods) [sql_lall]. 
//     A named constant is also subject for compiler optimizations.
//     • In conclusion, you will have fewer bugs and headaches by

// Also read: https://betterprogramming.pub/understanding-all-the-details-of-c-const-4d2a4b714b63
