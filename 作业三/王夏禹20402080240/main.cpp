//
//  main.cpp
//  Sort comprehensive experiment
//
//  Created by 王夏禹 on 2021/12/5.
//

#include <iostream>
#include <fstream>
#include <string>
#include "algorithms.hpp"



using namespace std;
//char  s[][20]={“while”，”if”，“else”，”do”，“for”，”switch”，“case”};
//每个单词不超过20个字母

int main()
{
  
    fstream ifs;
    ifs.open("draft.txt",ios::in);
    if(!ifs)
    {
        cout<<"document can't open!"<<endl;
        return 0;
    }
    
    char bufs[100][20];
    int p=0;
    while(ifs>>bufs[p])
    {
        p++;
    }
    cout<<"original sentense:"<<endl;
    for(int i=0;i<p;i++)
    {
        cout<<bufs[i]<<" ";
    }
    cout<<endl;
    cout<<"sorted by InsertionSort:"<<endl;
    InsertSort(bufs, p);
    for(int i=0;i<p;i++)
    {
        cout<<bufs[i]<<" ";
    }
    cout<<endl;
    cout<<"sorted by SelectSort:"<<endl;
    SelectSort(bufs,p);
    for(int i=0;i<p;i++)
    {
        cout<<bufs[i]<<" ";
    }
    cout<<endl;
    cout<<"sorted by QuickSort:"<<endl;
    QuickSort(bufs, 0, p-1);
    for(int i=0;i<p;i++)
    {
        cout<<bufs[i]<<" ";
    }
    cout<<endl;
}
