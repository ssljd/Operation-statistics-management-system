#include<iostream>
#include<stack>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

stack<char> opt;     //������ջ
stack<double> val;   //������ջ

char opt_set[10] = "+-*/()=.";
/*�ж�����Ĳ������Ƿ�Ϸ�*/
bool in_set(char theChar) {
	for (int i = 0; i < 8; i++) {
		if (theChar == opt_set[i])
			return true;
	}
	return false;
}
/*Ϊÿһ������������һ�����������������ȼ�*/
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
const int IN = 0;    // ��������
const int OUT = 1;    // ��������
/*����׺���ʽת���ɺ�׺���ʽ*/
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
			state = IN; //״̬��Ϊ��������
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
			state = OUT; //״̬Ϊ��������
		}
	}
	while (!opt.empty()) {
		to += opt.top();
		to += ' ';
		opt.pop();
	}
	return true;
}
/*�����׺���ʽ*/
bool compute(string& theExp)
{
	int theInt = 0; //�ݴ�����
	int state = OUT;//��ʼ״̬Ϊ��������
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
				state = IN; //״̬Ϊ��������
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
				default:cout << "δ֪�Ĵ���!" << endl;
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