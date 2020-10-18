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

using namespace std;

int n;

__global__ void vec_dot(float* a, float* b, double* result)
{
    result[0] += a[threadIdx.x] * b[threadIdx.x];
}

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

    float* v1, * v2;
    double *result;
    cudaMallocManaged(&result, sizeof(double));
    cudaMallocManaged(&v1, n * sizeof(float));
    cudaMallocManaged(&v2, n * sizeof(float));

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

    if (n >= 1000)
    {
        int i = 0;
        while (i <= n)
        {
            vec_dot << <i + 1, i + 1000 >> > (v1, v2, result);
            i += 1000;
        }
    }
    else
    {
        vec_dot << <1, n >> > (v1, v2, result);
    }
    cudaDeviceSynchronize();

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    printf("Cuda: %lf\n", result[0]);

    cout << "Self took "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms.\n";

    cudaFree(v1);
    cudaFree(v2);
    cudaFree(result);
    input.close();
    return 0;
}