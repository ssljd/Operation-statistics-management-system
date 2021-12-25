#include<iostream>
#include<cstdio>
#include<cstring> 
#define N 10 
#define M 2 * N-1 
using namespace std;

typedef struct
{
	char data[5]; //��ֵ��
	int weight; //Ȩ��
	int parent; //˫�׽�� 
	int lchild; //���ӽ�� 
	int rchild; //�Һ��ӽ�� 
}HTNode;

typedef struct
{
	char cd[N]; //��ŵ�ǰ���ع������� 
	int start; //��Ź���������cd�е���ʼλ�� 
}HCode;

void CreateHT(HTNode ht[],int n) 
{
	int i,k,lnode,rnode; int min1,min2;
	for (i=0;i<2*n-1;i++) // ���н��������ֵ��ֵΪ-1 
		ht[i].parent=ht[i].lchild=ht[i].rchild=-1;
	for (i=n;i<2*n-1;i++) //����������� 
	{
		min1=min2=32767; 
		lnode = rnode = -1;
		for(k=0;k<=i-1;k++) 
		if(ht[k].parent==-1) //δ����������Ľ���в��� 
		{
		if(ht[k].weight<min1)
			{
				min2=min1;
				rnode=lnode;
				min1=ht[k].weight;
				lnode=k;
			}
		else if(ht[k].weight<min2)
			{
				min2=ht[k].weight;
				rnode=k;
			}
		}
	ht[lnode].parent=i;
	ht[rnode].parent=i;
	ht[i].weight=ht[lnode].weight+ht[rnode].weight;
	ht[i].lchild=lnode;
	ht[i].rchild=rnode;
	}
}

void CreateHCode(HTNode ht[],HCode hcd[],int n) 
{
	int i,f,c;
	HCode hc;
	for(i=0;i<n;i++) //���ݹ���������������� 
	{
		hc.start=n;
		c=i;
		f=ht[i].parent; 
		while(f!=-1)//ѭ��ֱ����˫�׽�㼴����������� 
		{
			if(ht[f].lchild==c) //��ǰ��������ӽ�� 
				hc.cd[hc.start--]='0';
			else //��ǰ�����˫�׽����Һ��ӽ�� 
				hc.cd[hc.start--]='1';
			c=f;
			f=ht[f].parent;//�ٶ�˫�׽�����ͬ���Ĳ��� 
		}
		hc.start++; //startָ����������ʼ�ַ� 
		hcd[i]=hc;
	}
}

void DispHCode(HTNode ht[],HCode hcd[],int n) 
{
	int i,k; 
	int j;
	cout<<"�������������:"<<endl;
	for (i=0;i<n;i++)
	{
		j=0;
		cout<<ht[i].data<<" ";
		for(k=hcd[i].start;k<=n;k++)
		{
			cout<<hcd[i].cd[k];
			j++;
		}
		cout<<endl;
	}
}

int main()
{
	int n=5,i;
	const char *str[]={"a","u","p","t","o"};
	int fnum[]={14,8,6,5,2};
	HTNode ht[M];
	HCode hcd[N];
	for(i=0;i<n;i++)
	{
		strcpy(ht[i].data,str[i]);
		ht[i].weight=fnum[i];
	}
	CreateHT(ht,n);
	CreateHCode(ht,hcd,n);
	DispHCode(ht,hcd,n);
	return 0;
}


