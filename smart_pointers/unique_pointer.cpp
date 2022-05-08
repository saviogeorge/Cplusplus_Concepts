#include <iostream>
#include <memory> // For std::unique_ptr, std::make_unique

using namespace std; 

// A unique pointer cannot be copied or passed by value. 
// However, the ownership of its object can be transferred



// class definitions
class example{

public:
  example(string n):Name(n){}
  ~example(){cout<<"Deleted!";}
  string Name;
};

void funcIn(std::unique_ptr<example> a)
{
    cout<< "Pointer received."<<'\n';

} // a and its object are deleted.

std::unique_ptr<example> funcOut()
{
    auto a =  make_unique<example>("savio");
    return a;
} 


int main(){

    // implementations
    std::unique_ptr<int> ptr(new int);
    *ptr = 10;
    cout<<*ptr<<endl;

    // A unique pointer can also be created 
    // with std::make_unique
    auto p = make_unique<example>("Jack");
    // The below operations are supported
    //dereference pointer
    auto b = *p;
    //Access class members
    p->Name = "Stafania";

    // There is a raw pointer inside a 
    // unique pointer that can be accessed
    // Use the above raw pointer only for 
    // calculations and do not delete it as
    // it is managed by a unique pointer
    auto raw_ptr = p.get();

    // The object allocated to the pointer 
    // can be changed but remember that it is 
    // automatically deleted:

    cout<<p.get()<<endl;
    p = make_unique<example>("Savio");
    cout<<p.get()<<endl;

    // The pointer can be reset to a null or new object
    // https://www.cplusplus.com/reference/memory/unique_ptr/reset/#:~:text=Reset%20pointer,no%20object%20after%20the%20call.
    p.reset();
    cout<<p.get()<<endl;

    // Only one unique pointer owns the object on the heap
    // therefore following is not allowed.
    // auto ptr_1 = make_unique<int>();
    // auto ptr_2 = ptr_1;

    // However, the ownership of the object can be transfered via std::move():
    auto ptr_1 = make_unique<int>(2);
    auto ptr_2 = move(ptr_1);

    // std::swap works with unique pointers
    // As it does not violates the properties
    // of unique pointers.
    swap(ptr_1, ptr_2);


    auto x = make_unique<example>("stafania");
    // Have to move it inorder pass it as an argument.
    funcIn(move(x));

    // https://www.cplusplus.com/reference/memory/unique_ptr/release/
    // Releases ownership of its stored pointer, 
    // by returning its value and replacing it with a null pointer.
    // This call does not destroy the managed object, 
    // but the unique_ptr object is released from the 
    // responsibility of deleting the object. Some other 
    // entity must take responsibility for deleting the 
    // object at some point.
    example * manual_ptr = x.release();
    delete manual_ptr;

    x = funcOut();
    if(x)
        cout<<x->Name<<endl;


    return 0;
}

// Additional Reference and notes:
// https://iamsorush.com/posts/unique-pointers-cpp/
// Who Owns the Pointer
// Let's take a simple example — I create a pointer and want to store it in a 
// container. As a new user of unique_ptr, I write some pretty straightforward code:

// std::unique_ptr<foo> q( new foo(42) );
// v.push_back( q );
// This seems reasonable, but doing this gets me into a gray area: 
// Who owns the pointer? Will the container destroy it at some point in its lifetime? 
// Or is it still my job do so?
// The rules of using unique_ptr prohibit this kind of code, 
// and trying to compile it will lead to the classic cascade of template-based 
// compiler errors (the ones that were going to be fixed with concepts, remember?), ending thus:

// unique.cpp(26) : see reference to class template instantiation
//  'std::vector<_Ty>' being compiled
// Anyway, the problem here is that we are only allowed to have one copy of the pointer — 
// unique ownership rules apply. If I want to give the object to another piece of code, 
// I have to invoke move semantics:

// v.push_back( std::move(q) );
// After I move the object into the container, my original unique_ptr, 
// q, has given up ownership of the pointer and it now rests with the 
// container. Although object q still exists, any attempt to dereference 
// it will generate a null pointer exception. In fact, after the move operation, 
// the internal pointer owned by q has been set to null.
// Move semantics will be used automatically any place you create an rvalue 
// reference. For example, returning a unique_ptr from a function doesn't 
// require any special code:

// return q;
// Nor does passing a newly constructed object to a calling function:

// process( std::unique_ptr<foo>( new foo(41) ) );
