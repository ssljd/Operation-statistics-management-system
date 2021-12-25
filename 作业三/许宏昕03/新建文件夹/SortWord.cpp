#include <iostream>
#include <string.h>
using namespace std;

#define MaxLen 10
#define Radix 27            //�շ��Ž�0��������ĸ������ĸ��˳����ջ
typedef char String[MaxLen + 1];
typedef struct node
{
    String word;
    struct node *next;
} LinkNode;

void DisplayWord(String R[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        cout<<" "<< R[i];
    }
        cout << R[i];
    cout << endl;
}

void PreProcess(String R[], int n)      //Ԥ�������ڳ��Ȳ����ĵ����Կո񲹳�
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strlen(R[i]) < MaxLen)
        {
            for (j = strlen(R[i]); j < MaxLen; j++)
                R[i][j] = ' ';
            R[i][j] = '\0';
        }
    }
}

void EndProcess(String R[], int n)  //β���������޸�֮��ĵ��ʽ����޸ģ�ʹ��ָ�ԭ��
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = MaxLen - 1; R[i][j] == ' '; j--)
            R[i][j + 1] = '\0';
    }
}

void Distribute(String R[], LinkNode *head[], LinkNode *tail[], int j, int n)
{
    int i, k;
    LinkNode *p;
    for (i = 0; i < n; i++)
    {
        if (R[i][j] == ' ')
            k = 0;
        else
            k = R[i][j] - 'a' + 1;
        p = (LinkNode *)malloc(sizeof(LinkNode));
        strcpy(p->word, R[i]);
        p->next = NULL;                 //��������ջ
        if (head[k] == NULL)
        {
            head[k] = p;
            tail[k] = p;
        }
        else
        {
            tail[k]->next = p;
            tail[k] = p;
        }
    }
}

void Collect(String R[], LinkNode *head[])      //�ռ��ռ���
{
    int k = 0, i;
    LinkNode *p;
    for (i = 0; i < Radix; i++)
        for (p = head[i]; p != NULL; p = p->next)
            strcpy(R[k++], p->word);
}

void RadixSort(String R[], int n)   //���л����򣬶���β����ĸ�������򣬲�����ջ
{
    LinkNode *head[Radix], *tail[Radix];
    int i, j;
    for (i = MaxLen - 1; i >= 0; i--)
    {
        for (j = 0; j < Radix; j++)
            head[j] = tail[j] = NULL;
        Distribute(R, head, tail, i, n);
        Collect(R, head);
    }
}

int main()
{
    int n = 7;
    String R[] = {"while","if","wait","for","else","tip","but"}; 
    // cout<<"排序�?"<<endl;
    // DisplayWord(R,n);
    // PreProcess(R,n);
    // cout<<"预处理后�?"<<endl;
    // DisplayWord(R,n);
    // RadixSort(R,n);
    // cout<<"排序结果�?"<<endl;
    // DisplayWord(R,n);
    // EndProcess(R,n);
    // cout<<"最终结�?"<<endl;
    DisplayWord(R,n);
}