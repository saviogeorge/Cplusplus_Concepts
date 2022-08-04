//A simple thumb rule- whenever you can use a function pointer
//you can use a lambda.

#include<iostream>
#include<vector>
#include<functional>
#include <algorithm>    // std::find_if

using namespace std;

void foreach(const vector<int>& values, void(*func)(int))
{
	for (auto value : values)
		func(value);
}

void foreach_1(const vector<int>& values, const function<void(int)>& func)
{
	for (auto value : values)
		func(value);
}
int main()
{

	vector<int> values = { 1,2,3,4,5 };
	// another option is to replace the function with lambdas
	// basiocally does the same thing
	auto lambda = [](int value) {cout << "Value:" << value << endl; };
	foreach(values, lambda);

	//now in case where the lambda function has to print something outside
	//like the following
	// we can pass the value as reference or value
	// = indicates all values
	int a = 5;
	auto lambda_1 = [&a](int value) {cout << "Value:" << a << endl; };
	foreach_1(values, lambda_1);


	// one practical use of lambdas
	// returns an iterator 
	auto it = find_if(values.begin(), values.end(), [](int value) {return value > 3; });
	cout << *it;

	// also look into the notes for 
	// recursive function using lambdas
}

//Notes:
//https://www.youtube.com/watch?v=mWgmBBz0y8c&t=184s
// https://www.codeproject.com/Articles/570638/Ten-Cplusplus11-Features-Every-Cplusplus-Developer