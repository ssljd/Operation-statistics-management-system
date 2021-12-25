#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

#define MaxSize 20
int ErrorExp = 0; //A global variable to store the wrong expressions;
int TotalExp = 0; //A global variable to calculate total expressions;

template <typename T>
class Stack //Define a class named Stack;
{
public:
	Stack()
	{
		Top = -1; //Initialize stack ;
	}

	int GetTop() //A get founction return the Top of a Stack;
	{
		return Top;
	}

	int IsEmpty() //A founction judge whether the stack is empty;
	{
		return Top == -1;
	}

	int Push(T X) //Push a number into stack;
	{
		if (Top + 1 == MaxSize)
			return -1;
		Data[++Top] = X;
		return 0;
	}

	T Pop() //Pop a number out of stack;
	{
		if (Top == -1)
			return 0;
		return Data[Top--];
	}

	T Peek() 
	{
		if (Top == -1)
			return "ERROR";
		return Data[Top];
	}
private:
	int Top; //a variable to make the top of stack;
	T Data[MaxSize]; //An array to store datas;
};

//A founction to do calculate one step of the expession;
void J(Stack<double> &OperandStack, Stack<string> &OperatorStack)
{
	if (OperandStack.GetTop() <= 0 || OperatorStack.IsEmpty()) 
		//Judge whether there still is a operator and two operands;
		ErrorExp++; //If not,wrong expressions plus one;
	string op = OperatorStack.Pop(); //A variable to store a operator;
	double a = OperandStack.Pop(); //A variable to store one operand;
	double b = OperandStack.Pop(); //A variable to store another operand;
	if (op == "+")
		OperandStack.Push(a + b);
	else if (op == "-")
		OperandStack.Push(b - a);
	else if (op == "*")
		OperandStack.Push(a * b);
	else if (op == "/")
	{
		if (a == 0) 
			ErrorExp++; //If the denominator is zero ,wrong expressions plus one;
		OperandStack.Push(b / a);
	}
}

void Calculate(string *Expression, Stack<string> &OperatorStack, Stack<double> &OperandStack, int n)
{
	for (int i = 0; i < n; i++) //Scan the whole expression;
	{
		if (Expression[i] == "+" || Expression[i] == "-")
		{
			//Process all + - * / in the top of the Operrator satck;
			while (!OperatorStack.IsEmpty() && OperatorStack.Peek() == "+" || OperatorStack.Peek() == "-" 
				|| OperatorStack.Peek() == "*" || OperatorStack.Peek() == "/")	
				J(OperandStack, OperatorStack);
			OperatorStack.Push(Expression[i]); //Push the + or - operator into the Operator stack;
		}
		else if (Expression[i] == "*" || Expression[i] == "/")
		{
			Process all * / in the top of the Operrator satck;
			while (!OperatorStack.IsEmpty() && OperatorStack.Peek() == "*" || OperatorStack.Peek() == "/")
				J(OperandStack, OperatorStack);
			OperatorStack.Push(Expression[i]); //Push the * or / operator into the Operator stack;
		}
		else if (Expression[i] == "(")
		{
			OperatorStack.Push(Expression[i]); //Push ( to Operator stack;
		}
		else if (Expression[i] == ")")
		{
			while (OperatorStack.Peek() != "(") //Process all the operators int the stack until seeing ( ;
				J(OperandStack, OperatorStack);
			OperatorStack.Pop(); //Pop the ( symbol from the stack;
		}
		else
			OperandStack.Push(atof(Expression[i].c_str())); //Push an operand to the stack as integer;
	}
	while (!OperatorStack.IsEmpty()) //Process all the remaining operators int the stack;
	{
		J(OperandStack, OperatorStack);
	}
}

//Write the expressions and their results into a file;
void WriteIntoFile(string *Expression, double Num,int n)
{
	ofstream file("D:\\b_out.txt",ios::app);
	for (int i = 0; i < n; i++)
	{
		file << Expression[i];
		file << " ";
	}
	file << " = " << setprecision(6) << Num << endl; //keep four number bebind the opint;
	file.close();
}

//Write a statistics file;
void WriteRecord(double time)
{
	ofstream file2("D:\\b_log.txt");
	file2 << "执行运算时间：" << time << endl;
	file2 << "总的表达式数量：" << TotalExp << endl;
	file2 << "正确表达式数量：" << TotalExp - ErrorExp << endl;
	file2 << "错误表达式数量：" << ErrorExp << endl;
	file2.close();
}
int main()
{
	Stack<double> OperandStack; //Creat a stack to store operand with type of double;
	Stack<string> OperatorStack; //Creat a stack to store operator with type of string;
	OperatorStack.IsEmpty(); //Initialize the OperatorStack;
	OperandStack.IsEmpty(); //Initialize teh OperandStack;

	string Expression[MaxSize]; //A string variable record expressions;
	ifstream file("D:\\b.txt"); //Open a file;
	clock_t start = clock(); //Recored the start time;
	while (!file.eof())
	{
		int i = 0;
		string s;
		while (file >> s && s != "=") //Read data into expression;
			Expression[i++] = s;
		Calculate(Expression, OperatorStack, OperandStack, i);
		double Num = OperandStack.Pop(); //A variable to store the result of the expression;
		WriteIntoFile(Expression, Num, i); //write the expression and it's result into the file;
		TotalExp++; //The number of expressions plus one;
	}
	file.close(); //Close the file;
	clock_t finish = clock(); //Record the final time;
	double time = (double)(finish - start) / CLOCKS_PER_SEC; //Calculate the opration time;
	WriteRecord(time); //Write the data into the statistics file;
}

