#include<iostream>
#include<string>
using namespace std;


string list[]={"while","if","else","do","for","switch","case"};



void sortMaoPao(string list[],int len) {//√∞≈› 
	for(int i=0;i<len-1;i++){
		for(int j=0;j<len-1-i;j++){
			if(list[j+1]<list[j]){
				string tem=list[j+1];
				list[j+1]=list[j];
				list[j]=tem;
			}
		}
	}
	
} 

void sortedSort(string list[],int len){//—°‘Ò 
	 for(int i=0;i<len-1;i++){
            string temp=list[i];
            int index=i;
            for (int j=i;j<len;j++){
                if(temp>list[j]){
                    temp=list[j];
                    index=j;
                }
            }
            if(index!=i){
                list[index]=list[i];
                list[i]=temp;
            }
        }
}


void insertSort(string list[],int len){//≤Â»Î≈≈–Ú 
	for(int i=1;i<len;i++){
            int index=i-1;
            string val=list[i];
            while (index>=0 && val<list[index]){
               list[index+1]=list[index];
                index--;
            }

            list[index+1]=val;
        }
	
}

void print(string list[],int len){
	for(int i=0;i<len;i++)
		cout<<list[i]<<" ";
}

int main(){
		 
	insertSort(list,7);	 
	print(list,7);	 
	return 0;
} 
