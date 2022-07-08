#include <iostream>
#include <stdio.h>
using namespace std;

int main(){
    int one[] = {0, 1, 2, 3, 4};
    int i;
    cout<<"Address Contents"<<endl;
    for(i = 0; i < 5; i++){
        printf("%8u%5d\n",one+i, *(one+i));
    }
    cout<<endl;
    return 0;
    int n = 5;
    int *x = (int*)malloc(sizeof(int) * n);
    int *y = (int*)calloc(n, sizeof(int));
    realloc(y, 2*n*sizeof(int));

}