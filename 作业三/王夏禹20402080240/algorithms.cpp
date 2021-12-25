//
//  algorithms.cpp
//  Sort comprehensive experiment
//
//  Created by 王夏禹 on 2021/12/5.
//

#include "algorithms.hpp"




void InsertSort(char R[][20],int n)
{
    int i,j;//i是进行推进，j负责i之前的
    char temp[1][20];
    for(i=1;i<n;i++)
    {
        for(int p=0;p<20;p++)//temp为标量
        {
            temp[0][p]=R[i][p];
        }
        j=i-1;//j表示的位置是标量前一位的位置
        while(j>=0&&(temp[0][0]<R[j][0]))//标量小于前一位数
        {
            for(int p=0;p<20;p++)//标量和前一位数交换位置
            {
                R[j+1][p]=R[j][p];
            }
            --j;//标量前移，继续比较
        }
        for(int p=0;p<20;p++)//最后停止的位置赋值为标量
        {
            R[j+1][p]=temp[0][p];
        }
    }
    
}

void SelectSort(char R[][20],int n)
{
    int i,j,k;
    char temp[1][20];
    for(i=0;i<n;i++)
    {
        k=i;//从0开始，每次循环找到一个最小数，遍历范围缩小
        for(j=i+1;j<n;j++)
        {
            if(R[k][0]>R[j][0])//j是遍历指针，k是j之后的标量指针负责找到最小的数
            {
                k=j;
            }
            
        }
        //让最小的数与序列的第一个关键字换一下位置
        for(int p=0;p<20;p++)
        {
            temp[0][p]=R[i][p];
        }
        for(int p=0;p<20;p++)
        {
            R[i][p]=R[k][p];
        }
        for(int p=0;p<20;p++)
        {
            R[k][p]=temp[0][p];
        }
    }
}

void QuickSort(char R[][20],int low,int high)
//sorted from R[low] to R[high]
{
    char temp[1][20];
    int i=low,j=high;
    if(low<high)
    {
        for(int p=0;p<20;p++)//temp=first key in the array
        {
            temp[0][p]=R[low][p];
        }
        
        while(i<j)
        {
            //j从队尾开始向前遍历
            while(j>i&&R[j][0]>=temp[0][0])//j从右往左扫描，找到一个小于temp的关键字
            {
                j--;
            }
            if(i<j)
            {
                for(int p=0;p<20;p++)//i的位置放入j的数
                {
                    R[i][p]=R[j][p];
                }
                i++;//i向后移一位
            }
            //i开始从队前向后遍历
            while(i<j&&R[i][0]<temp[0][0])//i从左向右扫描，找到一个大于temp的关键字
            {
                i++;
            }
            if(i<j)
            {
                for(int p=0;p<20;p++)//j的位置放入i的数
                {
                    R[j][p]=R[i][p];
                }
                j--;//j左移一位
            }
        }
        //此时i=j
        for(int p=0;p<20;p++)//在中轴位置填入temp
        {
            R[i][p]=temp[0][p];
        }
        QuickSort(R, low, i-1);//递归地对temp左边的关键字进行排序
        QuickSort(R, i+1, high);//递归地对temp右边的关键字进行排序
    }
}
