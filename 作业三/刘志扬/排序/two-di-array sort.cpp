#include<iostream>
#include"file.h"
using namespace std;

void sort1(string a[],int n)//�����㷨һ(ѡ������)
{
	for(int i=0;i<=n-2;i++)
		for (int j = i; j <= n - 1; j++)
		{
			if (a[i] > a[j])
			{
				string temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
}


void sort2(string s[], int n)//�����㷨��(��������)
{
	int i, j;
	string temp;
	for (i = 1; i <= n - 1; i++)
	{
		temp = s[i];
		for (j = i; j > 0 && s[j - 1] > temp; j--)
		{
			s[j] = s[j - 1];
		}
		s[j] = temp;
	}
}


int main()
{
	int i, j;
	read("1.txt", i, j, a);//�����ݴ�һά���飬ͬʱ���ά������������
	sort2(a,i*j);//�������������
	int count = 0;
	for(int s=0;s<=i-1;s++)
		for (int m = 0; m <= j - 1; m++)//���ݶ�ȡ���������������������ݴ����ά����
		{
			b[s][m] = a[count];
			count++;
		}

	write("result.txt", b, i, j);//�ı�������
	cout << "done" << endl;



	return 0;
}