#include <iostream>
using namespace std;
#define MAX_STACK_SIZE 100

typedef struct{
    short int vert;
    short int horiz;
}offsets;

typedef struct {
    short int row;
    short int col;
    short int dir;
}element;

element stack[MAX_STACK_SIZE];
// offsets move[8];
// element stack[MAX_STACK_SIZE];
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

int maze[]
int main(){
    offsets move[8];
    move[0].vert = -1, move[0].horiz = 0;
    move[1].vert = -1, move[0].horiz = 1;
    move[2].vert = 0, move[0].horiz = 1;
    move[3].vert = 1, move[0].horiz = 1;
    move[4].vert = 1, move[0].horiz = 0;
    move[5].vert = 1, move[0].horiz = -1;
    move[6].vert = 0, move[0].horiz = -1;
    move[7].vert = -1, move[0].horiz = -1;


}
