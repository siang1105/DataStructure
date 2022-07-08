#include <iostream>
using namespace std;
#define MAX_QUEUE_SIZE 100

typedef struct{
    int key;
}element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void addq(element item){
    if(rear == MAX_QUEUE_SIZE){
        cout<<"is full"<<endl;
        return;
    }
    rear++;
    queue[rear] = item;
}

element deleteq(){
    if(front == rear){
        cout<<"empty"<<endl;
    }
    front++;
    cout<<"front = "<<front<<endl;
    return queue[front];
}

int main(){
    int index;
    element val;
    for(int i = 0; i < 5; i++){
        cin>>val.key;
        addq(val);
    }

    // int index = rear;
    for(index = front+1; index <= rear; index++){
        cout<<queue[index].key<<" ";
    }
    cout<<endl;
    cout<<"-----"<<endl;
    deleteq();
    // index = rear;
    for(index = front+1; index <= rear; index++){
        cout<<queue[index].key<<" ";
    }
    cout<<endl;
    cout<<"-----"<<endl;
    val.key = 6;
    addq(val);
    for(index = front+1; index <= rear; index++){
        cout<<queue[index].key<<" ";
    }
    cout<<endl;
    cout<<"-----"<<endl;
}

//--------------------------------------------------------------------------------
//circular queue
// #include <iostream>
// using namespace std;
// #define MAX_QUEUE_SIZE 100

// typedef struct{
//     int key;
// }element;

// element queue[MAX_QUEUE_SIZE];
// int rear = 0;
// int front = 0;

// void addq(element item){
//     rear = (rear+1) % MAX_QUEUE_SIZE;
//     if(front == rear){
//         cout<<"is full"<<endl;
//         return;
//     }
//     queue[rear] = item;
// }

// element deleteq(){
//     if(front == rear){
//         cout<<"empty"<<endl;
//     }
//     front = (front+1) % MAX_QUEUE_SIZE;
//     cout<<"front = "<<front<<endl;
//     return queue[front];
// }

// int main(){
//     int index;
//     element val;
//     for(int i = 0; i < 5; i++){
//         cin>>val.key;
//         addq(val);
//     }

//     // int index = rear;
//     for(index = front+1; index <= rear; index++){
//         cout<<queue[index].key<<" ";
//     }
//     cout<<endl;
//     cout<<"-----"<<endl;
//     deleteq();
//     // index = rear;
//     for(index = front+1; index <= rear; index++){
//         cout<<queue[index].key<<" ";
//     }
//     cout<<endl;
//     cout<<"-----"<<endl;
//     val.key = 6;
//     addq(val);
//     for(index = front+1; index <= rear; index++){
//         cout<<queue[index].key<<" ";
//     }
//     cout<<endl;
//     cout<<"-----"<<endl;
// }