#include<iostream>
//https://www.youtube.com/watch?v=uzF4u9KgUWI


struct Base
{
    virtual ~Base()=default;
    virtual void do_a_thing() = 0;

};

struct Derived: Base
{
    // One of The problem here is we do not 
    // virtual destructor in the derived class 
    // because the inherited destructor is going 
    // to virtual.
    // https://stackoverflow.com/questions/2198379/are-virtual-destructors-inherited

    // The second problem here is by providing a virtual destructor
    // the move construction and the move assignnment will be implicitly
    // disabled by the compiler.
    // BY providing the destructor we have told our compiler that we are 
    // doing something special with the life time of the object and therefore
    // it will not create move assignment and move construction for us
    virtual ~Derived()=default;
    virtual void do_a_thing() override{};
};

// so the following is better
// 10% improvement 

struct Base
{
    virtual ~Base()=default;
    Base() = default;
    Base(const Base&) = default;
    Base& operator=(const Base&) = default;
    Base(Base &&) = default;
    Base& operator=(Base &&) =default;
    virtual void do_a_thing() = 0;
};

struct Derived
{
    // the destructor is also removed from here
    // if not we are making the same problem as described above.
    virtual void do_a_thing() = 0;
}



