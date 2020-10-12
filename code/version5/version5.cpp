#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

int n;
float result = 0;

//bool checkInput(string s);
//bool checkInputN(string s);
//float transform(string s);
//int transformN(string s);
//int findString(string s, string a);


int main()
{
	ifstream input("in200000000.dat", ios::in | ios::binary);
	if (!input)
	{
		cout << "Error opening input file." << endl;
		return 0;
	}

	ofstream output("out200000000.dat", ios::out | ios::binary);
	if (!output)
	{
		input.close();
		cout << "Error opening output file." << endl;
		return 0;
	}

	chrono::steady_clock::time_point start = chrono::steady_clock::now();

/*	string s;
	while (!(input >> s))
	{
		printf("You haven't input anything, please input how many elements your vector has: ");
	}

	if (!checkInputN(s))
	{
		printf("Your input n is wrong, we set it as 0!\n");
		n = 0;
	}
	else
	{
		n = transformN(s);
	}
*/

	if (!(input.read((char*)&n, sizeof(int))))
	{
		printf("You haven't input n, so we set n as 0!");
		n = 0;
	}

	chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
	cout << "First part took "
		<< chrono::duration_cast<chrono::seconds>(end1 - start).count()
		<< "s.\n";

	float* v = new float[n];

/*	for (int i = 0; i < n; i++)
	{
		input >> s;
		if (!checkInput(s))
		{
			printf("Your input v1[%d] is wrong, we set it as 0!\n", i + 1);
			v1[i] = 0;
		}
		else
		{
			v1[i] = transform(s);
		}
	}
*/

	for (int i = 0; i < n; i++)
	{
		if (!(input.read((char*)&v[i], sizeof(float))))
		{
			printf("You haven't input the v1[%d], so we set it as 0!", i);
			v[i] = 0;
		}
	}

	chrono::steady_clock::time_point end2 = chrono::steady_clock::now();
	cout << "Second part took "
		<< chrono::duration_cast<chrono::seconds>(end2 - start).count()
		<< "s.\n";

	for (int i = 0; i < n; i++)
	{
		float temp;
		if (!(input.read((char*)&temp, sizeof(float))))
		{
			printf("You haven't input the v2[%d], so we set it as 0!", i);
			temp = 0;
		}
		result += v[i] * temp;
	}

	chrono::steady_clock::time_point end3 = chrono::steady_clock::now();
	cout << "Third part took "
		<< chrono::duration_cast<chrono::seconds>(end3 - start).count()
		<< "s.\n";

	output.write((char*)&result, sizeof(float));

	input.close();
	output.close();

	chrono::steady_clock::time_point end4 = chrono::steady_clock::now();
	cout << "Total took "
		<< chrono::duration_cast<chrono::seconds>(end4 - start).count()
		<< "s.\n";

	return 0;
}

// Check for N
/*
bool checkInputN(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (('0' <= s[i]) && (s[i] <= '9'))
		{
			continue;
		}
		return false;
	}
	return true;
}
*/

//Special input e = 2.71828
//This function will check the inputs are legal or not
/*
bool checkInput(string s)
{
	if ((s == "e") || (s == "-e"))
	{
		return true;
	}

	int point = findString(s, ".");
	if (point == -1)
	{
		return false;
	}

	string s1 = s.substr(0, point);
	string s2 = s.substr(point + 1, s.length() - point - 1);

	if (s1[0] == '-')
	{
		s1.erase(0, 1);
	}

	if (s1.empty() || s2.empty())
	{
		return false;
	}

	for (int i = 0; i < s1.length(); i++)
	{
		if (('0' <= s1[i]) && (s1[i] <= '9'))
		{
			continue;
		}
		return false;
	}

	for (int i = 0; i < s2.length(); i++)
	{
		if (('0' <= s2[i]) && (s2[i] <= '9'))
		{
			continue;
		}
		return false;
	}

	return true;
}
*/

//Special input e = 2.71828
//Transform a string to a float
/*float transform(string s)
{
	float result = 0;
	float flag = 1;
	if (s[0] == '-')
	{
		flag = -1;
		s.erase(0, 1);
	}

	if (s[0] == 'e')
	{
		return float(2.71828);
	}

	while ((s[0] == '0') && (s.length() != 1))
	{
		s.erase(0, 1);
	}

	while ((s[s.length()-1] == '0') && (s.length() != 1))
	{
		s.erase(s.length()-1, 1);
	}

	unsigned int i = 0;
	int length = s.length();
	while ((s[i] != '.') && (i < s.length()))
	{
		result = result * 10 + s[i] - '0';
		i++;
	}

	i++;
	float temp = 1;
	while (i < s.length())
	{
		temp *= float(0.1);
		result += (s[i] - '0') * temp;
		i++;
	}

	return result * flag;
}
*/
/*
//Transform for n
int transformN(string s)
{
	int result = 0;

	while (s.length() != 0)
	{
		result = result * 10 + (s[0] - '0');
		s.erase(0, 1);
	}

	return result;
}
*/

//Will use KMP
/*
int findString(string s, string a)
{
	for (int i = 0; i <= s.length() - a.length(); i++)
	{
		if (s[i] == a[0])
		{
			int flag = 1;
			for (int j = 1; j < a.length(); j++)
			{
				if (s[i + j] != a[j])
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				return i;
			}
		}
	}
	return -1;
}
*/