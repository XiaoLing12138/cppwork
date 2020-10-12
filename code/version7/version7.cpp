#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <atomic>

using namespace std;

float result1 = 0.0;
float result2 = 0.0;
float result3 = 0.0;
float result4 = 0.0;
float result5 = 0.0;
float result6 = 0.0;
float result7 = 0.0;
float result8 = 0.0;

int n;
float v1[100000000] = { 0 };
float v2[100000000] = { 0 };

int ThreadProc1();
int ThreadProc2();
int ThreadProc3();
int ThreadProc4();
int ThreadProc5();
int ThreadProc6();
int ThreadProc7();
int ThreadProc8();

int main()
{
	ifstream input("in100000000.dat", ios::in | ios::binary);
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

    thread t1(ThreadProc1);
    thread t2(ThreadProc2);
    thread t3(ThreadProc3);
    thread t4(ThreadProc4);
    thread t5(ThreadProc5);
    thread t6(ThreadProc6);
    thread t7(ThreadProc7);
    thread t8(ThreadProc8);

    t1.detach();
    t2.detach();
    t3.detach();
    t4.detach();
    t5.detach();
    t6.detach();
    t7.detach();
    t8.join();

	chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << result1+result2+result3+result4+result5+result6+result7+result8 << endl;

	cout << "Total took "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< "ms.\n";

	input.close();
	return 0;
}

int ThreadProc1()
{
    int i = 0;
    while (i < n / 8)
    {
        if (i + 8 < n / 8)
        {
            result1 = result1 + v1[i] * v2[i];
            result1 = result1 + v1[i + 1] * v2[i + 1];
            result1 = result1 + v1[i + 2] * v2[i + 2];
            result1 = result1 + v1[i + 3] * v2[i + 3];
            result1 = result1 + v1[i + 4] * v2[i + 4];
            result1 = result1 + v1[i + 5] * v2[i + 5];
            result1 = result1 + v1[i + 6] * v2[i + 6];
            result1 = result1 + v1[i + 7] * v2[i + 7];
            result1 = result1 + v1[i + 8] * v2[i + 8];
            i += 8;
        }
        else
        {
            result1 = result1 + v1[i] * v2[i];
            ++i;
        }
    }
    return 0;
}

int ThreadProc2()
{
    int i = n/8;
    while (i < n / 4)
    {
        if (i + 8 < n / 4)
        {
            result2 = result2 + v1[i] * v2[i];
            result2 = result2 + v1[i + 1] * v2[i + 1];
            result2 = result2 + v1[i + 2] * v2[i + 2];
            result2 = result2 + v1[i + 3] * v2[i + 3];
            result2 = result2 + v1[i + 4] * v2[i + 4];
            result2 = result2 + v1[i + 5] * v2[i + 5];
            result2 = result2 + v1[i + 6] * v2[i + 6];
            result2 = result2 + v1[i + 7] * v2[i + 7];
            result2 = result2 + v1[i + 8] * v2[i + 8];
            i += 8;
        }
        else
        {
            result2 = result2 + v1[i] * v2[i];
            ++i;
        }
    }
    return 0;
}

int ThreadProc3()
{
    int i = n / 4;
    while (i < n * 3 / 8)
    {
        if (i + 8 < n * 3 / 8)
        {
            result3 = result3 + v1[i] * v2[i];
            result3 = result3 + v1[i + 1] * v2[i + 1];
            result3 = result3 + v1[i + 2] * v2[i + 2];
            result3 = result3 + v1[i + 3] * v2[i + 3];
            result3 = result3 + v1[i + 4] * v2[i + 4];
            result3 = result3 + v1[i + 5] * v2[i + 5];
            result3 = result3 + v1[i + 6] * v2[i + 6];
            result3 = result3 + v1[i + 7] * v2[i + 7];
            result3 = result3 + v1[i + 8] * v2[i + 8];
            i += 8;
        }
        else
        {
            result3 = result3 + v1[i] * v2[i];
            ++i;
        }
    }
    return 0;
}

int ThreadProc4()
{
    int i = n * 3 / 8;
    while (i < n / 2)
    {
        if (i + 8 < n / 2)
        {
            result4 = result4 + v1[i] * v2[i];
            result4 = result4 + v1[i + 1] * v2[i + 1];
            result4 = result4 + v1[i + 2] * v2[i + 2];
            result4 = result4 + v1[i + 3] * v2[i + 3];
            result4 = result4 + v1[i + 4] * v2[i + 4];
            result4 = result4 + v1[i + 5] * v2[i + 5];
            result4 = result4 + v1[i + 6] * v2[i + 6];
            result4 = result4 + v1[i + 7] * v2[i + 7];
            result4 = result4 + v1[i + 8] * v2[i + 8];
            i += 8;
        }
        else
        {
            result4 = result4 + v1[i] * v2[i];
            ++i;
        }
    }
    return 0;
}

int ThreadProc5()
{
    int i = n / 2;
    while (i < n * 5 / 8)
    {
        if (i + 8 < n * 5 / 8)
        {
            result5 = result5 + v1[i] * v2[i];
            result5 = result5 + v1[i + 1] * v2[i + 1];
            result5 = result5 + v1[i + 2] * v2[i + 2];
            result5 = result5 + v1[i + 3] * v2[i + 3];
            result5 = result5 + v1[i + 4] * v2[i + 4];
            result5 = result5 + v1[i + 5] * v2[i + 5];
            result5 = result5 + v1[i + 6] * v2[i + 6];
            result5 = result5 + v1[i + 7] * v2[i + 7];
            result5 = result5 + v1[i + 8] * v2[i + 8];
            i += 8;
        }
        else
        {
            result5 = result5 + v1[i] * v2[i];
            ++i;
        }
    }
    return 0;
}

int ThreadProc6()
{
    int i = n * 5 / 8;
    while (i < n * 3 / 4)
    {
        if (i + 8 < n * 3 / 4)
        {
            result6 = result6 + v1[i] * v2[i];
            result6 = result6 + v1[i + 1] * v2[i + 1];
            result6 = result6 + v1[i + 2] * v2[i + 2];
            result6 = result6 + v1[i + 3] * v2[i + 3];
            result6 = result6 + v1[i + 4] * v2[i + 4];
            result6 = result6 + v1[i + 5] * v2[i + 5];
            result6 = result6 + v1[i + 6] * v2[i + 6];
            result6 = result6 + v1[i + 7] * v2[i + 7];
            result6 = result6 + v1[i + 8] * v2[i + 8];
            i += 8;
        }
        else
        {
            result6 = result6 + v1[i] * v2[i];
            ++i;
        }
    }
    return 0;
}

int ThreadProc7()
{
    int i = n * 3 / 4;
    while (i < n * 7 / 8)
    {
        if (i + 8 < n * 7 / 8)
        {
            result7 = result7 + v1[i] * v2[i];
            result7 = result7 + v1[i + 1] * v2[i + 1];
            result7 = result7 + v1[i + 2] * v2[i + 2];
            result7 = result7 + v1[i + 3] * v2[i + 3];
            result7 = result7 + v1[i + 4] * v2[i + 4];
            result7 = result7 + v1[i + 5] * v2[i + 5];
            result7 = result7 + v1[i + 6] * v2[i + 6];
            result7 = result7 + v1[i + 7] * v2[i + 7];
            result7 = result7 + v1[i + 8] * v2[i + 8];
            i += 8;
        }
        else
        {
            result7 = result7 + v1[i] * v2[i];
            ++i;
        }
    }
    return 0;
}

int ThreadProc8()
{
    int i = n * 7 / 8;
    while (i < n)
    {
        if (i + 8 < n)
        {
            result8 = result8 + v1[i] * v2[i];
            result8 = result8 + v1[i + 1] * v2[i + 1];
            result8 = result8 + v1[i + 2] * v2[i + 2];
            result8 = result8 + v1[i + 3] * v2[i + 3];
            result8 = result8 + v1[i + 4] * v2[i + 4];
            result8 = result8 + v1[i + 5] * v2[i + 5];
            result8 = result8 + v1[i + 6] * v2[i + 6];
            result8 = result8 + v1[i + 7] * v2[i + 7];
            result8 = result8 + v1[i + 8] * v2[i + 8];
            i += 8;
        }
        else
        {
            result8 = result8 + v1[i] * v2[i];
            ++i;
        }
    }
    return 0;
}