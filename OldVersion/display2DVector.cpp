#include <iostream>
#include <string>
#include <vector>

using namespace std;

void display2DVector(std::vector<std::vector<int>> a)
{
	for (size_t i = 0; i < a.size(); ++i)
	{
		for (size_t j = 0; j < a[0].size(); ++j)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}