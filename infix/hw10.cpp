#include<iostream>
#include<string>
#include <cmath>
using namespace std;

#define MAX 40


char stack[20];
int top = -1;
// Push function here, inserts value in stack and increments stack top by 1


struct Node
{
    char key;
    struct Node *left, *right;
};

void push(char oper){
    if(top == MAX-1){
        cout<<"stack full!";
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
    return 0;
}

string convert(string infix){
    int i = 0;
    string postfix = "";   
    while(infix[i] != '\0'){       
        if(infix[i] >= 'A'&& infix[i] <= 'Z'){
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
    cout<<"The postfix expression: "<<postfix<<endl; //it will print postfix conversion  
    return postfix;
}

struct Node* newNode(char key)
{
    // cout<<key<<endl;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
 
    return node;
}


struct Node* construct(char inorder[], int start, int end, char postorder[], int *pIndex, int pre[], int have){
    
    //base case
    
    if (start > end) {
        // cout<<"kkkk"<<endl;
        return NULL;
    }
    // Consider the next item from the end of a given postorder sequence.
    // This value would be the root node of the subtree formed by the sequence
    // inorder[start, end].
    struct Node* node = newNode(postorder[(*pIndex)--]);
    // cout<<node -> key<<endl;
    // search the current node index in inorder sequence to determine
    // the boundary of the left and right subtree of the current node
    // int i;
    int in =  20;
    int tmp = 1000;
    int pi = *pIndex;
    if(have == 0){
        for (int i = end; i >= start; i--){
            if (inorder[i] == node->key) {
                in = i;
                break;
            }
        }
    }
    else if(have == 1){
        for (int i = end; i >= start; i--){
            if (inorder[i] == node->key) {
                if(tmp > pre[i]){
                    tmp = pre[i];
                    in = i;
                }
            }
        }
    }
    // recursively construct the right subtree
    // node->right= construct(inorder, in + 1, end, postorder, pIndex);
    node -> right= construct(inorder, in + 1, end, postorder, pIndex, pre, have);
    // recursively construct the left subtree
    node -> left = construct(inorder, start, in - 1, postorder, pIndex, pre, have);

    // return the current node
    return node;
}
 
// Construct a binary tree from inorder and postorder traversals.
// This function assumes that the input is valid, i.e., given
// inorder and postorder sequences forming a binary tree.
struct Node* constructTree(char inorder[], char postorder[], int n, int pre[], int have)
{
    // `pIndex` stores the index of the next unprocessed node from the end
    // of the postorder sequence
    // cout<<n<<endl;
    int *pIndex = &n;
    // cout<<*pIndex<<endl;
    return construct(inorder, 0, n, postorder, pIndex, pre, have);
}
//(A/B)*((C+D)-((E-F)+G))
//(A/B)*((C+D)-(E+G))
// (A/B)*((C+D)-((E-F)+G))

void preorderTraversal(struct Node* root){
    if (root == NULL) {
        return;
    }
    cout<<root->key;
    // printf("%c ", root->key);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
    
}
struct Node* queue[MAX];

void addq(int front, int *rear, struct Node* item){  
/* add an item to the queue */
   if (*rear == MAX-1) {
      cout<<"full";
      return;
   }
   queue[++*rear] = item;
}

struct Node* deleteq(int *front, int rear){  
/* return element at the front of the queue */
   if (*front == rear)
      return NULL; /* return error key */
   return queue[++*front];
}


void level_order (struct Node* ptr){
   int front = 0;
   int rear = 0;
   if (!ptr) return;  /* empty tree */
   addq (front, &rear, ptr);
   for (;;) {
      ptr = deleteq (&front, rear);
      if (ptr) {
         printf ("%c", ptr->key);
         if (ptr->left)
            addq (front, &rear,ptr->left);
         if (ptr->right)
            addq (front, &rear,ptr->right);
      }
      else break;
   }
}


int stack2[MAX];
int top2 = -1; 

void push2(int item){ //define push operation
    if(top2 >= MAX - 1){
        printf("stack2 over flow");
        return;
    }
    else{
        top2 = top2 + 1;
        stack2[top2] = item;
    }
}

int pop2(){ //define pop operation
    int item;
    if(top2 < 0){
        printf("stack2 under flow");
    }
    else{
        item = stack2[top2];
        top2 = top2 - 1;
        return item;
    }
    return 0;
}

void EvalPostfix(int postfix[], int n){
    char ch;
    int val;
    int A, B;
    for(int i = 0; i < n; i++){ //evaluate postfix expression
        ch = postfix[i];
        // if(isdigit(postfix[i])){ //可用於檢查傳遞的字符是否為數字。如果是數字，則返回非零值，否則返回0。例如，對於‘0’到‘9’，它返回非零值，對於其他值則返回零。
        //      //ch - '0' is used for getting digit rather than ASCII code of digit
        // }
        
        if(ch == '+' || ch == '-' || ch == '*' || ch == '/' ){
            // cout<<ch;
            A = pop2();
            B = pop2();
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
            push2(val);
        }
        else{
            // cout<<postfix[i]<<" ";
            push2(postfix[i]);
        }
    }
    printf("Result of expression evaluation : %d \n", pop2());
}


int main(){
    int cont;
    string infix, postfix;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"                    Data Structure Homework 10"<<endl;;
    cout<<"                     40947007S 資工113 張欀齡"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"Enter the infix expression : "; //enter the expression
    getline(cin, infix);
    // cin>>infix;
    int number = 0;
    int math = 0;
    int left = 0;
    int right = 0;
    int have = 0;
    int F = 0;
    int space = 0;
    for(int i = 0; i < infix.length(); i++){
        int a = infix[i];
        if(a == 32){
            space = 1;
        }
    }
    for(int i = 0; i < infix.length(); i++){
        if(infix[i] == '+' ||infix[i] == '-' ||infix[i] == '*' ||infix[i] == '/' ){
            math++;
        }
        else if(infix[i] != '(' && infix[i] != ')'){
            number++;
        }
        else if(infix[i] == '(') left++;
        else if(infix[i] == ')') right++;
    }
    for(int i = 0; i < infix.length(); i++){
        if(infix[i] != '(' && infix[i] != ')' && infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && (infix[i] < 'A' || infix[i] > 'Z')){
            F = 1;
        }
    }
    if(space == 1){
        cout<<"不允許有空白字元"<<endl;
        return 0;
    }
    if( F == 1){
        cout<<"輸入了不允許的字元"<<endl;
        return 0;
    }
    if(infix.length() > 20){
        cout<<"長度不能大於20"<<endl;
        return 0;
    }
    if(math+1 != number){
        // cout<<math<<number<<endl;
        cout<<"運算子數目不等於運算元數目-1"<<endl;
        return 0;
    }
    if(right != left){
        cout<<"左右括弧不對稱"<<endl;
        return 0;
    }
    if(left != 0 || right != 0){
        have = 1;
    }
    postfix = convert(infix);
    int n = postfix.length();
    int sum = 1;
    int preI = 0;
    char *inorder = (char *)malloc(sizeof(char)*n);
    char *postorder = (char *)malloc(sizeof(char)*n);
    int *pre = (int *)malloc(sizeof(int)*n);
    for(int i = 0; i < infix.length(); i++){
        if(infix[i] == '('){
            sum++;
        }
        else if(infix[i] != ')'){
            pre[preI] = sum;
            preI++;
        }
    }
    int inI = 0;
    for(int i = 0; i < infix.length(); i++){
        if(infix[i] != '(' && infix[i] != ')'){
            inorder[inI] = infix[i];
            inI++;
        }
    }
    // for(int i = 0; i < n; i++){
    //     cout<<inorder[i];
    // }
    // cout<<endl;
    
    for(int i = 0; i < n; i++){
        postorder[i] = postfix[i];
    }
    // cout<<n<<endl;
    // for(int i = 0; i < n; i++){
    //     cout<<postorder[i];
    // }
    // cout<<endl;
    struct Node* root = constructTree(inorder, postorder, n - 1, pre, have);
    // cout<<root->key<<endl;
    cout<<"The prefix expression: ";
    preorderTraversal(root);
    cout<<endl;
    cout<<"The level-order of expression tree: ";
    level_order(root);
    cout<<endl;
    int num[100] = {0};
    char esc;
    int check;
    do{
        cout<<"一個一個輸入對應之數值："<<endl;
        for(int i = 0; i < postfix.length(); i++){
            if(postfix[i] != '+' && postfix[i] != '-' && postfix[i] != '*' && postfix[i] != '/' ){
                cout<<postfix[i]<<": ";
                int n;
                cin>>n;
                num[i] = n;
            }
            else{
                num[i] = postfix[i];
            }
        }
        EvalPostfix(num, postfix.length());
        cout<<"輸入Esc鍵結束程式，還未要結束按任意鍵繼續......"<<endl;
        cin>>esc;
        check = esc;
    }while(check != 27);

    return 0;
}
