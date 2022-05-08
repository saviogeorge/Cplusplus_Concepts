#include <iostream>
#include <memory> // For std::unique_ptr, std::make_unique

using namespace std; 

// shared_ptr functions the same way as unique_ptr – holding a pointer, 
// providing the same basic interface for construction and using the 
// pointer, and ensuring that the pointer is deleted on destruction.
// Unlike unique_ptr, it also allows copying of the shared_ptr object to 
// another shared_ptr, and then ensures that the pointer is still 
// guaranteed to always be deleted once (but not before) all shared_ptrobjects 
// that were holding it are destroyed (or have released it).
// It does this using reference counting – it keeps a shared count of 
// how many shared_ptr objects are holding the same pointer. 
// This reference counting is done using atomic functions and is thus threadsafe.

struct A{
    int M;
    A(int m):M(m){}
};

int main()
{

    shared_ptr<A> sh_ptr(new A(5));
    // or also with 
    auto sh_ptr1 = make_shared<A>(10);

    // can share its object with another one
    // the managed object is not re-created or copied, 
    // it is pointed by another pointer.
    // We can share the object with as 
    // many shared pointers as we like
    shared_ptr<A> sh_ptr2 = sh_ptr1;

    // shared pointer can be empty
    // can set it later
    // i think its not possible with unique ptr.
    shared_ptr<A> sh_ptr3;
    sh_ptr3 = sh_ptr2;

    // A shared pointer supports usual pointer dereferencing
    (*sh_ptr2).M = 1;
    // Same as above
    sh_ptr2 -> M = 2;

    // shared pointer is, in fact, a class which has a raw pointer pointing to 
    // the managed object. This pointer is called stored pointer. We can access it.
    // Use the stored pointer for accessing and working 
    // with the managed object not for modifying its ownership.

    // A shared pointer, in addition to the stored pointer, 
    // has a second pointer which points to a control block. 
    // The control block has a reference counter that memorizes 
    // the number of shared pointers pointing to the same object.
    // Goto the link provided under references to view the diagramatic 
    // representation.


    // At any scope, we can check how many 
    // shared pointers point to a managed object
    cout<<sh_ptr2.use_count()<<endl;

    // If a shared pointer is destructed, 
    // the control unit decrements the reference counter
    // managed object will be deleted when 
    // the last shared pointer is deleted:

    auto sh_ptr5 = make_shared<A>(5);

    {
        shared_ptr<A> sh_ptr4 = sh_ptr5;
        cout<< sh_ptr5.use_count()<<endl; 
    }
    cout<< sh_ptr5.use_count()<<endl;


    // counter is decremented also if a pointer is detached
    auto sp1 = make_shared<A>(5);
    auto sp2 = sp1;
    auto sp3 = sp1;

    cout<< sp1.use_count()<<endl; // 3
    cout<< sp2.use_count()<<endl; // 3
    cout<< sp3.use_count()<<endl; // 3

    sp2.reset(); // sp2 is detached and empty.

    sp3 = make_shared<A>(4); // sp3 is reassigned another object.

    cout<< sp1.use_count()<<endl; // 1
    cout<< sp2.use_count()<<endl; // 0
    cout<< sp3.use_count()<<endl; // 1 from the new memory allocated not the old

    // shared pointers initialized from a naked pointer
    // The above piece of code is going to cause an error 
    // because two shared_ptrs from different 
    // groups share a single resource.
    // After the scope when the resources are deallocated 
    // for the sptr2 it will be try to deallocate which is already deallocated. 
    // and the program will crash.
    // To avoid this, better not create the shared pointers from a naked pointer.
    int* p = new int;
    {
        shared_ptr<int> sptr1(p);
        shared_ptr<int> sptr2(p);
        cout<< sptr1.use_count()<<endl; // 1
        cout<< sptr2.use_count()<<endl; // 1
    }

     return 0;
}

// References and notes:
// https://iamsorush.com/posts/shared-pointer-cpp/
// One place where the use of shared_ptr can really shine 
// (and the main case where you would need to use shared_ptr rather 
// than unique_ptr is in multi-threaded applications. 
// When you're not sure which thread will finish needing an object last, 
// you can simply give each thread a shared_ptr that references the object.
// However, note here that I said that you give each thread one such object. 
// The shared_ptr class is notthread-safe for the case that two threads try 
// to access the same shared_ptr object concurrently. Rather, thread-safety 
// is ensured as long as each thread has their own shared_ptr objects
//  (which may in turn all share+reference the same pointer).