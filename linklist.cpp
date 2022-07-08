// #include <iostream>
// #define IS_EMPTY(first) (!(first))
// using namespace std;

// //宣告
// typedef struct list_node *list_pointer;
// typedef struct list_node{
//     char data[4];
//     list_pointer link;
// };

// list_pointer first = NULL;

// //create a linklist with two nodes
// list_pointer creat(){
//     list_pointer first, second;
//     first = (list_pointer)malloc(sizeof(list_node));
//     second = (list_pointer)malloc(sizeof(list_node));
//     second -> link = NULL;
//     second -> data = 20;
//     first -> data = 10;
//     first -> link = second;
//     return first;
// }

// //insertion
// void insert(list_pointer *first, list_pointer x){
//     list_pointer temp;
//     malloc(temp, sizeof(list_node));
//     temp -> data = 50;
//     if(*first){
//         temp -> link = x -> link;
//         x -> link = temp;
//     }
//     else{//if empty list
//         temp -> link = NULL;
//         *first = temp;
//     }
// }

// //delete
// void delete_(list_pointer first, list_pointer trail, list_pointer x){
//     if(trail){
//         trail -> link = x -> link;
//     }
//     else{
//         first = first -> link;
//     }
//     free(x);
// }


#include <iostream>
using namespace std;

typedef struct list_node *list_pointer;
typedef struct list_node{
    int data;
    list_pointer link;
    // struct list_node *nest;
}node;


void insert(list_pointer *first, int val){
    list_pointer temp = (list_pointer)malloc(sizeof(list_node));
    temp -> data = val;
    temp -> link = NULL;
    if(*first == NULL){
        *first = temp;
        return;
    }
    else{
        list_pointer current;
        current = *first;
        while(current -> link != NULL){
            current = current -> link;
        }
        current -> link = temp;
        return;
    }
}

void print_list(list_pointer node){
    while(node != NULL){
        printf("%d ",node -> data);
        node = node -> link;
    }
    printf("\n");
}

void free_list(list_pointer node){
    list_pointer current, temp;
    current = node;
    while(current != NULL){
        temp = current;
        current = current -> link;
        free(temp);
    }
}

int main(){
    list_pointer first = NULL;
    insert(&first, 5);
    insert(&first, 128);
    insert(&first, 42);

    print_list(first);
    free_list(first);


    return 0;
}