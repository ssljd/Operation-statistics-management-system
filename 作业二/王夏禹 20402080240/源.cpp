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

//���캯��
template <typename T>
class Stack {
public:
	void InitStack() {   //��ʼ��ջ
		Top = -1;
	}
	int IsEmpty() {     //�ж��Ƿ�Ϊ��
		return Top == -1;
	}
	int Push(T X) {   //��ջ
		if (Top + 1 == MaxSize) 
			return -1;
		Data[++Top] = X;
		return 0;
	}
	T Pop() { //��ջ
		return Data[Top--];
	}
	T Peek() { //����ջ��Ԫ��
		return Data[Top];
	}
	int GetTop() //����ջ��Ԫ�ص�ֵ;
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
int TotalExp = 0; //���ڴ洢�ļ��б��ʽ���ı���;
int ErrorExp = 0; //һ���������洢������ʽ������;

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

//������ʽ�е�����
double Num(string Expression, int &i)
{
	double integer = 0;  
	double decimal = 0; 
	int k = 0; //�����洢С������������;
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
	while (k--) //��ȡС����;
		decimal /= 10;
	return integer + decimal;
}

//��׺�ĺ�׺
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
	int bottom = PostStack.GetTop(); //���ջ��Ԫ��;
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

//��׺���ʽ����
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
	file2 << "ִ������ʱ�䣺" << hour << " h " << minute << " m " << second << " s " << endl;
	file2 << "�ܵı��ʽ������" << TotalExp << endl;
	file2 << "��ȷ���ʽ������" << TotalExp - ErrorExp << endl;
	file2 << "������ʽ������" << ErrorExp << endl;
	file2.close();
}

int main()
{
	string Expression, filename, newname;
	cout << "������Ҫ�򿪵��ı��ļ� ��";
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