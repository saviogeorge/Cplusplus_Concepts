// What is enum used for:
// The enum data type is used to create a type of data that 
// can only store a fixed set of values. For 
// instance, an enumeration that stores seasons would 
// only store spring, summer, autumn, and winter. 
// Enums are useful when a variable should only be capable 
// of storing one value that exists in a specific set of values.


#include <iostream>
#include <climits>

using namespace std;




int main() 
{
//  A short reminder. Three drawbacks of enumerations:
//  1)The enumerators implicitly convert to int.
//  2)They introduce the enumerators in the enclosing scope.
//  3)The type of enumeration can not be specified.
  enum prices {
	Raspberry = 2,
  Strawberry = 2,
  Powdered = 1,
  Chocolate = 1,
  Cinnamon = 2
};

	enum prices orderFlavor;
	orderFlavor = Raspberry;
	cout << "Donut ordered: 1x " << orderFlavor<<endl;
  // int Raspberry= 5;  // redeclaration ERROR



// The strongly-typed enumerations have to follow stronger rules:

// 1) The enumerators can only be accessed in the scope of the enumeration.
// 2) The enumerators don't implicitly convert to int.
// 3) The enumerators aren't imported in the enclosing scope.
// 4) The type of the enumerators is by default int. Therefore, 
//    you can forward the enumeration.

enum struct NewEnum{
  one= 1,
  ten=10,
  hundred=100,
  thousand= 1000
};

std::cout << "C++11= " << 2*static_cast<int>(NewEnum::thousand) + 
                            0*static_cast<int>(NewEnum::hundred) + 
                            1*static_cast<int>(NewEnum::ten) + 
	                          1*static_cast<int>(NewEnum::one) << std::endl;

// You can explicitly specify the type of enumerators. By default, it's int.

// But that does not have to be. You can use integral types like bool, 
// char, short int, long int, or, long long int

enum struct Colour0: bool{
  red,     // 0
  blue     // 1
};

enum Colour1{
  red= -5,   
  blue,      // -4
  green      // -3
};

enum struct Colour2: char{
  red= 100,
  blue, // 101
  green // 102
};

enum class Colour3: long long int{
  //red= 	std::numeric_limits<long long int>::min();
  red= LLONG_MIN,
  blue,    // std::numeric_limits<long long int>::min() + 1
  green    // std::numeric_limits<long long int>::min() + 2
};
}