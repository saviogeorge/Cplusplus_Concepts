#include<iostream>

int main()
{
    //Case1:
    // The problem here is first we are constructing the
    // string object and then reassigning it
    std::string s;
    s = "A stzring";
    // The following construct and initialize 
    // in one step is 32% more efficient
    const std::string s1 = "A string";


    //Case2:
    // Similarly
    // How can we make S2 const here
    const int i = std::rand();
    std::string S2;
    switch(i%4)
    {
        case 0:
            s = "string0";
            break;
        case 1:
            s = "string1";
            break;
        case 2:
            s = "string2";
            break;
        case 3:
            s = "string3";
            break;
    }
    // using lambda
    // 31% more efficient
    const std::string S2 = [&](){
    switch(i%4)
        {
        case 0:
            return "string0";
        case 1:
            return "string1";
        case 2:
            return "string2";
        case 3:
            return "string3";
        }
    }();

    
}