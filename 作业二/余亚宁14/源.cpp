#include<iostream>
#include<fstream>
#include<stack>
#include<iomanip>
using namespace std;

int getPriority(char c)
{
	if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return 0;
}
double calculate(double n1, double n2, char c)
{
	if (c == '+')
		return n1 + n2;
	else if (c == '-')
		return n1 - n2;
	else if (c == '*')
		return n1 * n2;
	else
		return n1 / n2;
}

int main()
{
	stack<double>num;
	stack<char>symbol;
	fstream infile;
	fstream outfile;
	infile.open("A1.txt");
	outfile.open("A1_out.txt");
	string s;
	double n=0;
	double n1, n2;
	bool t = false;
	while (infile >> s)
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] >= '0' && s[i] <= '9')
			{
				n = n * 10 + (s[i] - '0');
				t = true;
			}
			else
			{
				if (t)
				{
					num.push(n);
					n = 0;
					t = false;
				}
				if (!symbol.empty())
				{
					if (s[i] == '(')
						symbol.push(s[i]);
					else if (s[i] == ')')
					{
						while (symbol.top() != '(')
						{
							n1 = num.top();
							num.pop();
							n2 = num.top();
							num.pop();
							num.push(calculate(n2, n1, symbol.top()));
							symbol.pop();
						}
						symbol.pop();
					}
					else if (getPriority(symbol.top()) >= getPriority(s[i]))//优先级高或者一样的在栈内，栈内先计算
					{
						n1 = num.top();
						num.pop();
						n2 = num.top();
						num.pop();
						num.push(calculate(n2, n1, symbol.top()));
						symbol.pop();
						symbol.push(s[i]);
					}
					else if (getPriority(symbol.top()) < getPriority(s[i]))//优先级高的还没进栈，进栈
					{
						symbol.push(s[i]);
					}
				}
				else
					symbol.push(s[i]);
			}
		}
		if (n != 0)
			num.push(n);
		while (num.size() > 1 && !symbol.empty())
		{
			n1 = num.top();
			num.pop();
			n2 = num.top();
			num.pop();
			num.push(calculate(n2, n1, symbol.top()));
			symbol.pop();
		}
		outfile << s << "=" <<fixed<<setprecision(4)<< num.top() << endl;
		cout << s << "= " << fixed << setprecision(4) << num.top() << endl;
	}
	infile.close();
	outfile.close();
}