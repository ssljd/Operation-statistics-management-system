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
	ifstream file("D:\\�ı�.txt");
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
	ofstream file("D:\\�ı�1.txt");
	Position P;
	for (P = L->Next; P; P = P->Next)
	{
		file << P->ID << " " << P->NAME << " " << P->NUM << endl;
	}
	file.close();
	rename("D:\\�ı�1.txt", "D:\\�ı�2.txt");
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
		cout << "��ѡ������Ҫ�Ĺ���" << endl;
		cout << "1.��Ӽ�¼" << endl;
		cout << "2.ɾ����¼" << endl;
		cout << "3.�����¼" << endl;
		cout << "4.����������" << endl;
		cout << "5.�����¼" << endl;
		cout << "6.��ռ�¼" << endl;
		cout << "7.�˳�" << endl;

		cin >> fun;
		switch (fun)
		{
		case 1:
			cout << "���������ѧ��ID��";
			cin >> ID;
			cout << "���������������";
			cin >> NAME;
			cout << "��������ĵ绰���룺";
			cin >> NUM;
			Add(L, ID, NAME, NUM);
			cout << "��ӳɹ�" << endl;
			system("pause");
			system("cls");
			break;
		case 2:
			int Result;
			cout << "����������Ҫɾ����Ϣ��ѧ�ţ�";
			cin >> ID;
			Result = Delete(L, ID);
			if (Result == 0)
			{
				cout << "ɾ���ɹ�" << endl;
			}
			else
				cout << "ɾ��ʧ��" << endl;
			system("pause");
			system("cls");
			break;
		case 3:
			PrintAll(L);
			system("pause");
			system("cls");
			break;
		case 4:
			cout << "����������Ҫ������Ϣѧ����������";
			cin >> NAME;
			find(L, NAME);
			Result = find(L, NAME);
			if (Result == -1)
			{
				cout << "û���ҵ���λѧ��" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 5:
			Storage(L);
			cout << "����ɹ�����" << endl;
			system("pause");
			system("cls");
			break;
		case 6:
			DeleteAll(L);
			cout << "�Ѿ�������м�¼������" << endl;
			system("pause");
			system("cls");
			break;
		case 7:
			cout << "�����˳�ϵͳ����" << endl;
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