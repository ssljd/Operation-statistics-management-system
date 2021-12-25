#include<iostream>
#include<fstream>
using namespace std;
void InsertionSort(int a[],int N);
void Shellsort(int a[],int N);
const int N = 13;
int main()
{
	ifstream input;
	input.open("data.txt");
	int a[13];
	for(int i = 0; i < 13; i++)
		input >> a[i];
	input.close();
	cout<<"需要排序的数据为："<<endl;
	for(int j = 0; j < 13; j++)
	cout<<a[j]<<" ";cout<<endl;
	cout<<"插入排序后的数据："<<endl;
	InsertionSort(a,N);cout<<endl;
	cout<<"希尔排序后的数据："<<endl;
	Shellsort(a,N);
	
	return 0;
	
}
void InsertionSort(int a[],int N)
{
	int i,j,tmp;
	for(int i = 1; i < N; i++)
	{
		tmp = a[i];
		for(j = i; j > 0 && a[j-1] > tmp; j--)
		a[j] = a[j-1];
		a[j] = tmp;
	}
	for(int i = 0; i < N; i++)
	cout<<a[i]<<" ";
}
void Shellsort(int a[],int N)
{
	int i,j,Increment,tmp;
	for(Increment = N/2;Increment > 0; Increment /=2)
	{
		for(i = Increment; i < N; i++)
		{
			tmp =a[i];
			for(j = i; j >= Increment; j -= Increment)
			if(tmp < a[j-Increment])
				a[j] = a[j-Increment];
				else break;
				a[j] = tmp;
		}	
	} 
	for(int i = 0; i < N; i++)
	cout<<a[i]<<" ";
}


