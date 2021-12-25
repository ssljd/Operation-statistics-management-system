#include<iostream>
#include<cstring>
using namespace std;

 typedef struct node{   	
 	char data;
    struct node *lchild;
 	struct node *rchild;
} BTNode;


void CreateBTNode(node* b,char *str){
	
	int len=strlen(str);
	node* list[99];
	node* p=nullptr;
	int top=-1;
	char decide=' ';
	
	for(int i=0;i<len;i++){
		int c=str[i];
		
		if(c=='('){
			list[++top]=p;
			decide='l';
		}else if(')'){
			top--;
		}else if(','){
			decide='r';
		}else{
			p=new node();
			p->data=c;
			if(b==nullptr){
				b=p;
			}else{
				if(decide='l'){
					list[top]->lchild=p;
				}else if(decide='r'){
					list[top]->rchild=p;
				}
			}
		}
	}
}


node* findNode(node *b,char x){
	node* p;
         if (b==nullptr)   return nullptr;
         else if (b->data==x)   return b;
         else 
         {      p=findNode(b->lchild,x);
	    if (p!=nullptr) return p;
	     else   return findNode(b->rchild,x);
          }

}

node* lchildNode(node *p)
    {
           return p->lchild;
    }
    
    
node* rchildNode(node *p)
    {
          return p->rchild;
    } 


int depth(node *b) 
{     int lchilddep,rchilddep;
      if (b==nullptr) return 0; 
      else  
      {     
	 	 lchilddep=depth(b->lchild);	
  	 	rchilddep=depth(b->rchild);	
	
	 return(lchilddep>rchilddep)?
                      (lchilddep+1):(rchilddep+1);
      }
}


void display(node *b) {	
		if (b!=nullptr){     
		cout<<b->data;
	       if (b->lchild!=nullptr || b->rchild!=nullptr)
	       {	   printf("(");
		   display(b->lchild);
		
		   if (b->rchild!=nullptr) cout<<",";
		   display(b->rchild);

		   cout<<")";
	       }
	}
}







