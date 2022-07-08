#include <iostream>
using namespace std;
#define MAX_STACK_SIZE 100

// typedef struct{
//     int key;
// }element;

// element stack[100];

int stack[MAX_STACK_SIZE];
int top = -1;

void push(int item){
    if(top >= MAX_STACK_SIZE){
        cout<<"full"<<endl;
        return;
    }
    else{
        top++;
        stack[top] = item;
    }
}

int pop(){
    if(top == -1){
        cout<<"empty"<<endl;
        return 0;
    }
    else{
        int val = stack[top];
        top--;
        cout<<"top"<<top<<endl;
        return val;
    }
}

int main(){
    int val;
    for(int i = 0; i < 5; i++){
        cin>>val;
        push(val);
    }
    int index = top;
    for(; index >= 0; index--){
        cout<<stack[index]<<" ";
    }
    cout<<endl;
    cout<<"-----"<<endl;
    pop();
    index = top;
    for(; index >= 0; index--){
        cout<<stack[index]<<" ";
    }
    cout<<endl;
    cout<<"-----"<<endl;
    push(100);
    index = top;
    for(; index >= 0; index--){
        cout<<stack[index]<<" ";
    }
    cout<<endl;


}