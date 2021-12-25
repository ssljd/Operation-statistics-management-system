#include <iostream>
#include <fstream>
using namespace std;
void shellsort(int v[])
{
	int gap, i, j, temp; 
	int n=sizeof(v);
	int k; 
	for(gap = n/2; gap > 0; gap /= 2)
		for(i = gap; i <= n+1; i++)
			for(j = i - gap; j >= 0 && v[j] > v[j+gap]; j-= gap)
			{
				temp = v[j]; 
				v[j] = v[j+gap]; 
				v[j+gap] = temp; 
			}
			for(k=0;k<=n+1;k++)
			{
				cout<<v[k]<<" ";
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
 	shellsort(c);
    return 0;
}
