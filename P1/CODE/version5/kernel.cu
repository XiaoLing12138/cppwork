#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "struct.h"

#include <iostream>
#include <cstdio>

const int threads_sum = 16;
const int BLOCK_SIZE = threads_sum;
const int ROW = 2000;
const int COL = 50000;

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

	float cSum = 0.0;

	for (size_t i = 0; i < n; i += BLOCK_SIZE)
	{

		As[ty][tx] = devic_a[Row * n + i + tx];
		Bs[ty][tx] = devic_b[(i + ty) * m + Col];

		__syncthreads();
		//Synchronization is required before the calculation
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

	ios::sync_with_stdio(false);

	a.rows = ROW;
	a.cols = COL;
	b.rows = COL;
	b.cols = ROW;
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

	c.rows = ROW;
	c.cols = ROW;
	c.step = c.cols;
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

	cudaEvent_t start, stop;
	float running_time;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaMalloc((void**)&devic_a, a.rows * a.cols * sizeof(float));
	cudaMalloc((void**)&devic_b, b.rows * b.cols * sizeof(float));
	cudaMalloc((void**)&devic_c, c.rows * c.cols * sizeof(float));

	cudaEventRecord(start, 0);

	cudaMemcpy(devic_a, a.data, a.rows * a.cols * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(devic_b, b.data, b.rows * b.cols * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(devic_c, c.data, c.rows * c.cols * sizeof(float), cudaMemcpyHostToDevice);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&running_time, start, stop);

	cout << "Writing memcpy time:" << running_time << "ms" << endl;

	cudaEventRecord(start, 0);

	Kernel << <grid, block >> > (devic_a, devic_b, devic_c, a.cols, b.cols);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&running_time, start, stop);
	cout << "Calculating time2:" << running_time << "ms" << endl;

	cudaEventRecord(start, 0);

	cudaMemcpy(c.data, devic_c, c.rows * c.cols * sizeof(float), cudaMemcpyDeviceToHost);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&running_time, start, stop);
	cout << "Writing back time:" << running_time << "ms" << endl;

	printf("%0.2f %0.2f\n", c.data[0], c.data[c.rows * c.cols - 1]);

	cudaFree(devic_a);
	cudaFree(devic_b);
	cudaFree(devic_c);
}
