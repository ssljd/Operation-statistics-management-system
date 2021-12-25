#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<cstdlib>
using namespace std;

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node
{
	char ID[20];
	char NAME[20];
	char NUM[20];
	Position Next;
};

void Add(List L, const char ID[], char NAME[], char NUM[])
{
	Position TmpCell, p;
	TmpCell = (PtrToNode)malloc(sizeof(struct Node));
	strcpy_s(TmpCell->ID, ID);
	strcpy_s(TmpCell->NAME, NAME);
	strcpy_s(TmpCell->NUM, NUM);
	TmpCell->Next = NULL;
	p = L->Next;
	if (p)
	{
		while (p->Next)
			p = p->Next;
		p->Next = TmpCell;
	}
	else
		L->Next = TmpCell;
}

int Open(List& L)
{
	string c1, c2, c3;
	ifstream file("D:\\文本.txt");
	while (!file.eof())
	{
		file >> c1 >> c2 >> c3;
		const char* ID = c1.c_str();
		const char* NAME = c2.c_str();
		const char* NUM = c3.c_str();
		if (file.eof())
		{
			break;
		}
		//Add(L, ID,NAME,NUM);
	}file.close();
	return 0;
}

int Delete(List L, char ID[])
{
	Position P = L, TmpCell;
	while (P->Next)
	{
		if (strcmp(P->Next->ID, ID) == 0)
		{
			TmpCell = P->Next;
			P->Next = P->Next->Next;
			free(TmpCell);
			return 0;
		}
		P = P->Next;
	}
	return -1;
}

int find(List L, char Name[])
{
	Position P = L->Next;
	while (P)
	{
		if (strcmp(P->NAME, Name) == 0)
		{
			cout << P->ID << " " << P->NAME << " " << P->NUM << endl;
			return 0;
		}
		P = P->Next;
	}
	return -1;
}

void PrintAll(List L)
{
	Position P;
	for (P = L->Next; P; P = P->Next)
	{
		cout << P->ID << "  " << P->NAME << "  " << P->NUM << endl;
	}
}

void DeleteAll(List L)
{
	Position P, TmpCell;
	for (P = L; P->Next; )
	{
		TmpCell = P->Next;
		P->Next = P->Next->Next;
		free(TmpCell);
	}
	free(L);
}

int Storage(List L)
{
	string s1, s2, s3;
	ofstream file("D:\\文本1.txt");
	Position P;
	for (P = L->Next; P; P = P->Next)
	{
		file << P->ID << " " << P->NAME << " " << P->NUM << endl;
	}
	file.close();
	rename("D:\\文本1.txt", "D:\\文本2.txt");
	return 0;
}

void Menu()

{
	int fun;
	List L = (PtrToNode)malloc(sizeof(Node));
	L->Next = NULL;
	char ID[20], NAME[20], NUM[20];
	do
	{
		cout << "请选择你需要的功能" << endl;
		cout << "1.添加记录" << endl;
		cout << "2.删除记录" << endl;
		cout << "3.输出记录" << endl;
		cout << "4.按姓名查找" << endl;
		cout << "5.保存记录" << endl;
		cout << "6.清空记录" << endl;
		cout << "7.退出" << endl;

		cin >> fun;
		switch (fun)
		{
		case 1:
			cout << "请输入你的学号ID：";
			cin >> ID;
			cout << "请输入你的姓名：";
			cin >> NAME;
			cout << "请输入你的电话号码：";
			cin >> NUM;
			Add(L, ID, NAME, NUM);
			cout << "添加成功" << endl;
			system("pause");
			system("cls");
			break;
		case 2:
			int Result;
			cout << "请输入你需要删除信息的学号：";
			cin >> ID;
			Result = Delete(L, ID);
			if (Result == 0)
			{
				cout << "删除成功" << endl;
			}
			else
				cout << "删除失败" << endl;
			system("pause");
			system("cls");
			break;
		case 3:
			PrintAll(L);
			system("pause");
			system("cls");
			break;
		case 4:
			cout << "请输入你需要查找信息学生的姓名：";
			cin >> NAME;
			find(L, NAME);
			Result = find(L, NAME);
			if (Result == -1)
			{
				cout << "没有找到这位学生" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 5:
			Storage(L);
			cout << "保存成功！！" << endl;
			system("pause");
			system("cls");
			break;
		case 6:
			DeleteAll(L);
			cout << "已经清空所有记录！！！" << endl;
			system("pause");
			system("cls");
			break;
		case 7:
			cout << "正在退出系统！！" << endl;
		default:
			break;
		}
	} while (fun != 7);
}

int main()
{
	int Result;
	Menu();
	List L = (PtrToNode)malloc(sizeof(Node));
	L->Next = NULL;
	char ID[20], NAME[20], NUM[20];
	Open(L);

	return 0;
}