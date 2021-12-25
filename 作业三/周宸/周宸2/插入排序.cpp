#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;
void sort(int a[])
{
    int i, j, temp;
    for (i = 1; i<=sizeof(a)+1; i++) //控制趟数
       {
             temp = a[i];
             for(j = i; j > 0 && temp < a[j-1]; j--) // 无序区的数据与有序区的数据元素比较
               {
                  a[j] = a[j-1]; //将有序区的元素后移
               }
             a[j] = temp;
       }	
	for(int i=0;i<10;i++)
 	{
 		cout<<a[i]<<" ";
	 }
 } 
 int main()
 {
 	int c[100];
 	int k=0;
    fstream infile;
 	infile.open("zhuzi.txt");
 	if(infile.fail())
 	{
 		cout<<"文件不存在"<<endl;
	 }
 	while(!infile.eof())
 	{
 		infile>>c[k];
 		k++;
	 }
 	sort(c);
    return 0;
 }
