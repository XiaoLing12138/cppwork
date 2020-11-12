#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "struct.h"

#include <iostream>
#include <cstdio>
#include <ctime>
#include <chrono>

const int threads_sum = 16;

__global__ void Kernel(float* devic_a, float* devic_b, float* devic_c,
						size_t n, size_t m)
{
	size_t x = size_t(blockIdx.x) * blockDim.x + threadIdx.x;
	size_t y = size_t(blockIdx.y) * blockDim.y + threadIdx.y;
	size_t offset = x * blockDim.x * gridDim.x + y;

	float ans = 0;
	for (size_t i = 0; i < n; i++)
	{
		ans += devic_a[x * n + i] * devic_b[i * m + y];
	}
	devic_c[offset] = ans;
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

	printf("%0.2f %0.2f\n", c.data[0], c.data[c.rows * c.cols - 1]);

	cout << "CUDA takes "
		<< chrono::duration_cast<chrono::microseconds>(end - start).count()
		<< "us.\n";

	cudaFree(devic_a);
	cudaFree(devic_b);
	cudaFree(devic_c);
}