#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string a[200];
string b[200][200];

void read(string s,int& p,int &j,string a[]) //��ȡ�ı����� �ı���һ��Ϊ����������������������ݣ���ȡ�����������
{
	ifstream A;
	int tempi, tempj;
	string temp;
	int i=0;
	A.open(s);
	if (A.fail())
	{
		throw - 1;
	}
	else
	{
		A >> tempi;
		A >> tempj;
		while (A >> temp)
		{
			a[i] = temp;
			i++;
		}
		p = tempi;
		j = tempj;
	}
}


void write(string s, string b[][200],int ti,int tj)
{
	ofstream A;
	A.open(s);
	for (int i = 0; i <= ti-1; i++)
	{
		for (int j = 0; j <= tj - 1; j++)
		{
			A << b[i][j] << " ";
		}
		A << endl;
	}
}