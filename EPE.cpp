#include <stdio.h>
#include <ctype.h>

#define MAXSTACK 100 /* for max size of stack */
#define POSTFIXSIZE 100 /* define max number of charcters in postfix expression */

int stack[MAXSTACK];
int top = -1; 


void push(int item){ //define push operation
    if(top >= MAXSTACK - 1){
        printf("stack over flow");
        return;
    }
    else{
        top = top + 1;
        stack[top] = item;
    }
}

int pop(){ //define pop operation
    int item;
    if(top < 0){
        printf("stack under flow");
    }
    else{
        item = stack[top];
        top = top - 1;
        return item;
    }
    return 0;
}

void EvalPostfix(char postfix[]){
    char ch;
    int val;
    int A, B;
    for(int i = 0; postfix[i] != ')'; i++){ //evaluate postfix expression
        ch = postfix[i];
        if(isdigit(ch)){ //可用於檢查傳遞的字符是否為數字。如果是數字，則返回非零值，否則返回0。例如，對於‘0’到‘9’，它返回非零值，對於其他值則返回零。
            push(ch - '0'); //ch - '0' is used for getting digit rather than ASCII code of digit
        }
        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'){
            A = pop();
            B = pop();
            switch(ch){ //ch is an operator
                case '*':
                    val = B * A;
                    break;
                case '/':
                    val = B / A;
                    break;
                case '+':
                    val = B + A;
                    break;
                case '-':
                    val = B - A;
                    break;
                case '%':
                    val = B % A;
                    break;
            }
            push(val);
        }
    }
    printf(" \n Result of expression evaluation : %d \n", pop());
}

int main(){
    int i;
    char postfix[POSTFIXSIZE];
    printf("Enter postfix expression,press right parenthesis ')' for end expression : ");

    
    for (i = 0; i <= POSTFIXSIZE - 1; i++) {
        scanf("%c", &postfix[i]);
        if(postfix[i] == ')'){
            break;
        }
    }
    EvalPostfix(postfix);

    return 0;
}