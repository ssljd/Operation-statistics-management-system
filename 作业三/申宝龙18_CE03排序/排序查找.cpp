#include<iostream>
#include<memory>
using namespace std;
typedef char ElementType;
void InsertionSort(ElementType A[], int N)
{
    int j, p;
    ElementType Tmp;
    for (p = 1; p < N; p++) {
        Tmp = A[p];
        for (j = p; j > 0 && A[j - 1] > Tmp; j--)
            A[j] = A[j - 1];
        A[j] = Tmp;
    }
}
void Shellsort(ElementType A[], int N)
{
    int i, j, Increment;
    ElementType Tmp;
    for (Increment = N / 2; Increment > 0; Increment /= 2)
    {
        for (i = Increment; i < N; i++)
        {
            Tmp = A[i];
            for (j = i; j >= Increment; j -= Increment)
                if (Tmp < A[j - Increment])
                    A[j] = A[j - Increment];
                else break;
            A[j] = Tmp;
        }
    }
}
int main()
{
    char  A[][20] = { ¡°while¡±£¬¡±if¡±£¬¡°else¡±£¬¡±do¡±£¬¡°for¡±£¬¡±switch¡±£¬¡°case¡± };;
    InsertionSort(A, 19);
    ElementType c = A[1];
    for (int i = 0; i <20 ; i++)
        cout << A[i];
    char  B[][20] = { ¡°while¡±£¬¡±if¡±£¬¡°else¡±£¬¡±do¡±£¬¡°for¡±£¬¡±switch¡±£¬¡°case¡± };;
    InsertionSort(B, 19);
    ElementType c = B[1];
    for (int i = 0; i < 20; i++)
        cout << B[i];
}