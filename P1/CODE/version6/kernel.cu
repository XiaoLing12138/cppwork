#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "struct.h"
#include "cublas_v2.h"

#include <iostream>
#include <cstdio>

const int AROW = 2000;
const int ACOL = 50000;
const int BROW = 50000;
const int BCOL = 2000;

void matrixMul(Matrix a, Matrix b, Matrix c);

int main()
{
	Matrix a, b, c;

	ios::sync_with_stdio(false);

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
	a.data[0] = 1.0f;
	b.data[0] = 1.0f;
	a.data[a.rows * a.cols - 1] = 2.0f;
	b.data[b.rows * b.cols - 1] = 2.0f;

	if (a.cols != b.rows)
	{
		printf("Your matrixes do not match!");
		return 0;
	}

	c.rows = AROW;
	c.cols = BCOL;
	c.step = c.cols;
	c.data = (float*)malloc(sizeof(float) * c.rows * c.cols);
	if (c.data != 0)
	{
		memset(c.data, 0, sizeof(float) * c.rows * c.cols);
	}

	matrixMul(a, b, c);

	free(a.data);
	free(b.data);
	free(c.data);
	return 0;
}

void matrixMul(Matrix a, Matrix b, Matrix c)
{
	float* cuda_a;
	float* cuda_b;
	float* cuda_c;

	cudaEvent_t start, stop;
	float running_time;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaMalloc((void**)&cuda_a, a.rows * a.cols * sizeof(float));
	cudaMalloc((void**)&cuda_b, b.rows * b.cols * sizeof(float));
	cudaMalloc((void**)&cuda_c, c.rows * c.cols * sizeof(float));

	cublasHandle_t handle;

	cublasCreate(&handle);
	
	cublasSetMatrix(AROW, ACOL, sizeof(*a.data), a.data, AROW, cuda_a, AROW);
	cublasSetMatrix(BROW, BCOL, sizeof(*b.data), b.data, BROW, cuda_b, BROW);
	cublasSetMatrix(AROW, BCOL, sizeof(*c.data), c.data, AROW, cuda_c, BCOL);
	
	float alpha = 1, beta = 0;

	cudaEventRecord(start, 0);

	cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N,
		AROW, BCOL, ACOL, &alpha, cuda_a,
		AROW, cuda_b, BROW, &beta, cuda_c, BCOL);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&running_time, start, stop);

	cout << "cuBLAS time: " << running_time << "ms" << endl;

	cublasGetMatrix(AROW, BCOL, sizeof(*c.data), cuda_c, AROW, c.data, BCOL);

	printf("%0.2f %0.2f\n", c.data[0], c.data[c.rows * c.cols - 1]);

	cudaFree(cuda_a);
	cudaFree(cuda_b);
	cudaFree(cuda_c);
}
