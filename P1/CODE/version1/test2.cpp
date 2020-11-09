#include <iostream>
#include <cstdio>
#include <malloc.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "struct.h" 
using namespace std;

Matrix a, b;

Matrix matrixMul(Matrix a, Matrix b);

int main()
{
	Matrix c;

	a.rows = 2000;
	a.cols = 50000;
	b.rows = 50000;
	b.cols = 2000;
	a.step = a.cols;
	b.step = b.cols;
	a.data = (float*)malloc(sizeof(float) * a.rows * a.cols);
	b.data = (float*)malloc(sizeof(float) * b.rows * b.cols);
	a.data[0] = (float)1.0;
	b.data[0] = (float)1.0;
	a.data[a.rows * a.cols - 1] = (float)2.0;
	b.data[b.rows * b.cols - 1] = (float)2.0;

	chrono::steady_clock::time_point start = chrono::steady_clock::now();

	c = matrixMul(a, b);

	if (c.cols == -1)
	{
		return 0;
	}

	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	printf("%0.2f %0.2f\n", c.data[0], c.data[c.cols * c.rows - 1]);

	cout << "It took "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< "ms.\n";

	free(a.data);
	free(b.data);
	free(c.data);
	return 0;
}

Matrix matrixMul(Matrix a, Matrix b)
{
	Matrix c;
	c.cols = -1;

	if (a.cols != b.rows)
	{
		printf("Your matrixes do not match!");
		return c;
	}
	
	c.rows = a.rows;
	c.cols = b.cols;
	c.step = c.cols;
	c.data = (float*)malloc(sizeof(float) * c.rows * c.cols);

	for (size_t i = 0; i < c.rows; i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			for (size_t j = 0; j < a.cols; j++)
			{
				temp += a.data[i * a.step + j] * b.data[j * b.step + k];
			}
			c.data[i * c.step + k] = temp;
			printf("%d %d\n", i, k);
		}
	}

	return c;
}

