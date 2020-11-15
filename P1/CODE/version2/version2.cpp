#include <iostream>
#include <cstdio>
#include <malloc.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "cblas.h"
#include "struct.h" 
using namespace std;

const int AOROW = 2000;
const int AOCOL = 50000;
const int BOROW = 50000;
const int BOCOL = 2000;

const int AROW = 200;
const int ACOL = 50000;
const int BROW = 50000;
const int BCOL = 200;

Matrix matrixMul(Matrix& a, Matrix& b);
void ThreadProc1(Matrix a, Matrix b, Matrix c);
void ThreadProc2(Matrix a, Matrix b, Matrix c);
void ThreadProc3(Matrix a, Matrix b, Matrix c);
void ThreadProc4(Matrix a, Matrix b, Matrix c);
void ThreadProc5(Matrix a, Matrix b, Matrix c);
void ThreadProc6(Matrix a, Matrix b, Matrix c);
void ThreadProc7(Matrix a, Matrix b, Matrix c);
void ThreadProc8(Matrix a, Matrix b, Matrix c);
void ThreadProc9(Matrix a, Matrix b, Matrix c);
void ThreadProc10(Matrix a, Matrix b, Matrix c);

int main()
{
	float* ao;
	float* bo;
	float* co;

	ao = (float*)malloc(sizeof(float) * AOROW * AOCOL);
	if (ao != 0)
	{
		memset(ao, 0, sizeof(float) * AOROW * AOCOL);
	}
	bo = (float*)malloc(sizeof(float) * BOROW * BOCOL);
	if (bo != 0)
	{
		memset(bo, 0, sizeof(float) * BOROW * BOCOL);
	}
	co = (float*)malloc(sizeof(float) * AOROW * BOCOL);
	if (co != 0)
	{
		memset(co, 0, sizeof(float) * AOROW * BOCOL);
	}

	ao[0] = 1.0;
	bo[0] = 1.0;
	ao[AOROW * AOCOL - 1] = 2.0;
	bo[BOROW * BOCOL - 1] = 2.0;

	chrono::steady_clock::time_point starto = chrono::steady_clock::now();

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, AOROW, BOCOL, AOCOL, 1, ao, AOCOL, bo, BOCOL, 0, co, BOCOL);

	chrono::steady_clock::time_point endo = chrono::steady_clock::now();

	printf("%0.2f %0.2f\n", co[0], co[AOROW * BOCOL - 1]);

	cout << "(2000*50000 and 50000*2000) OpenBlas takes "
		<< chrono::duration_cast<chrono::milliseconds>(endo - starto).count()
		<< "ms.\n";

	free(ao);
	free(bo);
	free(co);

	Matrix a, b, c;

	a.rows = AROW;
	a.cols = ACOL;
	b.rows = BROW;
	b.cols = BCOL;
	a.step = a.cols;
	b.step = b.cols;
	a.data = (float*)malloc(sizeof(float) * a.rows * a.cols);
	b.data = (float*)malloc(sizeof(float) * b.rows * b.cols);
	if (a.data != 0)
	{
		memset(a.data, 0, sizeof(float) * a.rows * a.cols);
	}
	if (b.data != 0)
	{
		memset(b.data, 0, sizeof(float) * b.rows * b.cols);
	}
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

	cout << "(200*50000 and 50000*200) Mine takes "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< "ms.\n";

	free(a.data);
	free(b.data);
	free(c.data);

	return 0;
}


Matrix matrixMul(Matrix& a, Matrix& b)
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
	if (c.data != 0)
	{
		memset(c.data, 0, sizeof(float) * c.rows * c.cols);
	}

	thread t1(ThreadProc1, a, b, c);
	thread t2(ThreadProc2, a, b, c);
	thread t3(ThreadProc3, a, b, c);
	thread t4(ThreadProc4, a, b, c);
	thread t5(ThreadProc5, a, b, c);
	thread t6(ThreadProc6, a, b, c);
	thread t7(ThreadProc7, a, b, c);
	thread t8(ThreadProc8, a, b, c);
	thread t9(ThreadProc9, a, b, c);
	thread t10(ThreadProc10, a, b, c);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();

	return c;
}

void ThreadProc1(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = 0; i < (c.rows * 0.1); i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}

void ThreadProc2(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = (c.rows * 0.1); i < (c.rows * 0.2); i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}

void ThreadProc3(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = (c.rows * 0.2); i < (c.rows * 0.3); i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}

void ThreadProc4(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = (c.rows * 0.3); i < (c.rows * 0.4); i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}

void ThreadProc5(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = (c.rows * 0.4); i < (c.rows * 0.5); i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}

void ThreadProc6(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = (c.rows * 0.5); i < (c.rows * 0.6); i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}

void ThreadProc7(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = (c.rows * 0.6); i < (c.rows * 0.7); i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}

void ThreadProc8(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = (c.rows * 0.7); i < (c.rows * 0.8); i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}

void ThreadProc9(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = (c.rows * 0.8); i < (c.rows * 0.9); i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}

void ThreadProc10(const Matrix a, const Matrix b, Matrix c)
{
	for (size_t i = (c.rows * 0.9); i < c.rows; i++)
	{
		for (size_t k = 0; k < c.cols; k++)
		{
			float temp = 0;
			size_t j = 0;
			while (j < a.cols)
			{
				if (j + 10 < a.cols)
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					temp += a.data[i * a.step + j + 1] * b.data[(j + 1) * b.step + k];
					temp += a.data[i * a.step + j + 2] * b.data[(j + 2) * b.step + k];
					temp += a.data[i * a.step + j + 3] * b.data[(j + 3) * b.step + k];
					temp += a.data[i * a.step + j + 4] * b.data[(j + 4) * b.step + k];
					temp += a.data[i * a.step + j + 5] * b.data[(j + 5) * b.step + k];
					temp += a.data[i * a.step + j + 6] * b.data[(j + 6) * b.step + k];
					temp += a.data[i * a.step + j + 7] * b.data[(j + 7) * b.step + k];
					temp += a.data[i * a.step + j + 8] * b.data[(j + 8) * b.step + k];
					temp += a.data[i * a.step + j + 9] * b.data[(j + 9) * b.step + k];
					j += 10;
				}
				else
				{
					temp += a.data[i * a.step + j] * b.data[j * b.step + k];
					j++;
				}
			}
			c.data[i * c.step + k] = temp;
		}
	}
}
