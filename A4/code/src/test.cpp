#include <iostream>
#include <cstdio>
#include <algorithm>
#include "Matrix.h"

using namespace std;

int main()
{
	Matrix a;
	cout << "Matrix a():\n" << a;
	
	float* bM = (float*)malloc(2 * 2 * sizeof(float));
	bM[0] = 1; bM[1] = 1; bM[2] = 1; bM[3] = 1;
	
	Matrix b(2, 2, bM);
	cout << "Matrix b(2, 2, bM):\n" << b << endl;
	
	Matrix c(b);
	cout << "Matrix c(b):\n" << c << endl;
	cout << "c.rows:\n" << c.getRows() << endl;
	cout << "c.cols:\n" << c.getCols() << endl;
	cout << "c.size:\n" << c.getSize() << endl;
	cout << "c.copy:\n" << c.getCopy() << endl;
	if (c == b)
	{
		printf("Mat c == Mat b\n");
	}
	else
	{
		printf("Mat c != Mat b\n");
	}

	Matrix d = b;
	cout << "Matrix d = b:\n" << d << endl;
	cout << "Matrix d[1][0]:\n" << d.getPlace(1, 0) << endl;

	Matrix e = b + c;
	cout << "Matrix e = b + c:\n" << e << endl;
	e.setPlace(1, 1, 9);
	cout << "Change e[1][1] to 9:\n" << e << endl;

	Matrix f = 1 + c;
	cout << "Matrix f = 1 + c:\n" << f << endl;

	Matrix g = b + 1;
	cout << "Matrix g = b + 1:\n" << g << endl;

	Matrix h = b - c;
	cout << "Matrix h = b - c:\n" << h << endl;

	Matrix i = b - 1;
	cout << "Matrix i = b - 1:\n" << i << endl;

	Matrix j = 1 - b;
	cout << "Matrix j = 1 - b:\n" << j << endl;
	
	Matrix k = b * c;
	cout << "Matrix k = b * c:\n" << k << endl;

	Matrix l = b * 5;
	cout << "Matrix l = b * 5:\n" << l << endl;

	Matrix m = 5 * b;
	cout << "Matrix m = 5 * b:\n" << m << endl;
	m.transposition();
	cout << "Matrix m transposition:\n" << m << endl;

	Matrix n(2, 2);
	cout << "Matrix &n:\n" << &n << endl << endl;

	Matrix o = a * b;

	return 0;
}