#include<iostream>
#include<stack>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

stack<char> opt;     //操作符栈
stack<double> val;   //操作数栈

char opt_set[10] = "+-*/()=.";
/*判断输入的操作符是否合法*/
bool in_set(char theChar) {
	for (int i = 0; i < 8; i++) {
		if (theChar == opt_set[i])
			return true;
	}
	return false;
}
/*为每一个操作符返回一个数，数代表了优先级*/
int level(char theOpt)
{
	switch (theOpt) {
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case ')':
		return 3;
	}
}
const int IN = 0;    // 在数字中
const int OUT = 1;    // 在数字外
/*将中缀表达式转换成后缀表达式*/
bool change(string& from, string& to)
{
	int theInt = 0;
	int state = OUT;
	char c;

	for (int i = 0; i < from.length(); i++)
	{
		c = from[i];
		if (isdigit(c)) {
			to = to + c;
			theInt *= 10;
			theInt += c - '0';
			state = IN; //状态改为在数字内
		}
		else {
			if (state == IN && c == '.') {
				to = to + '.';
				theInt = 0;
				continue;
			}
			if (state == IN && c != '.') {
				to += ' ';
				theInt = 0;
			}
			if (c == '=')
				break;
			else if (c == '(')
				opt.push(c);
			else if (c == ')') {
				while (!opt.empty() && opt.top() != '(') {
					to += opt.top();
					to += ' ';
					opt.pop();
				}
				opt.pop();
			}
			else {
				while (true) {
					if (opt.empty() || opt.top() == '(')
						opt.push(c);
					else if (level(c) > level(opt.top()))
						opt.push(c);
					else {
						to += opt.top();
						to += ' ';
						opt.pop();
						continue;
					}
					break;
				}
			}
			state = OUT; //状态为在数字外
		}
	}
	while (!opt.empty()) {
		to += opt.top();
		to += ' ';
		opt.pop();
	}
	return true;
}
/*计算后缀表达式*/
bool compute(string& theExp)
{
	int theInt = 0; //暂存数字
	int state = OUT;//初始状态为在数字外
	char c;
	bool dot = false;
	double count = 1.0;
	for (int i = 0; i < theExp.length(); i++)
	{
		c = theExp[i];
		if (isdigit(c) || c == '.') {
			if (isdigit(c)) {
				theInt *= 10;
				theInt += c - '0';
				state = IN; //状态为在数字内
				if (dot == true)
					count *= 10.0;
			}
			if (c == '.') {
				dot = true;
				continue;
			}
		}
		else {
			dot = false;
			double ans = theInt / count;
			count = 1.0;
			if (state == IN) {
				val.push(ans);
				theInt = 0;
			}
			double x, y;
			if (c != ' ') {
				x = val.top(); val.pop();
				y = val.top(); val.pop();

				switch (c) {
				case '+':val.push(x + y); break;
				case '-':val.push(y - x); break;
				case '*':val.push(x * y); break;
				case '/':val.push(y / x); break;
				default:cout << "未知的错误!" << endl;
				}
			}
			state = OUT;
		}
	}
	return true;
}

int main()
{
	fstream f;
	f.open("A1.txt", ios::in);
	string s;
	while (f >> s);
	string t = 0;
	f.close();
	return 0;
	change(s, t);
	compute(t);
	fstream x;
	x.open("A1_out.txt", ios::out);
	for (int i = 0; i < s.length(); i++)
		x << s[i];
	x << "=" << val.top();
	x.close();

}