#include <iostream>
#include <memory> // for std::shared_ptr and std::weak_ptr
#include <string>

// std::weak_ptr was designed to solve the “cyclical ownership” 
// problem described above. A std::weak_ptr is an observer -- it 
// can observe and access the same object as 
// a std::shared_ptr (or other std::weak_ptrs) but it is not considered 
// an owner. Remember, when a std::shared pointer goes out of scope, 
// it only considers whether other std::shared_ptr are 
// co-owning the object. std::weak_ptr does not count!

class Person
{
	std::string m_name;
	std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

public:

	Person(const std::string &name): m_name(name)
	{
		std::cout << m_name << " created\n";
	}
    // Destructors for nonstatic member objects are called in the 
    // reverse order in which they appear in the class declaration. 
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

    // The downside of std::weak_ptr is that std::weak_ptr are not 
    // directly usable (they have no operator->). 
    // To use a std::weak_ptr, you must first convert it into a std::shared_ptr. 
    // Then you can use the std::shared_ptr. To convert a std::weak_ptr into a 
    // std::shared_ptr, you can use the lock() member function. Here’s the 
    // above example, updated to show this off:
    const std::shared_ptr<Person> getPartner() const 
    { 
        return m_partner.lock(); 
    } // use lock() to convert weak_ptr to shared_ptr
	const std::string& getName() const { return m_name; }
};

int main()
{
	auto lucy { std::make_shared<Person>("Lucy") };
    auto ricky { std::make_shared<Person>("Ricky") };
	

	partnerUp(lucy, ricky);

    auto partner = ricky->getPartner(); // get shared_ptr to Ricky's partner
	std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';

	return 0;
}

// Notes:
// Functionally, it works almost identically to the problematic 
// example. However, now when ricky goes out of scope, it sees 
// that there are no other std::shared_ptr pointing at “Ricky” 
// (the std::weak_ptr from “Lucy” doesn’t count). Therefore, 
// it will deallocate “Ricky”. The same occurs for lucy.