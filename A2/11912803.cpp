/*
 * Wu Xiao 11912803
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

struct Stack
{
    int type;// 1 a 2 b 3c
    char c;
    long long a;
    double b;
    Stack()
    {
        type = 0;
        a = 0;
        b = 0;
    }
};

void expression();
void variable();
void additionB();
void subtractionB();
void multiplicationB();
void divisionB();
void factorialB();
void exponentB();
void matrixB();
void squareRoot();

bool checkNum(char c);
bool checkSym(char c, char s);// return priority c > s
int priorityCheck(char c);
long long factorial(long long s);
long long exponential(long long a, long long b);// a^b

int main()
{
    printf("Please Select Your Function:\n");
    printf("0 for expression only.\n");
    printf("1 for variable expression.\n");
    printf("2 for single expression with higher accuracy.\n");
    printf("So input your choice here:\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 0)
    {
        printf("\n\nWarning:\n");
        printf("If you wants to input a negetive number, please input as (-1)!\n");
        expression();
    }
    else if (choice == 1)
    {
        variable();
    }
    else
    {
        printf("\n\n");
        printf("\nPlease select a fuction:\n");
        printf("Input 1 for addition;\n");
        printf("Input 2 for subtraction;\n");
        printf("Input 3 for multiplication;\n");
        printf("Input 4 for division;\n");
        printf("Input 5 for factorial;\n");
        printf("Input 6 for exponent;\n");
        printf("Input 7 for matrix;\n");
        printf("Input 8 for squareRoot;\n");
        printf("\nPlease select a fuction:\n");
        int k = 0;
        scanf("%d", &k);
        switch (k)
        {
        case 1:additionB(); break;
        case 2:subtractionB(); break;
        case 3:multiplicationB(); break;
        case 4:divisionB(); break;
        case 5:factorialB(); break;
        case 6:exponentB(); break;
        case 7:matrixB(); break;
        case 8:squareRoot(); break;
        default:
            return 0;
        }
    }
    return 0;
}

void expression()
{
    Stack stackS1[201];
    Stack stackS2[201];
    string exp;
    printf("Input your expression here (without space):\n");
    cin >> exp;
    stackS2[0].c = '@';

    int s1 = 0, s2 = 0;
    while (exp.length() > 0)
    {
        if (exp.substr(0, 2) == "pi")// pi
        {
            stackS1[s1].b = 3.1415926535898;
            stackS1[s1].type = 2;
            exp.erase(0, 2);
            s1++;
        }
        else if (exp.substr(0, 1) == "e")// e
        {
            stackS1[s1].b = 2.718281828459;
            stackS1[s1].type = 2;
            exp.erase(0, 1);
            s1++;
        }
        else if (checkNum(exp[0]))// NUMBER
        {
            int i = 0;
            bool flag = false;
            while (checkNum(exp[i]))
            {
                double dBase = 0.1;
                if (exp[i] == '.')
                {
                    flag = true;
                }
                else if (!flag)
                {
                    stackS1[s1].a = stackS1[s1].a * 10 + (exp[i] - '0');
                }
                else
                {
                    stackS1[s1].b = stackS1[s1].b + double(exp[i] - '0') * dBase;
                    dBase *= 0.1;
                }

                if (flag)
                {
                    stackS1[s1].b += double(stackS1[s1].a);
                    stackS1[s1].a = 0;
                    stackS1[s1].type = 2;
                }
                else
                {
                    stackS1[s1].type = 1;
                }
                i++;
            }
            exp.erase(0, i);
            s1++;
        }
        else//SYMBOL + - * / ^ ( ) !
        {
            s2++;
            stackS2[s2].type = 3;
            if (exp[0] == '(')
            {
                stackS2[s2].c = exp[0];
                exp.erase(0, 1);
            }
            else if (exp[0] == ')')
            {
                while (stackS2[s2 - 1].c != '(')
                {
                    stackS1[s1] = stackS2[s2 - 1];
                    s1++;
                    stackS2[s2 - 1].c = stackS1[0].c;
                    s2--;
                }
                stackS2[s2 - 1].c = stackS1[0].c;
                s2--;
                exp.erase(0, 1);
            }
            else if ((s2 == 1) || (stackS2[s2 - 1].c == '('))
            {
                if ((exp[0] == '-') && (stackS2[s2 - 1].c == '('))
                {
                    int i = 1;
                    bool flag = false;
                    while (checkNum(exp[i]))
                    {
                        double dBase = 0.1;
                        if (exp[i] == '.')
                        {
                            flag = true;
                        }
                        else if (!flag)
                        {
                            stackS1[s1].a = stackS1[s1].a * 10 + (exp[i] - '0');
                        }
                        else
                        {
                            stackS1[s1].b = stackS1[s1].b + double(exp[i] - '0') * dBase;
                            dBase *= 0.1;
                        }

                        if (flag)
                        {
                            stackS1[s1].b += double(stackS1[s1].a);
                            stackS1[s1].a = 0;
                            stackS1[s1].type = 2;
                            stackS1[s1].b *= -1;
                        }
                        else
                        {
                            stackS1[s1].a *= -1;
                            stackS1[s1].type = 1;
                        }
                        i++;
                    }
                    exp.erase(0, i);
                    s1++;
                }
                else
                {
                    stackS2[s2].c = exp[0];
                    stackS2[s2].type = 3;
                    exp.erase(0, 1);
                }
            }
            else if (checkSym(exp[0], stackS2[s2 - 1].c)) // priority e > s
            {
                stackS2[s2].c = exp[0];
                exp.erase(0, 1);
            }
            else // priority e <= s
            {
                while (!checkSym(exp[0], stackS2[s2 - 1].c))
                {
                    stackS1[s1] = stackS2[s2 - 1];
                    s1++;
                    stackS2[s2 - 1].c = stackS1[0].c;
                    s2--;
                }
                stackS2[s2].c = exp[0];
                exp.erase(0, 1);
            }
        }
    }
    //s1 0 --- s1-1
    //s2 1 --- s2
    while (s2 > 0)
    {
        stackS1[s1] = stackS2[s2];
        s1++;
        stackS2[s2].c = stackS1[0].c;
        s2--;
    }

    // calculate
    stackS2[0].c = stackS1[0].c;
    s2 = 0;

    for (int i = 0; i < s1; i++)
    {
        if (stackS1[i].type != 3)
        {
            stackS2[s2] = stackS1[i];
            s2++;
        }
        else//SYMBOL + - * / ^ !
        {
            if (stackS1[i].c == '^')
            {
                stackS2[s2 - 2].a = exponential(stackS2[s2 - 2].a, stackS2[s2-1].a);
                stackS2[s2 - 1].a = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
            else if (stackS1[i].c == '!')
            {
                stackS2[s2-1].a = factorial(stackS2[s2-1].a);
            }
            else if (stackS1[i].c == '+')
            {
                if ((stackS2[s2 - 2].type == 1) && (stackS2[s2 - 1].type == 1))
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a + stackS2[s2 - 1].a;
                }
                else if ((stackS2[s2 - 2].type == 2) && (stackS2[s2 - 1].type == 2))
                {
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b + stackS2[s2 - 1].b;
                }
                else
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a + stackS2[s2 - 1].a;
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b + stackS2[s2 - 1].b;
                    stackS2[s2 - 2].b = double(stackS2[s2 - 2].a) + stackS2[s2 - 2].b;
                    stackS2[s2 - 2].a = 0;
                    stackS2[s2 - 2].type = 2;
                }
                stackS2[s2 - 1].a = 0;
                stackS2[s2 - 1].b = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
            else if (stackS1[i].c == '-')
            {
                if ((stackS2[s2 - 2].type == 1) && (stackS2[s2 - 1].type == 1))
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a - stackS2[s2 - 1].a;
                }
                else if ((stackS2[s2 - 2].type == 2) && (stackS2[s2 - 1].type == 2))
                {
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b - stackS2[s2 - 1].b;
                }
                else
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a - stackS2[s2 - 1].a;
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b - stackS2[s2 - 1].b;
                    stackS2[s2 - 2].b = double(stackS2[s2 - 2].a) + stackS2[s2 - 2].b;
                    stackS2[s2 - 2].a = 0;
                    stackS2[s2 - 2].type = 2;
                }
                stackS2[s2 - 1].a = 0;
                stackS2[s2 - 1].b = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
            else if (stackS1[i].c == '/')
            {
                if ((stackS2[s2 - 2].type == 1) && (stackS2[s2 - 1].type == 1))
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a / stackS2[s2 - 1].a;
                }
                else if ((stackS2[s2 - 2].type == 2) && (stackS2[s2 - 1].type == 2))
                {
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b / stackS2[s2 - 1].b;
                }
                else
                {
                    stackS2[s2 - 1].b = double(stackS2[s2 - 1].a) + stackS2[s2 - 1].b;
                    stackS2[s2 - 2].b = double(stackS2[s2 - 2].a) + stackS2[s2 - 2].b;
                    stackS2[s2 - 2].a = 0;
                    stackS2[s2 - 1].a = 0;
                    stackS2[s2 - 2].type = 2;
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b / stackS2[s2 - 1].b;
                }
                stackS2[s2 - 1].b = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
            else if (stackS1[i].c == '*')
            {
                if ((stackS2[s2 - 2].type == 1) && (stackS2[s2 - 1].type == 1))
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a * stackS2[s2 - 1].a;
                }
                else if ((stackS2[s2 - 2].type == 2) && (stackS2[s2 - 1].type == 2))
                {
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b * stackS2[s2 - 1].b;
                }
                else
                {
                    stackS2[s2 - 1].b = double(stackS2[s2 - 1].a) + stackS2[s2 - 1].b;
                    stackS2[s2 - 2].b = double(stackS2[s2 - 2].a) + stackS2[s2 - 2].b;
                    stackS2[s2 - 2].a = 0;
                    stackS2[s2 - 1].a = 0;
                    stackS2[s2 - 2].type = 2;
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b * stackS2[s2 - 1].b;
                }
                stackS2[s2 - 1].b = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
        }
    }

    if (stackS2[0].type == 1)
    {
        printf("\nAnswer = %lld\n", stackS2[0].a);
    }
    else
    {
        printf("\nAnswer = %0.3lf\n", stackS2[0].b);
    }
}

void variable()
{
    printf("\nWelcome to use variables fuction, you can choose at most three variables.\n");
    printf("Please tell us how much variables you would like to use:\n");
    int numbers = 0;
    scanf("%d", &numbers);
    if (numbers == 0)
    {
        printf("?????\n");
        return;
    }

    printf("x = ");
    double x = 0, y = 0, z = 0;
    scanf("%lf", &x);

    if (numbers > 1)
    {
        printf("y = ");
        scanf("%lf", &y);
    }
    if (numbers > 2)
    {
        printf("z = ");
        scanf("%lf", &z);
    }

    Stack stackS1[201];
    Stack stackS2[201];
    string exp;
    printf("Input your expression here (without space):\n");
    cin >> exp;
    stackS2[0].c = '@';

    int s1 = 0, s2 = 0;
    while (exp.length() > 0)
    {
        if (exp.substr(0, 1) == "x")// x
        {
            stackS1[s1].b = x;
            stackS1[s1].type = 2;
            exp.erase(0, 1);
            s1++;
        }
        else if (exp.substr(0, 1) == "y")// y
        {
            stackS1[s1].b = y;
            stackS1[s1].type = 2;
            exp.erase(0, 1);
            s1++;
        }
        else if (exp.substr(0, 1) == "z")// z
        {
            stackS1[s1].b = z;
            stackS1[s1].type = 2;
            exp.erase(0, 1);
            s1++;
        }
        else if (exp.substr(0, 2) == "pi")// pi
        {
            stackS1[s1].b = 3.1415926535898;
            stackS1[s1].type = 2;
            exp.erase(0, 2);
            s1++;
        }
        else if (exp.substr(0, 1) == "e")// e
        {
            stackS1[s1].b = 2.718281828459;
            stackS1[s1].type = 2;
            exp.erase(0, 1);
            s1++;
        }
        else if (checkNum(exp[0]))// NUMBER
        {
            int i = 0;
            bool flag = false;
            while (checkNum(exp[i]))
            {
                double dBase = 0.1;
                if (exp[i] == '.')
                {
                    flag = true;
                }
                else if (!flag)
                {
                    stackS1[s1].a = stackS1[s1].a * 10 + (exp[i] - '0');
                }
                else
                {
                    stackS1[s1].b = stackS1[s1].b + double(exp[i] - '0') * dBase;
                    dBase *= 0.1;
                }

                if (flag)
                {
                    stackS1[s1].b += double(stackS1[s1].a);
                    stackS1[s1].a = 0;
                    stackS1[s1].type = 2;
                }
                else
                {
                    stackS1[s1].type = 1;
                }
                i++;
            }
            exp.erase(0, i);
            s1++;
        }
        else//SYMBOL + - * / ^ ( ) !
        {
            s2++;
            stackS2[s2].type = 3;
            if (exp[0] == '(')
            {
                stackS2[s2].c = exp[0];
                exp.erase(0, 1);
            }
            else if (exp[0] == ')')
            {
                while (stackS2[s2 - 1].c != '(')
                {
                    stackS1[s1] = stackS2[s2 - 1];
                    s1++;
                    stackS2[s2 - 1].c = stackS1[0].c;
                    s2--;
                }
                stackS2[s2 - 1].c = stackS1[0].c;
                s2--;
                exp.erase(0, 1);
            }
            else if ((s2 == 1) || (stackS2[s2 - 1].c == '('))
            {
                if ((exp[0] == '-') && (stackS2[s2 - 1].c == '('))
                {
                    int i = 1;
                    bool flag = false;
                    while (checkNum(exp[i]))
                    {
                        double dBase = 0.1;
                        if (exp[i] == '.')
                        {
                            flag = true;
                        }
                        else if (!flag)
                        {
                            stackS1[s1].a = stackS1[s1].a * 10 + (exp[i] - '0');
                        }
                        else
                        {
                            stackS1[s1].b = stackS1[s1].b + double(exp[i] - '0') * dBase;
                            dBase *= 0.1;
                        }

                        if (flag)
                        {
                            stackS1[s1].b += double(stackS1[s1].a);
                            stackS1[s1].a = 0;
                            stackS1[s1].type = 2;
                            stackS1[s1].b *= -1;
                        }
                        else
                        {
                            stackS1[s1].a *= -1;
                            stackS1[s1].type = 1;
                        }
                        i++;
                    }
                    exp.erase(0, i);
                    s1++;
                }
                else
                {
                    stackS2[s2].c = exp[0];
                    stackS2[s2].type = 3;
                    exp.erase(0, 1);
                }
            }
            else if (checkSym(exp[0], stackS2[s2 - 1].c)) // priority e > s
            {
                stackS2[s2].c = exp[0];
                exp.erase(0, 1);
            }
            else // priority e <= s
            {
                while (!checkSym(exp[0], stackS2[s2 - 1].c))
                {
                    stackS1[s1] = stackS2[s2 - 1];
                    s1++;
                    stackS2[s2 - 1].c = stackS1[0].c;
                    s2--;
                }
                stackS2[s2].c = exp[0];
                exp.erase(0, 1);
            }
        }
    }
    //s1 0 --- s1-1
    //s2 1 --- s2
    while (s2 > 0)
    {
        stackS1[s1] = stackS2[s2];
        s1++;
        stackS2[s2].c = stackS1[0].c;
        s2--;
    }

    // calculate
    stackS2[0].c = stackS1[0].c;
    s2 = 0;

    for (int i = 0; i < s1; i++)
    {
        if (stackS1[i].type != 3)
        {
            stackS2[s2] = stackS1[i];
            s2++;
        }
        else//SYMBOL + - * / ^ !
        {
            if (stackS1[i].c == '^')
            {
                stackS2[s2 - 2].a = exponential(stackS2[s2 - 2].a, stackS2[s2 - 1].a);
                stackS2[s2 - 1].a = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
            else if (stackS1[i].c == '!')
            {
                stackS2[s2 - 1].a = factorial(stackS2[s2 - 1].a);
            }
            else if (stackS1[i].c == '+')
            {
                if ((stackS2[s2 - 2].type == 1) && (stackS2[s2 - 1].type == 1))
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a + stackS2[s2 - 1].a;
                }
                else if ((stackS2[s2 - 2].type == 2) && (stackS2[s2 - 1].type == 2))
                {
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b + stackS2[s2 - 1].b;
                }
                else
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a + stackS2[s2 - 1].a;
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b + stackS2[s2 - 1].b;
                    stackS2[s2 - 2].b = double(stackS2[s2 - 2].a) + stackS2[s2 - 2].b;
                    stackS2[s2 - 2].a = 0;
                }
                stackS2[s2 - 1].a = 0;
                stackS2[s2 - 1].b = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
            else if (stackS1[i].c == '-')
            {
                if ((stackS2[s2 - 2].type == 1) && (stackS2[s2 - 1].type == 1))
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a - stackS2[s2 - 1].a;
                }
                else if ((stackS2[s2 - 2].type == 2) && (stackS2[s2 - 1].type == 2))
                {
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b - stackS2[s2 - 1].b;
                }
                else
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a - stackS2[s2 - 1].a;
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b - stackS2[s2 - 1].b;
                    stackS2[s2 - 2].b = double(stackS2[s2 - 2].a) + stackS2[s2 - 2].b;
                    stackS2[s2 - 2].a = 0;
                }
                stackS2[s2 - 1].a = 0;
                stackS2[s2 - 1].b = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
            else if (stackS1[i].c == '/')
            {
                if ((stackS2[s2 - 2].type == 1) && (stackS2[s2 - 1].type == 1))
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a / stackS2[s2 - 1].a;
                }
                else if ((stackS2[s2 - 2].type == 2) && (stackS2[s2 - 1].type == 2))
                {
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b / stackS2[s2 - 1].b;
                }
                else
                {
                    stackS2[s2 - 1].b = double(stackS2[s2 - 1].a) + stackS2[s2 - 1].b;
                    stackS2[s2 - 2].b = double(stackS2[s2 - 2].a) + stackS2[s2 - 2].b;
                    stackS2[s2 - 2].a = 0;
                    stackS2[s2 - 1].a = 0;
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b / stackS2[s2 - 1].b;
                }
                stackS2[s2 - 1].b = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
            else if (stackS1[i].c == '*')
            {
                if ((stackS2[s2 - 2].type == 1) && (stackS2[s2 - 1].type == 1))
                {
                    stackS2[s2 - 2].a = stackS2[s2 - 2].a * stackS2[s2 - 1].a;
                }
                else if ((stackS2[s2 - 2].type == 2) && (stackS2[s2 - 1].type == 2))
                {
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b * stackS2[s2 - 1].b;
                }
                else
                {
                    stackS2[s2 - 1].b = double(stackS2[s2 - 1].a) + stackS2[s2 - 1].b;
                    stackS2[s2 - 2].b = double(stackS2[s2 - 2].a) + stackS2[s2 - 2].b;
                    stackS2[s2 - 2].a = 0;
                    stackS2[s2 - 1].a = 0;
                    stackS2[s2 - 2].b = stackS2[s2 - 2].b * stackS2[s2 - 1].b;
                }
                stackS2[s2 - 1].b = 0;
                stackS2[s2 - 1].type = 0;
                s2--;
            }
        }
    }

    if (stackS2[0].type == 1)
    {
        printf("\nAnswer = %lld\n", stackS2[0].a);
    }
    else
    {
        printf("\nAnswer = %0.3lf\n", stackS2[0].b);
    }
}

void additionB()
{
    int a[2001] = { 0 }, b[2001] = { 0 };
    string s1, s2;
    printf("\nPlease input two integer:\n");
    cin >> s1 >> s2;

    int m = 0, n = 0;
    while (s1.length() >= 4)
    {
        a[m] = (s1[s1.length() - 4] - '0') * 1000 + (s1[s1.length() - 3] - '0') * 100 + (s1[s1.length() - 2] - '0') * 10 + (s1[s1.length() - 1] - '0') * 1;
        s1.erase(s1.length() - 4, 4);
        m++;
    }
    if (s1.length() > 0)
    {
        for (int i = 0; i < s1.length(); i++)
        {
            a[m] = a[m] * 10 + (s1[i] - '0');
        }
    }
    if (a[m] == 0)
    {
        m--;
    }

    while (s2.length() >= 4)
    {
        b[n] = (s2[s2.length() - 4] - '0') * 1000 + (s2[s2.length() - 3] - '0') * 100 + (s2[s2.length() - 2] - '0') * 10 + (s2[s2.length() - 1] - '0') * 1;
        s2.erase(s2.length() - 4, 4);
        n++;
    }
    if (s2.length() > 0)
    {
        for (int i = 0; i < s2.length(); i++)
        {
            b[n] = b[n] * 10 + (s2[i] - '0');
        }
    }
    if (b[n] == 0)
    {
        n--;
    }

    int k = max(m, n);
    for (int i = 0; i <= k; i++)
    {
        a[i] += b[i];
        a[i + 1] += a[i] / 10000;
        a[i] = a[i] % 10000;
        while (a[k+1]!=0)
        {
            k++;
        }
    }

    printf("\nResult is:");
    for (int i = k; i >= 0; i--)
    {
        printf("%d", a[i]);
    }
    return;
}

void subtractionB()
{
    long double a, b;
    printf("\nPlease input two integer:\n");
    cin >> a >> b;
    if (a == b)
    {
        printf("\nResult is: 1\n");
        return;
    }

    printf("\nResult is: %lld", a / b);

    return;
}

void multiplicationB()
{
    int flag = 0;  // 0+   1-
    int a[1001] = { 0 }, b[1001] = { 0 }, c[2001] = { 0 };
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
    if (m > 1000)
    {
        printf("Too big to calculate! You need shift the code.\n");
        return;
    }

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
    while (c[m + 1] != 0)
    {
        m++;
    }

    printf("\nResult is:");
    if (flag == 1)
    {
        printf("-");
    }
    for (int i = m; i >= 0; i--)
    {
        printf("%d", c[i]);
    }
    return ;
}

void divisionB()
{
    long double a, b;
    printf("For division a/b, please input a & b:\n");
    cin >> a >> b;
    printf("\nResult is: %0.3llf\n", a / b);
}

void factorialB()
{
    int n = 0, m = 0;
    int a[1000] = { 0 };
    a[0] = 1;
    printf("Input your number:");
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            a[j] *= i;
        }
        for (int j = 0; j <= m; j++)
        {
            a[j + 1] += a[j] / 100000;
            a[j] = a[j] % 100000;
        }
        while (a[m + 1] != 0)
        {
            m++;
            a[m + 1] += a[m] / 100000;
            a[m] = a[m] % 100000;
        }
    }

    while (a[m + 1] != 0)
    {
        m++;
        a[m + 1] += a[m] / 100000;
        a[m] = a[m] % 100000;
    }
    printf("\nResult is:\n");
    for (int i = m; i >= 0; i--)
    {
        printf("%d", a[i]);
    }
    return ;
}

void exponentB()
{
    int base, b, m = 0, ans[1000] = { 0 };
    ans[0] = 1;
    printf("\nInput the base:\n");
    scanf("%d", &base);
    printf("Input the exponent:\n");
    scanf("%d", &b);

    while (b != 0)
    {
        if (b & 1)
        {
            for (int j = 0; j <= m; j++)
            {
                ans[j] *= base;
            }
            for (int j = 0; j <= m; j++)
            {
                ans[j + 1] += ans[j] / 1000000;
                ans[j] = ans[j] % 1000000;
            }
            while (ans[m + 1] != 0)
            {
                m++;
                ans[m + 1] += ans[m] / 1000000;
                ans[m] = ans[m] % 1000000;
            }
        }
        base *= base;
        b = b >> 1;
    }

    printf("\nResult is:\n");
    for (int i = m; i >= 0; i--)
    {
        printf("%d", ans[i]);
    }
    return;
}

void matrixB()
{
    int ma, na, mb, nb;
    printf("Please input your first matrix, m*n.\n");
    printf("Input ma (less than 40):");
    scanf("%d", &ma);
    printf("Input na (less than 40):");
    scanf("%d", &na);
    printf("Input mb (less than 40):");
    scanf("%d", &mb);
    printf("Input nb (less than 40):");
    scanf("%d", &nb);
    int matrixA[41][41] = { 0 }, matrixB[41][41] = { 0 };
    if (na != mb)
    {
        printf("Wrong Matrix!");
        return ;
    }
    printf("Input the matrixA:\n");
    for (int i = 1; i <= ma; i++)
    {
        for (int  j = 1; j <= na; j++)
        {
            scanf("%d", &matrixA[i][j]);
        }
    }

    printf("Input the matrixB:\n");
    for (int i = 1; i <= mb; i++)
    {
        for (int j = 1; j <= nb; j++)
        {
            scanf("%d", &matrixB[i][j]);
        }
    }

    printf("\nResult matrix is:\n");
    for (int i = 1; i <= ma; i++)
    {
        for (int j = 1; j <= nb; j++)
        {
            int temp = 0;
            for (int k = 1; k <= na; k++)
            {
                temp += matrixA[i][k] * matrixB[k][j];
            }
            printf("%d ", temp);
        }
        printf("\n");
    }
    return;
}

void squareRoot()
{
    printf("\nHere is squareRoot function, please input your number:\n");
    double n;
    scanf("%lf", &n);
    printf("\nResult is: %0.3lf\n", sqrt(n));
}

bool checkNum(char c)
{
    if (((c <= '9') && (c >= '0')) || (c == 'e') || (c == '.') || (c == 'x') || (c == 'y') || (c == 'z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkSym(char c, char s)
{
    int a = 0, b = 0;
    a = priorityCheck(c);
    b = priorityCheck(s);
    return a > b;
}

int priorityCheck(char c)
{
    switch (c)
    {
    case '(': return 4;
    case ')': return 4;
    case '!': return 3;
    case '^': return 3;
    case '*': return 2;
    case '/': return 2;
    case '+': return 1;
    case '-': return 1;
    case '@': return 0;
    default:  return 0;
    }
}

long long factorial(long long s)
{
    long long ans = 1;
    int n = 0;
    if (s == 0)
    {
        return 1;
    }
    else
    {
        for (long long i = 2; i <= s; i++)
        {
            ans *= i;
        }
    }
    return ans;
}

long long exponential(long long a, long long b)// n^m
{
    long long n = 0, m = 0, ans = 1;
    while (b != 0)
    {
        ans *= a;
        b--;
    }
    return ans;
}