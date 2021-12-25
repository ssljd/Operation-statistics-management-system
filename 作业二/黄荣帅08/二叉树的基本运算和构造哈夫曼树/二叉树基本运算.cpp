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
     if (b==NULL) return(0); /*空树的高度为0*/
     else  
     {     lchilddep=BTNodeDepth(b->lchild);    
       /*求左子树的高度为lchilddep*/
      rchilddep=BTNodeDepth(b->rchild);    
       /*求右子树的高度为rchilddep*/
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
           /*递归处理左子树*/
          if (b->rchild!=NULL) printf(",");
          DispBTNode(b->rchild);
           /*递归处理右子树*/
          printf(")");
          }
   }
   }
   
int main()
{
	BTree T; 
	CreatBTree(T);//创建树;
	char x ='C';
	FindNode(T,x);//查找结点;
	LchildNode(T);//寻找左孩子; 
	RchildNode(T);//寻找右孩子； 
	BTNodeDepth(T);//求高度； 
	DispBTNode(T);//输出二叉树： 
	 return 0;
	
}

          
   
 

