// C++ Program infix to postfix expression using stack (array) in data structure
#include<iostream>
#include<string>
#define MAX 20
using namespace std;

char stack[20];
int top = -1;
// Push function here, inserts value in stack and increments stack top by 1

void push(char oper){
    if(top == MAX-1){
        cout<<"stackfull!!!!";
    }
    else{
        top++;
        stack[top] = oper;
    }
}
// Function to remove an item from stack.  It decreases top by 1
char pop(){
    char ch;
    if(top == -1){
        cout<<"stackempty!!!!";
    }
    else{
        ch = stack[top];
        stack[top] = '\0';
        top--;
        return(ch);
    }
    return 0;
}

int priority(char alpha){
    if(alpha == '+' || alpha =='-'){
        return(1);
    }
    if(alpha == '*' || alpha =='/'){
        return(2);
    }
    if(alpha == '$'){
        return(3);
    }
    return 0;
}
string convert(string infix){
    int i = 0;
    string postfix = "";   
    while(infix[i] != '\0'){       
        if(infix[i] >= 'a' && infix[i] <= 'z'|| infix[i] >= 'A'&& infix[i] <= 'Z'){
            postfix.insert(postfix.end(),infix[i]);
            i++;
        }       
        else if(infix[i] == '('){
            push(infix[i]);
            i++;
        }        
        else if(infix[i] == ')'){
            while(stack[top] != '('){               
                postfix.insert(postfix.end(),pop());
            }
            pop();//拿掉左括弧
            i++;
        }
        else{
            if(top == -1){
                push(infix[i]);
                i++;
            }
            else if( priority(infix[i]) <= priority(stack[top])){
                postfix.insert(postfix.end(),pop());
                while(priority(stack[top]) == priority(infix[i])){
                    postfix.insert(postfix.end(),pop());
                    if(top < 0) {
                        break;
                    }
                }
                push(infix[i]);
                i++;
            }
            else if(priority(infix[i]) > priority(stack[top])){
                push(infix[i]);
                i++;
            }
        }
    }

    while(top != -1){
        postfix.insert(postfix.end(),pop());
    }
    cout<<"The converted postfix string is : "<<postfix<<endl; //it will print postfix conversion  
    return postfix;
}

int main(){
    int cont;
    string infix, postfix;
    cout<<"Enter the infix expression : "; //enter the expression
    cin>>infix;
    postfix = convert(infix);
    return 0;
}