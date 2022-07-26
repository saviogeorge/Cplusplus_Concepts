#include<iostream>

using namespace std;

template<typename T>
void f(T& param)
{
    std::cout<<"in f"<<endl;
    std::cout<<typeid(T).name();
}
// param is a reference

int main()
{
    int x = 27;
    const int cx = x;
    const int& rx = x;
    // x is an int
    // cx is a const int
    // rx is a reference to x as a const int
}

