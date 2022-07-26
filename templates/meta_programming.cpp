// Template metaprogramming is in fact Turing-complete, 
// meaning that any computation expressible by a computer 
// program can be computed, in some form, by a template
// metaprogram


#include <iostream>

template <int N>                                                                 // (2)
struct Factorial{
    static int const value = N * Factorial<N-1>::value;
};

template <>                                                                      // (3)
struct Factorial<1>{
    static int const value = 1;
};

// Manipulating Types at Compile Time
// An example.
template<typename T > 
struct removeConst{ 
    typedef T type;               // (1)
};

template<typename T > 
struct removeConst<const T> { 
    typedef T type;               // (1)
};

int main(){
    
    std::cout << std::endl;
    
    std::cout << "Factorial<5>::value: " << Factorial<5>::value << std::endl;    // (1)
    std::cout << "Factorial<10>::value: " << Factorial<10>::value << std::endl;
    
    std::cout << std::endl;

    // In the case of removeConst<int> the first or general class 
    // template kicks in; in the case of removeConst<const int>, 
    // the partial specialisation for const T applies. 
    // The key observation is that both class templates 
    // return the underlying type in line (1) and, therefore, the constness is removed.
    std::is_same<int, removeConst<int>::type>::value;        // true
    std::is_same<int, removeConst<const int>::type>::value;  // true

}