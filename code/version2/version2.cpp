#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;
      
int n;
float result = 0;

bool checkInput(string s);
bool checkInputN(string s);
float transform(string s);
int findString(string s, string a);


int main()
{
	printf("Please input how many elements your vector has: ");
	string s;
	while (!(cin >> s))
	{
		printf("You haven't input anything, please input how many elements your vector has: ");
	}

	if (!checkInputN(s))
	{
		printf("Your input is wrong, please check it and restart!\n");
		return 0;
	}

	n = transform(s);

	float* v1 = new float[n];

	printf("Please input your vector1: ");
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		if (!checkInput(s))
		{
			printf("Your input is wrong, please check it and restart!\n");
			return 0;
		}
		v1[i] = transform(s);
	}

	printf("Please input your vector2: ");
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		if (!checkInput(s))
		{
			printf("Your input is wrong, please check it and restart!\n");
			return 0;
		}
		result += v1[i] * transform(s);
	}

	printf("The result is: %f", result);
	
	return 0;
}

// Check for N
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

//Special input e = 2.71828
//This function will check the inputs are legal or not 
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

//Special input e = 2.71828
//Transform a string to a float
float transform(string s)
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


//Will use KMP

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