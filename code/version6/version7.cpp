#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <malloc.h>
#include <stdlib.h>
#define min(a,b) (a<b ? a:b)
#define sum_squares(x) (x*(x+1)*(2*x+1)/6)
const int N = 200000000;
const int threadsPerBlock = 256;
const int blockPerGrid = min(32, (N + threadsPerBlock - 1) / threadsPerBlock);


using namespace std;

int n;

__global__ void vec_dot(float* a, float* b, float* c)
{
    __shared__ float cache[threadsPerBlock];
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int cacheIndex = threadIdx.x;

    float temp = 0;
    while (tid < N)
    {
        temp += a[tid] * b[tid];
        tid += blockDim.x * gridDim.x;
    }

    cache[cacheIndex] = temp;

    __syncthreads();

    //对于归约运算来说，以下代码要求threadPerBLock必须为2的指数
    int i = blockDim.x / 2;
    while (i != 0)
    {
        if (cacheIndex < i)
            cache[cacheIndex] += cache[cacheIndex + i];
        __syncthreads();
        i /= 2;
    }

    if (cacheIndex == 0)
    {
        c[blockIdx.x] = cache[0];
    }
}

int main()
{
    float* a, * b, c, * partial_c;
    float* dev_a, * dev_b, * dev_partial_c;


    a = (float*)malloc(N * sizeof(float));
    b = (float*)malloc(N * sizeof(float));
    partial_c = (float*)malloc(blockPerGrid * sizeof(float));


    cudaMalloc((void**)&dev_a, N * sizeof(float));
    cudaMalloc((void**)&dev_b, N * sizeof(float));
    cudaMalloc((void**)&dev_partial_c, blockPerGrid * sizeof(float));

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
        if (!(input.read((char*)&a[i], sizeof(float))))
        {
            printf("Your input for v1[%d] is somehow wrong, so we set it as 0!", i);
            a[i] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (!(input.read((char*)&b[i], sizeof(float))))
        {
            printf("Your input for v2[%d] is somehow wrong, so we set it as 0!", i);
            b[i] = 0;
        }
    }

    cudaMemcpy(dev_a, a, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, N * sizeof(float), cudaMemcpyHostToDevice);

    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    vec_dot << <blockPerGrid, threadsPerBlock >> > (dev_a, dev_b, dev_partial_c);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Self took "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << "us.\n";

    cudaMemcpy(partial_c, dev_partial_c, blockPerGrid * sizeof(float), cudaMemcpyDeviceToHost);

    c = 0;
    for (int i = 0; i < blockPerGrid; i++)
    {
        c += partial_c[i];
    }

    printf("c = %f\n", c);


    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_partial_c);


    free(a);
    free(b);
    free(partial_c);
    input.close();
    return 0;
}
