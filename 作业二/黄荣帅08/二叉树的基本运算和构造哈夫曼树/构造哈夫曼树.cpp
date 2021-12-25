#include<iostream>
#include<cstdio>
#include<cstring> 
#define N 10 
#define M 2 * N-1 
using namespace std;

typedef struct
{
	char data[5]; //结值点
	int weight; //权重
	int parent; //双亲结点 
	int lchild; //左孩子结点 
	int rchild; //右孩子结点 
}HTNode;

typedef struct
{
	char cd[N]; //存放当前结点地哈夫曼码 
	int start; //存放哈夫曼树在cd中的起始位置 
}HCode;

void CreateHT(HTNode ht[],int n) 
{
	int i,k,lnode,rnode; int min1,min2;
	for (i=0;i<2*n-1;i++) // 所有结点的相关域值初值为-1 
		ht[i].parent=ht[i].lchild=ht[i].rchild=-1;
	for (i=n;i<2*n-1;i++) //构造哈夫曼树 
	{
		min1=min2=32767; 
		lnode = rnode = -1;
		for(k=0;k<=i-1;k++) 
		if(ht[k].parent==-1) //未构造二叉树的结点中查找 
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
	for(i=0;i<n;i++) //根据哈夫曼树求哈夫曼码 
	{
		hc.start=n;
		c=i;
		f=ht[i].parent; 
		while(f!=-1)//循环直到无双亲结点即到达树根结点 
		{
			if(ht[f].lchild==c) //当前结点是左孩子结点 
				hc.cd[hc.start--]='0';
			else //当前结点是双亲结点的右孩子结点 
				hc.cd[hc.start--]='1';
			c=f;
			f=ht[f].parent;//再对双亲结点进行同样的操作 
		}
		hc.start++; //start指向哈夫曼码最开始字符 
		hcd[i]=hc;
	}
}

void DispHCode(HTNode ht[],HCode hcd[],int n) 
{
	int i,k; 
	int j;
	cout<<"输出哈夫曼编码:"<<endl;
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


