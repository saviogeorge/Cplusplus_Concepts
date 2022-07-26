#include <iostream>
#include <memory> // for std::shared_ptr
#include <string>

class Person
{
	std::string m_name;
	std::shared_ptr<Person> m_partner; // initially created empty

public:

	Person(const std::string &name): m_name(name)
	{
		std::cout << m_name << " created\n";
	}
	~Person()
	{
		std::cout << m_name << " destroyed\n";
	}

	friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
	{
		if (!p1 || !p2)
			return false;

		p1->m_partner = p2;
		p2->m_partner = p1;

		std::cout << p1->m_name << " is now partnered with " << p2->m_name << "\n";

		return true;
	}
};

class Resource
{
public:
	std::shared_ptr<Resource> m_ptr; // initially created empty

	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
	auto lucy { std::make_shared<Person>("Lucy") }; // create a Person named "Lucy"
	auto ricky { std::make_shared<Person>("Ricky") }; // create a Person named "Ricky"

	partnerUp(lucy, ricky); // Make "Lucy" point to "Ricky" and vice-versa


    // It turns out, this cyclical reference issue can even happen 
    // with a single std::shared_ptr -- a std::shared_ptr referencing 
    // the object that contains it is still a cycle (just a reductive one)
    auto ptr1 { std::make_shared<Resource>() };

	ptr1->m_ptr = ptr1; // m_ptr is now sharing the Resource that contains it

	return 0;

}

// Notes:
// At the end of main(), the ricky shared pointer goes out 
// of scope first. When that happens, ricky checks if 
// there are any other shared pointers that co-own the Person 
// “Ricky”. There are (Lucy’s m_partner). Because of this, it
//  doesn’t deallocate “Ricky” (if it did, then Lucy’s 
//  m_partner would end up as a dangling pointer). 
//  At this point, we now have one shared pointer to 
//  “Ricky” (Lucy’s m_partner) and two shared pointers to 
//  “Lucy” (lucy, and Ricky’s m_partner).

// Next the lucy shared pointer goes out of scope, and the 
// same thing happens. The shared pointer lucy checks if 
// there are any other shared pointers co-owning the Person 
// “Lucy”. There are (Ricky’s m_partner), so “Lucy” isn’t 
// deallocated. At this point, there is one shared pointer 
// to “Lucy” (Ricky’s m_partner) and one shared pointer to
//  “Ricky” (Lucy’s m_partner).

// Then the program ends -- and neither Person “Lucy” or 
// “Ricky” have been deallocated! Essentially, “Lucy” ends 
// up keeping “Ricky” from being destroyed, and “Ricky” ends 
// up keeping “Lucy” from being destroyed.

// It turns out that this can happen any time shared pointers 
// form a circular reference