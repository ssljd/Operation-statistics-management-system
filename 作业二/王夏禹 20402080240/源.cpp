#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#define MaxSize 20
#define INIFITY 1000
using namespace std;

//创造函数
template <typename T>
class Stack {
public:
	void InitStack() {   //初始化栈
		Top = -1;
	}
	int IsEmpty() {     //判断是否为空
		return Top == -1;
	}
	int Push(T X) {   //入栈
		if (Top + 1 == MaxSize) 
			return -1;
		Data[++Top] = X;
		return 0;
	}
	T Pop() { //出栈
		return Data[Top--];
	}
	T Peek() { //返回栈顶元素
		return Data[Top];
	}
	int GetTop() //返回栈顶元素的值;
	{
		return Top;
	}
	T ReturnData(int Top)  
	{
		return Data[Top];
	}
private:
	int Top;  
	T Data[MaxSize];
};
int TotalExp = 0; //用于存储文件中表达式数的变量;
int ErrorExp = 0; //一个变量来存储错误表达式的数量;

struct Node {
	double Operand;
	char Operator;
};

struct TreeNode {
	double Operand;
	char Operator;
	struct TreeNode *Lchild; 
	struct TreeNode *Rchild;
};

int IsOperator(char X)
{
	if (X == '+' || X == '-' || X == '*' || X == '/' || X == '(' || X == ')' || X == '=')
		return 1;
	else
		return 0;
}

//计算表达式中的数字
double Num(string Expression, int &i)
{
	double integer = 0;  
	double decimal = 0; 
	int k = 0; //变量存储小数点后面的数字;
	while (!IsOperator(Expression[i])) //
	{
		while (Expression[i] != '.' && !IsOperator(Expression[i]))
		{ 
			integer *= 10;
			integer += (Expression[i] - '0');
			i++;
		}
		while (!IsOperator(Expression[i])) {   
			if (Expression[i] == '.')
				i++;
			else  //calculate the decimal part;
			{
				decimal *= 10;
				decimal += (Expression[i] - '0');
				i++;
				k++;
			}
		}
	}
	i--;
	while (k--) //获取小数点;
		decimal /= 10;
	return integer + decimal;
}

//中缀改后缀
Stack<Node> InfixToPost(string Expression)
{
	int i = 0;
	Node node;
	Stack<char> OperatorStack;  
	Stack<Node> PostStack;   
	OperatorStack.InitStack();
	PostStack.InitStack();
	while (Expression[i] != '=')
		node.Operator = '#';
		if (Expression[i] == '+' || Expression[i] == '-')
		{
			while (OperatorStack.Peek() == '+' || OperatorStack.Peek() == '+' ||
				OperatorStack.Peek() == '*' || OperatorStack.Peek() == '/') {
				node.Operator = OperatorStack.Pop();
				PostStack.Push(node);
			}
			OperatorStack.Push(Expression[i]);
		}
		else if (Expression[i] == '*' || Expression[i] == '/')
		{
			//Process all * / in the top of the Operrator satck;
			while (OperatorStack.Peek() == '*' || OperatorStack.Peek() == '/') {
				node.Operator = OperatorStack.Pop();
				PostStack.Push(node);
			}
			OperatorStack.Push(Expression[i]);
		}
		else if (Expression[i] == '(')
			OperatorStack.Push(Expression[i]);
		else if (Expression[i] == ')')
		{
			while (OperatorStack.Peek() != '(') 
				node.Operator = OperatorStack.Pop();
				PostStack.Push(node);
			}
			OperatorStack.Pop();
		}
		else
		{
			node.Operand = Num(Expression, i); 
			PostStack.Push(node);
		}
		i++;
	}
	while (!OperatorStack.IsEmpty()) {  
		node.Operator = OperatorStack.Pop();
		PostStack.Push(node);
	}
	return PostStack;
}

Stack<TreeNode*> CreatTree(Stack<Node> PostStack)
{
	Stack<TreeNode*> TreeStack;
	TreeStack.InitStack();
	TreeNode *node, *root;
	int bottom = PostStack.GetTop(); //获得栈顶元素;
	int top = 0;
	while (top <= bottom)
	{
		if (PostStack.ReturnData(top).Operator == '#')
		{
			node = (TreeNode*)malloc(sizeof(TreeNode));
			node->Operand = PostStack.ReturnData(top).Operand;
			node->Lchild = node->Rchild = NULL;
			TreeStack.Push(node);
		}
		else
		{
			root = (TreeNode*)malloc(sizeof(TreeNode));
			root->Operator = PostStack.ReturnData(top).Operator;
			root->Rchild = TreeStack.Pop();
			root->Lchild = TreeStack.Pop();
			TreeStack.Push(root);
		}
		top++;
	}
	return TreeStack;
}

//后缀表达式计算
double Calculate(TreeNode *T)
{
	if (T->Lchild == NULL && T->Rchild == NULL)
		return T->Operand;
	switch (T->Operator)
	{
	case '+':return Calculate(T->Lchild) + Calculate(T->Rchild);
	case '-':return Calculate(T->Lchild) - Calculate(T->Rchild);
	case '*':return Calculate(T->Lchild) * Calculate(T->Rchild);
	case '/':return Calculate(T->Lchild) / Calculate(T->Rchild);
	}
}

void WriteIntoFile(string Expression, double Num, string filename)
{
	filename += "_out.txt";
	ofstream file(filename.c_str(), ios::app);
	file << Expression << setprecision(6) << Num << endl;  //add "=" when no "="
	file.close();
}

void WriteRecord(double time, string filename)
{
	filename += "_log.txt";
	time *= 1000;
	double hour, minute, second;
	(time >= 3600) ? hour = time / 3600 : hour = 0;
	(time >= 60) ? minute = time / 60 - hour * 60 : minute = 0;
	second = time - hour * 3600 - minute * 60;
	ofstream file2(filename.c_str());
	file2 << "执行运算时间：" << hour << " h " << minute << " m " << second << " s " << endl;
	file2 << "总的表达式数量：" << TotalExp << endl;
	file2 << "正确表达式数量：" << TotalExp - ErrorExp << endl;
	file2 << "错误表达式数量：" << ErrorExp << endl;
	file2.close();
}

int main()
{
	string Expression, filename, newname;
	cout << "请输入要打开的文本文件 ：";
	cin >> filename;
	newname = filename + ".txt";
	ifstream File(newname.c_str());
	clock_t start = clock();
	while (File >> Expression) {
		TotalExp++;
		Stack<Node> S = InfixToPost(Expression);
		Stack<TreeNode*> T = CreatTree(S);
		TreeNode* Tree = T.Pop();
		double Num = Calculate(Tree);
		WriteIntoFile(Expression, Num, filename);
	}
	File.close();
	clock_t finish = clock();
	double time = (double)(finish - start) / CLOCKS_PER_SEC;
	WriteRecord(time, filename);
	return 0;
}