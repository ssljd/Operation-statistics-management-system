#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void InsertSort(string a[], int n)
{
    for (int j = 1; j < n; j++)
    {
        string key = a[j]; 
        int i = j - 1; 
        while (i >= 0 && key < a[i])
        {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }
}

void BubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
        }
    }
}

void main()
{  
    int i = 0;
    string d[10];
    ifstream infile;
    infile.open("text.txt");
    while (!infile.eof())
    {
        infile >> d[i];
        if (infile.eof())
            break;
        i++;
    }
    infile.close();
    InsertSort(d, i);
    cout << "ÅÅÐòºó½á¹û£º";
    for (int j = 0; j < i; j++)
    {
        cout << d[j] << " ";
    }
}