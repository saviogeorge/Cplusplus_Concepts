#include<iostream>
//https://www.youtube.com/watch?v=uzF4u9KgUWI
// The problem with below is
// we do not use the class initializer list
// which is more performant.
struct test
{
    test(std::string t_s)
    {
        m_s = t_s;
    }
    int val() const{
        return std::atoi(m_s.c_str());
    }

    std::string m_s;
};
// Better performant than above.
struct test1
{
    test1(std::string t_s):m_s(std::move(t_s))
    {}
    int val() const{
        return std::atoi(m_s.c_str());
    }

    std::string m_s;
};


int main()
{

}