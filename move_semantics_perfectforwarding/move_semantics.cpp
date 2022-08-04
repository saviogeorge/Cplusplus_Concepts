#include<iostream>


// A naive class that handles a dynamic chunk of memory.
// When we choose to manage memory ourselves the Rule of Three
// applies:https://en.wikipedia.org/wiki/Rule_of_three_%28C++_programming%29
// states that if your class defines one or more of the following methods it 
// should probably explicitly define all three
// 1.destructor;
// 2.copy constructor;
// 3.copy assignment operator.
// A C++ compiler will generate them by default if needed
// Unfortunately the default versions are just "not enough" 
// when your class deals with dynamic resources
class example
{
  public:

    // Constructor
    example(int size)         
    {
      m_data = new unsigned int[size];
      m_size = size;
    }

    //Copy constructor declaration
    example(const example& other);
    // Assignment operator declaration
    example& operator=(const example& other);
    // Move constructor declaration
    example(example&& other);
    // Move Assignment operator declaration
    example& operator=(example&& other);
    // Destructor
    ~example()                
    {
      delete[] m_data;
    }

  private:

    unsigned int*   m_data;
    size_t m_size;
};

//const reference argument since
// it needs to left untouched
example::example(const example& other)
{
    m_data = new unsigned int[other.m_size];  
    std::copy(other.m_data, other.m_data + other.m_size, m_data);  
    m_size = other.m_size;
}

//const reference argument since
// it needs to left untouched
example& example::operator=(const example& other) 
{
  //Check for self assignment
  if(this == &other) return *this;
  // Check if the pointer 
  // is not empty and 
  // Delete old memory
  if (m_data != 0) 
    delete[] m_data;
  // Allocate new memory
  m_data = new unsigned int[other.m_size];
  // Copy the data
  std::copy(other.m_data, other.m_data + other.m_size, m_data);
  m_size = other.m_size;
  // A reference is returned.
  // to avoid an unnecessary copy operation
  return *this;  
}

example create_example(unsigned int size)
{
  return example(size);
}

// Move constructor
// No deep copies here, we have just moved resources around! 
// It's important to set the rvalue reference data to some valid state 
// to prevent it from being accidentally deleted when the temporary object dies
example::example(example&& other)
{
  // steal the data
  m_data = other.m_data;   
  m_size = other.m_size;
  // setting it to null
  other.m_data = nullptr; 
  other.m_size = 0;
}

// We steal data from the other object coming in as an 
// rvalue reference, after a cleanup of the existing resources. 
// Let's not forget to put the temporary object to some valid state
// as we did in the move constructor. Everything else is 
// just regular assignment operator duty.
example& example::operator=(example&& other)    
{  
  if (this == &other) 
    return *this;

  delete[] m_data;         

  m_data = other.m_data;   
  m_size = other.m_size;

  other.m_data = nullptr;  
  other.m_size = 0;

  return *this;
}

int main()
{
    //Calls the regular constructor
    example obj_1(10);
    // Calls the copy constructor
    example obj_2(obj_1);
    // Also calls the copy constructor
    example obj3 = obj_1;

    example obj4(100);
    example obj5(50);

    //Calls assignment operator
    obj4 = obj5;


  // The above implementation of the class is fine 
  // However we will encounter some optimization 
  // issues

  // Consider case with function create_example
  // it returns object by value.
  // returning such things by value with our 
  // current class design would trigger multiple 
  // expensive memory allocations,
  // We know that when a function returns an object by value, 
  // the compiler has to create a temporary 
  // — yet fully-fledged — object (rvalue)

  //  for instance 
  //  temporary object coming out from create_example() is 
  //  passed to the copy constructor. According to our 
  //  current design, the copy constructor allocates its 
  //  own m_data pointer by copying the data from the 
  //  temporary object. Two expensive memory allocations: 
  //  a) during the creation of the temporary, 
  //  b) during the actual object copy-construct operation.
  //  The will also happen with assignment operator
  // example obj6 = create_example(5000);// Copy const
  // obj6 = create_example(5000);// Assg opr

  // This is where the move semantics with rvalue references
  // will help us optimize.

  // At this point we naturally follow another C++ pattern 
  // called the Rule of Five. It's an extension to the Rule of 
  // Three seen before and it states that any class for which 
  // move semantics are desirable, has to declare two additional member functions:

  // a)the move constructor — to construct new objects by stealing data from temporaries;
  // b)the move assignment operator — to replace existing objects 
  //   by stealing data from temporaries.

  // Lets try out the move const and the assg
  example obj6 = create_example(5000);// Copy const
  obj6 = create_example(5000);// Assg opr

  // Theoretically it should call the copy coonst
  // but in practice it may not due to 
  example obj6 = create_example(5000);// Copy const
  // Return value optimizations
  // https://www.fluentcpp.com/2016/11/28/return-value-optimizations/
  // Note: You can tell the compiler to bypass such optimization: for example, 
  // GCC supports the -fno-elide-constructors flag

  // Now we may think since we have RVO why would we need to implement move semantics
  // RVO is only about return values (output), not function parameters (input). 
  // There are many places where you may pass movable objects as input parameters, 
  // which would make the move constructor and the move assignment operator come 
  // into play, if implemented. The most important one: the Standard Library. 
  // During the upgrade to C++11 all the algorithms and containers in there were 
  // extended to support move semantics. So if you use the Standard Library with 
  // classes that follow the Rule of Five you will gain an important optimization boost.


}


// References:
// https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners
