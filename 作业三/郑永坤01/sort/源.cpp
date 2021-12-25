#include<iostream>
#include<string>
#include<cstring>
using namespace std;

/*void insertsort(int list[], int n)
{
	int i, j;
	int tmp;
	for (i = 1; i < n; i++)
	{
		tmp = list[i];
		for (j = i; j > 0 && tmp < list[j - 1]; j--)
			list[j] = list[j-1];
		list[j] = tmp;
	}
}*/

void Print_IS(char a[][20], int n, int i) {
	cout << i;
	for (int j = 0; j < n; j++) {
		cout << a[j] << " ";
	}
	cout << endl;
}
void insertsort(char s[][20], int n)
{
	int i, j;
	char x[20];
	for (i = 1; i < n; i++)
	{
		if (strcmp(s[i], s[i - 1]) < 0)        //strcmp函数用于字符串大小的比较，初次比较
		{
			strcpy_s(x, 20, s[i]);              //strpy_s函数赋值，不用strcpy而是strcpy_s和gets_s函数效果类似，安全
			for (j = i-1; j > -1 && strcmp(x, s[j]) < 0;j--)    
			{
				strcpy_s(s[j + 1], 20, s[j]);
			}
			strcpy_s(s[j + 1], 20, x);
		}
		Print_IS(s, n, i);
	}
}
void bubblesort(char s[][20], int n)
{
	char x[20];
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
		{
			if (strcmp(s[j], s[j + 1]) > 0)
			{
				//tmp = s[j];
				//s[j] = s[j + 1];
				//s[j + 1] = tmp;
				strcpy_s(x, 20, s[j]);
				strcpy_s(s[j], 20, s[j + 1]);
				strcpy_s(s[j + 1], 20, x);
			}
		}
	
}
/*void bubblesort(int list[], int n)
{
	int tmp;
	for(int i=0;i<n-1;i++)
		for (int j = 0; j < n - i-1; j++)
		{
			if (list[j] > list[j + 1])
			{
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
		}
}*/
int Quick_sort(char s[][20], int start, int end) {
	int i, j;
	i = start;
	j = end;

	strcpy_s(s[0], 20, s[start]);
	while (i < j) {
		while (i < j && strcmp(s[0], s[j]) < 0)
		{
			j--;
		}
		if (i < j) {
			strcpy_s(s[i], 20, s[j]);//
			i++;
		}
		while (i < j && strcmp(s[i], s[0]) <= 0)
		{
			i++;
		}
		if (i < j) {
			strcpy_s(s[i], s[j]);
			j--;
		}
	}
	strcpy_s(s[i], s[0]);

	if (start < i) {
		Quick_sort(s, start, j - 1);
	}
	if (i < end) {
		Quick_sort(s, j + 1, end);
	}
	return 0;
}

int main()
{
	char s[][20] =
	{
		"while",
		"if",
		"else",
		"do",
		"for",
		"swith",
		"case"
	};
	int i = 0;
	cout << "直接插入排序结果:" << endl;
	insertsort(s, 7);//插入排序！
	char S[][20] =
	{
		"TestWordUseless",
		"while",
		"if",
		"else",
		"do",
		"for",
		"swith",
		"case"
	};
	cout << "冒泡排序结果:" << endl;
	bubblesort(S, 7);
	for (int j = 0; j < 7; j++) 
	{
		cout << S[j] << " ";
	}
	cout << endl;
	char H[][20] =
	{
		"while",
		"if",
		"else",
		"do",
		"for",
		"swith",
		"case"
	};
	cout << "快速排序结果:" << endl;
	Quick_sort(S, 1, 7);
	for (int j = 0; j < 7; j++) 
	{
		cout << s[j] << " ";
	}
	cout << endl;
	return 0;
}