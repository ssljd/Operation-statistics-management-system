#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#define MaxSize 20
#define INIFITY 1000
using namespace std;

//创建一个Stack类 
template <typename T>  
class Stack {    
public:
	void InitStack() {   //初始化栈 
		Top = -1;
	}
	int IsEmpty() {     //判断栈是否为空 
		return Top == -1;
	}
	int Push(T X) {   //压数进栈 
		if (Top + 1 == MaxSize)  //判断栈是否满了 
			return -1;
		Data[++Top] = X;
		return 0;
	}
	T Pop() { //出栈 
		return Data[Top--];
	}
	T Peek() { //返回第一个数据 
		return Data[Top];
	}
	int GetTop() //栈顶元素 
	{
		return Top;
	}
	T ReturnData(int Top)  //return the data in array which index is top;
	{
		return Data[Top];
	}
private:
	int Top;  //store the index of the first data;
	T Data[MaxSize]; //store the data;
};
int TotalExp = 0; //a variable to store the number of expressions in the file;
int ErrorExp = 0; //a variable to store the number of wrong expressions;

//a struct contains an operand and an operator;
struct Node {  
	double Operand;
	char Operator;
};

struct TreeNode { 
	double Operand;
	char Operator;
	struct TreeNode *Lchild; //a pointer points to the left node;
	struct TreeNode *Rchild; //a pointer points to the right node;
};

//if character is an operater,return 1,else return 0;
int IsOperator(char X) 
{
	if (X == '+' || X == '-' || X == '*' || X == '/' || X == '(' || X == ')' || X == '=')
		return 1;
	else
		return 0;
}

//a founction to calculate the number int an expression;
double Num(string Expression, int &i) 
{
	double integer = 0;  //initialize the interger part;
	double decimal = 0;  //initialize the decimal part;
	int k = 0; //a variable stores how many digits behind the decimal point;
	while (!IsOperator(Expression[i])) //add i < Expression.size() when no "=" 
	{
		while (Expression[i] != '.' && !IsOperator(Expression[i]))//calculate the interger part;
		{                                                         //add i < Expression.size() when no "=" 
			integer *= 10;
			integer += (Expression[i] - '0');
			i++;
		}
		while (!IsOperator(Expression[i])) {                      // add i < Expression.size() when no "=" 
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
	while (k--) //get the decimal;
		decimal /= 10;
	return integer + decimal;
}

//a fonction to change infix to postfix;
Stack<Node> InfixToPost(string Expression)
{
	int i = 0;
	Node node;
	Stack<char> OperatorStack;  //creat a stack with type of char to store operators;
	Stack<Node> PostStack;   //creat a stack with type of Node to store postfix expressions;
	OperatorStack.InitStack(); 
	PostStack.InitStack();
	while (Expression[i] != '=') {  //i < Expression.size() when no "="
		node.Operator = '#';
		if (Expression[i] == '+' || Expression[i] == '-')
		{
			//Process all + - * / in the top of the Operrator satck;
			while (OperatorStack.Peek() == '+' || OperatorStack.Peek() == '+' ||
				OperatorStack.Peek() == '*' || OperatorStack.Peek() == '/') {
				node.Operator = OperatorStack.Pop();
				PostStack.Push(node);
			}
			OperatorStack.Push(Expression[i]);//Push the + or - operator into the Operator stack;
		}
		else if (Expression[i] == '*' || Expression[i] == '/')
		{
			//Process all * / in the top of the Operrator satck;
			while (OperatorStack.Peek() == '*' || OperatorStack.Peek() == '/') {
				node.Operator = OperatorStack.Pop();
				PostStack.Push(node);
			}
			OperatorStack.Push(Expression[i]);//Push the * or / operator into the Operator stack;
		}
		else if (Expression[i] == '(')
			OperatorStack.Push(Expression[i]);//Push ( to Operator stack;
		else if (Expression[i] == ')')
		{
			while (OperatorStack.Peek() != '(') {//Process all the operators int the stack until seeing ( ;
				node.Operator = OperatorStack.Pop();
				PostStack.Push(node);
			}
			OperatorStack.Pop();//Pop the ( symbol from the stack;
		}
		else
		{
			node.Operand = Num(Expression, i); //calculate the number from the expressions;
			PostStack.Push(node);//Push an operand to the stack ;
		}
		i++;
	}
	while (!OperatorStack.IsEmpty()) {  //Process all the remaining operators int the stack;
		node.Operator = OperatorStack.Pop();
		PostStack.Push(node);
	}
	return PostStack;
}

//using the post stack to creat a tree;
Stack<TreeNode*> CreatTree(Stack<Node> PostStack)
{
	Stack<TreeNode*> TreeStack;  
	TreeStack.InitStack();  
	TreeNode *node, *root; 
	int bottom = PostStack.GetTop(); //get the total number of the stack;
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

//a function to calculate the operater tree;
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

//Write the expressions and their results into a file;
void WriteIntoFile(string Expression, double Num, string filename)
{
	filename += "_out.txt";
	ofstream file(filename.c_str(), ios::app);
	file << Expression << setprecision(6) << Num << endl;  //add "=" when no "="
	file.close();
}

//Write a statistics file;
void WriteRecord(double time,string filename)
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
	cout << "请输入要打开的文件名 ：";
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
	WriteRecord(time ,filename);
	return 0;
}

