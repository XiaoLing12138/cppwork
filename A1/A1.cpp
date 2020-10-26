#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

bool checkInput(string s, int n);

int a[100001] = { 0 };
int b[100001] = { 0 };
int c[200005] = { 0 };

int main()
{
    int flag = 0;  // 0+   1-
    string s1, s2;
    printf("Please input two integers\n");
    cin >> s1 >> s2;

    if (s1[0] == '-')
    {
        flag = flag ^ 1;
        s1.erase(0, 1);
    }
    else if (s1[0] == '+')
    {
        s1.erase(0, 1);
    }
    if (s2[0] == '-')
    {
        flag = flag ^ 1;
        s2.erase(0, 1);
    }
    else if (s2[0] == '+')
    {
        s2.erase(0, 1);
    }

    int m = s1.length() + s2.length() - 2;
    if (m > 200000)
    {
        printf("Too big to calculate! You need shift the code.\n");
        return 0;
    }

    if (checkInput(s1, 1) && checkInput(s2, 2))
    {
        for (int i = 0; i < s1.length(); i++)
        {
            a[i] = s1[s1.length() - 1 - i] - '0';
        }
        for (int i = 0; i < s2.length(); i++)
        {
            b[i] = s2[s2.length() - 1 - i] - '0';
        }

        for (int i = 0; i < s1.length(); i++)
        {
            for (int j = 0; j < s2.length(); j++)
            {
                c[i + j] += a[i] * b[j];
                c[i + j + 1] += c[i + j] / 10;
                c[i + j] = c[i + j] % 10;
            }
        }
        for (int i = 0; i <= m; i++)
        {
            c[i + 1] += c[i] / 10;
            c[i] = c[i] % 10;
        }
        while (c[m+1] != 0)
        {
            m++;
        }
        if (flag == 1)
        {
            printf("-");
        }
        for (int i = m; i >= 0; i--)
        {
            printf("%d", c[i]);
        }
    }
    return 0;
}

bool checkInput(string s, int n)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (('0' <= s[i])&&(s[i] <= '9'))
        {
            continue;
        }
        else
        {
            printf("The s%d isn't a integer, please check it.\n", n);
            return false;
        }
    }
    return true;
}

