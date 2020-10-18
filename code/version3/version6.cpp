#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

int n;
float result = 0;
float v1[200000000];
float v2[200000000];

int main()
{
	ifstream input("in200000000.dat", ios::in | ios::binary);
	if (!input)
	{
		cout << "Error opening input file." << endl;
		return 0;
	}

	if (!(input.read((char*)&n, sizeof(int))))
	{
		printf("You haven't input n, so we set n as 0!");
		n = 0;
	}

	for (int i = 0; i < n; i++)
	{
		if (!(input.read((char*)&v1[i], sizeof(float))))
		{
			printf("Your input for v1[%d] is somehow wrong, so we set it as 0!", i);
			v1[i] = 0;
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (!(input.read((char*)&v2[i], sizeof(float))))
		{
			printf("Your input for v2[%d] is somehow wrong, so we set it as 0!", i);
			v2[i] = 0;
		}
	}

	chrono::steady_clock::time_point start = chrono::steady_clock::now();

	for (int i = 0; i < n; i++)
	{
		result += v1[i] * v2[i];
	}

	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	printf("The result: %f\n", result);

	cout << "Total took "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< "ms.\n";

	input.close();
	return 0;
}
