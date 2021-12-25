#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct BTNode{
	char data;
	struct BTNode *lchild,*rchild;
}BTNode,*BTree; 

void CreatBTree(BTree &T)
{
    char ch;
    cin >> ch;
    if(ch == '0')
        T = NULL;
    else
    {
        T = (BTree)malloc(sizeof(BTNode));    
        if(!T)
            exit(1);
        T->data = ch;
        CreatBTree(T->lchild); 
        CreatBTree(T->rchild); 
    }
}

BTree FindNode(BTree b,char x)
 {     BTree p;
        if (b==NULL)   return NULL;
        else if (b->data==x)   return b;
        else
        {      p=FindNode(b->lchild,x);
       if (p!=NULL) return p;
        else   return FindNode(b->rchild,x);
         }
 }
 
BTree LchildNode(BTree p)
{
    return p->lchild;
}

BTree RchildNode(BTree p)
{
    return p->rchild;
}

int BTNodeDepth(BTree b)
{     int lchilddep,rchilddep;
     if (b==NULL) return(0); /*�����ĸ߶�Ϊ0*/
     else  
     {     lchilddep=BTNodeDepth(b->lchild);    
       /*���������ĸ߶�Ϊlchilddep*/
      rchilddep=BTNodeDepth(b->rchild);    
       /*���������ĸ߶�Ϊrchilddep*/
    return(lchilddep>rchilddep)?
                     (lchilddep+1):(rchilddep+1);
     }
}

void DispBTNode(BTree b)
   {    if (b!=NULL)
   {     printf("%c",b->data);
          if (b->lchild!=NULL || b->rchild!=NULL)
          {       printf("(");
          DispBTNode(b->lchild);
           /*�ݹ鴦��������*/
          if (b->rchild!=NULL) printf(",");
          DispBTNode(b->rchild);
           /*�ݹ鴦��������*/
          printf(")");
          }
   }
   }
   
int main()
{
	BTree T; 
	CreatBTree(T);//������;
	char x ='C';
	FindNode(T,x);//���ҽ��;
	LchildNode(T);//Ѱ������; 
	RchildNode(T);//Ѱ���Һ��ӣ� 
	BTNodeDepth(T);//��߶ȣ� 
	DispBTNode(T);//����������� 
	 return 0;
	
}

          
   
 

