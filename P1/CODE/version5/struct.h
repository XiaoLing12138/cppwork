#include <iostream>
#include <cstdio>

using namespace std;

struct Matrix {
	size_t rows;
	size_t cols;
	float* data;
	size_t step;
};
