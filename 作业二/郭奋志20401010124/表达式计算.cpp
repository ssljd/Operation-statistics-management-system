#include<iostream>
#include<string>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<fstream>
#include<iomanip> 
#include<ctime>
using namespace std;
template<typename T>
class Stack 
{
	public:
		Stack();
		Stack(const Stack&);
		~Stack();
		bool empty()const;
		T peek()const;
		void push(T value);
		T pop();
		int getSize()const;
		
	private:
		T* elements;
		int size;
		int capacity;
		void ensureCapacity(); 
};
template<typename T>
Stack<T>::Stack():size(0),capacity(16)
{
	elements=new T[capacity];	
} 
template<typename T>
Stack<T>::Stack(const Stack& stack)
{
	elements=new T[stack.capacity];
	size=stack.size;
	capacity=stack.capacity;
	for(int i=0;i<size;i++)
	{
		elements[i]=stack.elements[i];
	}
}
template<typename T>
Stack<T>::~Stack() 
{
	delete [] elements;
} 
template<typename T>
bool Stack<T>::empty()const
{
	return size==0;
}
template<typename T>
T Stack<T>::peek()const
{
	return elements[size-1];
}
template<typename T>
void Stack<T>::push(T value)
{
	ensureCapacity();
	elements[size++]=value;
}
template<typename T>
void Stack<T>::ensureCapacity()
{
	if(size==capacity)
	{
		T* old=elements;
		capacity=2*size;
		elements=new T[capacity];
		for(int i=0;i<size;i++)
		elements[i]=old[i];
		delete [] old;
	}
}
template<typename T>
T Stack<T>:: pop()
{
	if(size>=0)
	  	return elements[--size];
	else
		return 0;
	  	
}
template<typename T>
int Stack<T>:: getSize()const
{
	return size;
}
vector<string>split(const string& expression); 
bool  isCorrect(vector<string>&);
double evaluateExpression(const string& expression);
void processAnOperator(Stack<double>&,Stack<char>&);

int main()
{
	clock_t begin,end;
	begin=clock();
	ifstream input("Expressions.txt");
	ofstream out("Expressions_out.txt");
	ofstream output("Expressions_log.txt");
	string expression;
	int correct=0,count=0;
	while(getline(input,expression,'\n'))
	{
		count++;
		vector<string> v=split(expression);
		if(isCorrect(v))
		{
			correct++;
			double re=evaluateExpression(expression);
			if((re-((int)re))!=0)
			out<<expression<<" = "<<fixed<<setprecision(4)<<re<<endl;
			else
				out<<expression<<" = "<<((int)re)<<endl;
			
		}
		else
		out<<expression<<" :错误表达式"<<endl;
			
		
	}
	end=clock();
	output<<"执行时间："<<end-begin<<"ms"<<endl;
	output<<"表达式数目总数目："<<count<<endl;
	output<<"正确表达式数目：" <<correct<<endl;
	output<<"错误表达式是数目："<<count-correct<<endl;
	
	input.close();
	out.close();
	output.close();
	return 0;
}
vector<string>split(const string& expression)
{
	vector<string> v;
	string numberString;
	for(unsigned i=0;i<expression.length();i++)
	{
		if((isdigit(expression[i]))||expression[i]=='.')
		numberString.append(1,expression[i]);
		else
		{
			if(numberString.size()>0)
			{
				v.push_back(numberString);
				numberString.erase();
			}
			if(!isspace(expression[i]))
			{
				string s;
				s.append(1,expression[i]);
				v.push_back(s);
			}
		}
	}
	if(numberString.size()>0)
	v.push_back(numberString);
	return v;
}
bool isCorrect(vector<string>& ve)
{
	 char ch=ve[0][0];
	 char lastch=ve[ve.size()-1][(ve[ve.size()-1].length()-1)];
	 int left=0,right=0;
	 if(ch!='+'&&ch!='-'&&ch!='('&&!isdigit(ch))
	 	return false;
	 if(lastch!=')'&&!isdigit(lastch))
	 	return false;
	 if(lastch==')')
	 	right++;
	 for(unsigned i=0;i<ve.size()-1;i++)
	 {
	 	char c1=ve[i][0];
	 	char c2=ve[i+1][0];
	 	if(c1=='(')
	 	{
	 		left++;
	 		if(c2!='('&&c2!='-'&&c2!='+'&&!isdigit(c2))
	 		return false;
		}
		else if(c1==')')
		{
			right++;
			if(c2!=')'&&c2!='('&&c2!='+'&&c2!='-'&&c2!='*'&&c2!='/')
				return false;
		}
		else if(c1=='+')
		{
			if(c2!='('&&!isdigit(c2))
				return false;
		}
		else if(c1=='-')
		{
			if(c2!='('&&!isdigit(c2))
				return false;
		}
		else if(c1=='*')
		{
			if(c2!='('&&!isdigit(c2))
				return false;
		}
		else if(c1=='/')
		{
			if(c2!='('&&!isdigit(c2))
				return false;
		}
		else if(isdigit(c1))
		{		
		}
		else
			return false;
		
	 }
	 if(left!=right)
	 	return false;
	 return true;
}
double evaluateExpression(const string& expression)
{
	Stack<double> operandStack;
	Stack<char> operatorStack;
	vector<string> tokens=split(expression);
	for(unsigned i=0;i<tokens.size();i++)
	{
		if(tokens[i][0]=='+'||tokens[i][0]=='-')
		
		{
			while(!operatorStack.empty()&&(operatorStack.peek()=='+'||operatorStack.peek()=='-'
				||operatorStack.peek()=='*'||operatorStack.peek()=='/'))
			{
				processAnOperator(operandStack,operatorStack);
			}
			operatorStack.push(tokens[i][0]);
		}
		else if(tokens[i][0]=='*'||tokens[i][0]=='/')
		{
			while(!operatorStack.empty()&&(operatorStack.peek()=='*'||operatorStack.peek()=='/'))
			{
				processAnOperator(operandStack,operatorStack);
			}
			operatorStack.push(tokens[i][0]);
		}
		else if(tokens[i][0]=='(')
		{
			operatorStack.push('(');
		}
		else if(tokens[i][0]==')')
		{
			while(operatorStack.peek()!='(')
			{
				processAnOperator(operandStack,operatorStack);
			}
			operatorStack.pop(); 
		}
		else
		{
			operandStack.push(atof(tokens[i].c_str()));
		}
	}
	while(!operatorStack.empty())
	{
		processAnOperator(operandStack,operatorStack);
	}
	return operandStack.pop();
}
void processAnOperator(Stack<double>& operandStack,Stack<char>& operatorStack)
{
	char op=operatorStack.pop();
	double op1=operandStack.pop();
	double op2=operandStack.pop();
	double answer;
	if(op=='+') 
		answer=op2+op1;
	else if(op=='-')
		answer=op2-op1;
	else if(op=='*')
		answer=op2*op1;
	else if(op=='/')
		answer=op2/op1;
	else
		{
		}
	operandStack.push(answer);
}
