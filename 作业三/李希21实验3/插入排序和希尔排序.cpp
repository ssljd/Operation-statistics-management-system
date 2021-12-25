#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define NumberSize 5
int A[NumberSize];
using namespace std;


//��������� 
void Input()
{
	int a;
	for(int i=0;i<NumberSize;i++){
	   scanf("%d",&a);
	  A[i]=a;
	}
	  
}

//���
void output()
{
	for(int i=0;i<NumberSize;i++)
	   cout<<A[i]<<endl;
	cout<<endl;
 } 
//�������� 
void InsertionSort(int A[],int N){
	for(int p = 1;p<N;p++){
		int tmp = A[p];   // ȡ��һ���� 
		int j = p;
		for(;tmp<A[j-1] && j > 0;j--)  // �ҵ�������ʺϵ�λ�� 
			A[j] = A[j-1];  
		A[j] = tmp;  //  �Ѻ��ʴ�С�������� 
	} 
}
//ϣ������ 
void Shellsort(int N)
{
	for(int D=N/2;D>0;D/=2)
	{
		for(int p=D;p<N;p+=D)
		{
			int tmp = A[p];
			int j = p;
			for(;j>=D && tmp<A[j-D] ;j-=D)  // j>=D ��ǰ����ΪҲ�� A[j-D]�Ѿ�Խ�� 
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
	InsertionSort(A,NumberSize);//��������
	output();
//	Shellsort(NumberSize);//ϣ������ 
	return 0;
 } 
