#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "struct.h"

#include <iostream>
#include <cstdio>
#include <ctime>
#include <chrono>

const int threads_sum = 16;
const int BLOCK_SIZE = threads_sum;

__global__ void Kernel(float* devic_a, float* devic_b, float* devic_c,
						size_t n, size_t m)
{
	__shared__ float As[BLOCK_SIZE][BLOCK_SIZE];
	__shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];

	size_t bx = blockIdx.x;
	size_t by = blockIdx.y;

	size_t tx = threadIdx.x;
	size_t ty = threadIdx.y;

	size_t Row = by * BLOCK_SIZE + ty;
	size_t Col = bx * BLOCK_SIZE + tx;

	float cSum = 0.0f;

	for (size_t i = 0; i < n; i += BLOCK_SIZE)
	{

		As[ty][tx] = devic_a[Row * n + i + tx];
		Bs[ty][tx] = devic_b[(i + ty) * m + Col];

		__syncthreads();
		//Synchronization is required before the calculation, 
		//for each thread in the block has finished reading

		for (size_t k = 0; k < BLOCK_SIZE; k++)
		{
			cSum += As[ty][k] * Bs[k][tx];
		}

		__syncthreads();
		//Synchronize before going to the next calculation 
		//to avoid changing the values in the Shared memory
	}

	devic_c[m * Row + Col] = cSum;
}

void matrixMul(Matrix a, Matrix b, Matrix c, dim3 grid, dim3 block);

int main()
{
	Matrix a, b, c;

	a.rows = 2000;
	a.cols = 50000;
	b.rows = 50000;
	b.cols = 2000;
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

    dim3 grid(a.rows / threads_sum, b.cols / threads_sum);
    dim3 block(threads_sum, threads_sum);

	if (a.cols != b.rows)
	{
		printf("Your matrixes do not match!");
		return 0;
	}

	c.rows = 2000;
	c.cols = 2000;
	c.step = 2000;
	c.data = (float*)malloc(sizeof(float) * a.rows * b.cols);

	matrixMul(a, b, c, grid, block);

	free(a.data);
	free(b.data);
	free(c.data);

	return 0;
}

void matrixMul(Matrix a, Matrix b, Matrix c, dim3 grid, dim3 block)
{
	float* devic_a;
	float* devic_b;
	float* devic_c;

	chrono::steady_clock::time_point startR = chrono::steady_clock::now();

	cudaMalloc((void**)&devic_a, a.rows * a.cols * sizeof(float));
	cudaMalloc((void**)&devic_b, b.rows * b.cols * sizeof(float));
	cudaMalloc((void**)&devic_c, c.rows * c.cols * sizeof(float));

	cudaMemcpy(devic_a, a.data, a.rows * a.cols * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(devic_b, b.data, b.rows * b.cols * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(devic_c, c.data, c.rows * c.cols * sizeof(float), cudaMemcpyHostToDevice);

	chrono::steady_clock::time_point start = chrono::steady_clock::now();

	Kernel << <grid, block >> > (devic_a, devic_b, devic_c, a.cols, b.cols);

	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	cudaMemcpy(c.data, devic_c, c.rows * c.cols * sizeof(float), cudaMemcpyDeviceToHost);

	chrono::steady_clock::time_point endR = chrono::steady_clock::now();

	printf("%0.2f %0.2f\n", c.data[0], c.data[c.rows * c.cols - 1]);

	cout << "CUDA takes "
		<< chrono::duration_cast<chrono::microseconds>(end - start).count()
		<< "us to count.\n";

	cout << "CUDA takes "
		<< chrono::duration_cast<chrono::seconds>(endR - startR).count()
		<< "s to write memory.\n";

	cudaFree(devic_a);
	cudaFree(devic_b);
	cudaFree(devic_c);
}