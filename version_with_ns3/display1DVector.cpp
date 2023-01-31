#include <iostream>
#include <string>
#include <vector>

using namespace std;

void display1DVector(std::vector<int> a)
{
	for (size_t i = 0; i < a.size(); ++i)
		cout << a[i] << " ";
	cout << endl;
}