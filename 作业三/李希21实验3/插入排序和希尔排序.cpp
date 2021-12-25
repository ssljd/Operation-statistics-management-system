#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define NumberSize 5
int A[NumberSize];
using namespace std;


//生成随机数 
void Input()
{
	int a;
	for(int i=0;i<NumberSize;i++){
	   scanf("%d",&a);
	  A[i]=a;
	}
	  
}

//输出
void output()
{
	for(int i=0;i<NumberSize;i++)
	   cout<<A[i]<<endl;
	cout<<endl;
 } 
//插入排序 
void InsertionSort(int A[],int N){
	for(int p = 1;p<N;p++){
		int tmp = A[p];   // 取出一个数 
		int j = p;
		for(;tmp<A[j-1] && j > 0;j--)  // 找到这个数适合的位置 
			A[j] = A[j-1];  
		A[j] = tmp;  //  把合适大小的数放入 
	} 
}
//希尔排序 
void Shellsort(int N)
{
	for(int D=N/2;D>0;D/=2)
	{
		for(int p=D;p<N;p+=D)
		{
			int tmp = A[p];
			int j = p;
			for(;j>=D && tmp<A[j-D] ;j-=D)  // j>=D 在前，因为也许 A[j-D]已经越界 
				A[j] = A[j-D];
			A[j] = tmp;
		}
	}
} 

int main()
{
	int m;
	Input();
	cin>>m;
	output();
	InsertionSort(A,NumberSize);//插入排序
	output();
//	Shellsort(NumberSize);//希尔排序 
	return 0;
 } 
