/*
version 1:
Simply realize the function---Input two vectors with n elements and count for the result
Using two loop with O(n) time complexity
Without error solution
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
      
int n;
float result = 0;

int main()
{
	printf("Please input how many elements your vector has: ");
	scanf("%d", &n);
	float* v1 = new float[n];

	printf("Please input your vector1: ");
	for (int i = 0; i < n; i++)
	{
		scanf("%f", &v1[i]);
	}
	printf("Please input your vector2: ");
	for (int i = 0; i < n; i++)
	{
		float temp;
		scanf("%f", &temp);
		result += v1[i] * temp;
	}

	printf("The result is: %f", result);
	
	return 0;
}
