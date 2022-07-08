#include <iostream>
#include <time.h>
#include <stdio.h>
#include <math.h>
using namespace std;

//1-13 0
//14-26 1
//27-39 2
//40-52 3

typedef struct card* cardPointer;
typedef struct card{
    int num;
    int color;
    cardPointer link;
}card;
cardPointer S, H, D, C;
cardPointer S2, H2, D2, C2;
cardPointer firstC, firstD, firstH, firstS;
cardPointer firstC2, firstD2, firstH2, firstS2;
int check[52] = {0};
int player;

int length (cardPointer head){  
	int size = 0;
    while(head) {
         head = head -> link;
        size++;
    }
    return size;
}

void deleteL (cardPointer *first, cardPointer trail, cardPointer x){  
/* delete x from the list, trail is the preceding 
      node, first is the front of the list, */
    if(trail)
    	trail->link = x->link;
    else{ /* delete first node*/
    	*first = (*first) -> link; 
    }
    free(x);
}

void func5(cardPointer* first, int* choNum){
    cardPointer tmp = *first;
    cardPointer tmp2 = *first;
    cardPointer trail, x;
    trail = *first;
    int findMax = 0;
    int findMin = 0;
    int ans = 0;
    int min = 0;
    int preD = 1000;
    ans = *choNum;
    min = *choNum;
    for(; tmp != NULL; tmp = tmp -> link){
        if(tmp -> num > *choNum && abs((tmp -> num) - *choNum) < preD){
            ans = tmp -> num;
            preD = abs((tmp -> num) - *choNum);
            x = tmp;
            findMax = 1;
        }
    }
    if(findMax == 0){
        for(; tmp2 != NULL; tmp2 = tmp2 -> link){
            if(tmp2 -> num < min){
                min = tmp2 -> num;
                findMin = 1;
            }
        }
    }
    if(findMin == 1){
            printf("%c", (*first) -> color);
            cout<<min<<endl;
    }
    else if(findMax == 0 && findMin == 0){
        cout<<"該花色只有這一張牌：";
        printf("%c", (*first) -> color);
        cout<<(*first) -> num<<endl;
    }
    else{
        while(1){
            if(x == *first){
                trail = NULL;
                break;
            }
            if(trail -> link == x){
                break;
            }
            trail = trail -> link;
        }
        deleteL (first, trail, x);
        printf("%c", (*first) -> color);
        cout<<ans<<endl;
    }
}




void print(cardPointer first){
    cardPointer head = first;
    for(; head != NULL; head = head -> link){
        printf("%c",head -> color);
        cout<<head -> num<<" -> ";
        if(!(head -> link)){
            cout<<"NULL";
        }
    }
    cout<<endl;
}


cardPointer bubbleSortList(cardPointer *head){
    cardPointer ace = (*head);
    for(; ace != NULL; ace = ace -> link){
        if(ace -> num == 1){
            ace -> num = 14;
        }
    }
    // bubble sort
    cardPointer tail = (*head);
    cardPointer tmp = (*head);
    cardPointer curr = (*head);
    cardPointer prev = (*head);
    
    // get Linked list size first
    int size = 0;
    while(tail) {
        tail = tail -> link;
        size++;
    }
    
    for(int i = size; i > 0; i--) {
        curr = (*head);
        prev = (*head);
        for(int j = 0; j < i-1 && curr -> link; j++) {
            // Compares two elements, and swaps if current is bigger than next
            if(curr -> num > curr -> link -> num) {
                tmp = curr -> link;
                curr -> link = tmp -> link;
                tmp -> link = curr;
                // In linked list, swap has two case. In head or not.
                if(curr == (*head)) {
                    (*head) = tmp;
                    prev = tmp;
                } else {
                    prev -> link = tmp;
                    prev = prev -> link;
                }
            } else {
                curr = curr -> link;
                if(j!=0) prev = prev -> link;
            }
        }
    }
    cardPointer ace2 = (*head);
    for(; ace2 != NULL; ace2 = ace2 -> link){
        if(ace2 -> num == 14){
            ace2 -> num = 1;
        }
    }
    return (*head);
}

cardPointer invert (cardPointer *lead){   
/* invert the list pointed to by lead */
   cardPointer  middle, trail;
   middle = NULL;
   while (*lead) {
	trail = middle;
	middle = (*lead);
	(*lead) = (*lead)->link;
	middle->link = trail;
   }
   return middle;
}
int fc = 0, fd = 0, fh = 0, fs = 0;
void add(cardPointer *firstC, cardPointer *firstD, cardPointer *firstH, cardPointer *firstS, cardPointer *C, cardPointer *D, cardPointer *H, cardPointer *S, int n){
    // int n;
    // cout<<"輸入正整數n：";
    // cin>>n;
    int randNum;
    // int fc = 0, fd = 0, fh = 0, fs = 0;
    while(n--){
        randNum = (rand() % 52);
        while(check[randNum] == 1){
            randNum = (rand() % 52);
            // cout<<"rand = "<<randNum<<endl;
        }
        check[randNum] = 1;
        randNum++;
        // cout<<"check"<<randNum<<"="<<check[randNum-1]<<endl;
        // cout<<randNum;
        int cardC = randNum / 13;
        int cardN = randNum % 13;
        if(cardN == 0){
            cardN = 13;
            cardC--;
        }
        // cout<<"->"<<cardC<<endl;
        
        //0就是C梅花
        //1就是D方塊
        //2就是H愛心
        //3就是S黑桃
        cardPointer tmp = (cardPointer)malloc(sizeof(*tmp));
        tmp -> num = cardN;
        if(cardC == 0) tmp -> color = 67;
        if(cardC == 1) tmp -> color = 68;
        if(cardC == 2) tmp -> color = 72;
        if(cardC == 3) tmp -> color = 83;
        // tmp -> num = cardN;
        
        if(cardC == 0){ 
            if(*C) (*C)->link = tmp;
            (*C) = tmp;
            if(fc == 0){
                (*firstC) = (*C);
                fc = 1;
            }
        }
        else if(cardC == 1){
            if(*D) (*D)->link = tmp;
            (*D) = tmp;
            if(fd == 0){
                (*firstD) = (*D);
                fd = 1;
            }
        }
        else if(cardC == 2){
            if(*H) (*H)->link = tmp;
            (*H) = tmp;
            if(fh == 0){
                (*firstH) = (*H);
                fh = 1;
            }
        }
        else if(cardC == 3){
            if(*S) (*S)->link = tmp;
            (*S) = tmp;
            if(fs == 0){
                (*firstS) = (*S);
                fs = 1;
            }
        }
    }
    cout<<"加入完畢！"<<endl;
}


void menu(){
    cout<<"\033[33m------------------------------主選單------------------------------\033[m"<<endl;
    cout<<"\033[33m(1)\033[m輸入一個正整數 n，隨機產生 n 張牌加到資料中，表示發給這個人 n 張牌"<<endl;
    cout<<"\033[33m(2)\033[m選擇某一花色，依發牌拿到的順序一一列出"<<endl;
    cout<<"\033[33m(3)\033[m選擇某一花色，依發牌拿到的相反順序一一列出"<<endl;
    cout<<"\033[33m(4)\033[m選擇某一花色，依牌色大小由小而大一一列出"<<endl;
    cout<<"\033[33m(5)\033[m刪除一張牌"<<endl;
    cout<<"\033[33m(6)\033[m輸入並記錄另一個人的牌，並可提供上述5項功能選項"<<endl;
    cout<<"\033[33m(7)\033[m結束"<<endl;
    cout<<"\033[33m------------------------------------------------------------------\033[m"<<endl;
}

int main(){
    cout<<"\033[33m------------------------------------------------------------------\033[m"<<endl;
    cout<<"                     Data Structure Homework 7"<<endl;;
    cout<<"                     40947007S 資工113 張欀齡"<<endl;
    int choose = 0;
    while(1){
        menu();
        cout<<"請輸入選項(1-7)：";
        cin>>choose;
        // cardPointer firstC, firstD, firstH, firstS;
        srand(time(NULL));
        if(choose == 1){
            cout<<"請選擇是Player 1 還是Player 2 [輸入方式] 1 or 2：";
            cin>>player;
            if(player == 1){
                int n;
                cout<<"輸入正整數n：";
                cin>>n;
                add(&firstC, &firstD, &firstH, &firstS, &C, &D, &H, &S, n);
            }
            else if(player == 2){
                int n;
                cout<<"輸入正整數n：";
                cin>>n;
                add(&firstC2, &firstD2, &firstH2, &firstS2, &C2, &D2, &H2, &S2, n);
            }
        }
        else if(choose == 2){
            cout<<"請選擇是Player 1 還是Player 2 [輸入方式] 1 or 2：";
            cin>>player;
            if(player == 1){
                int choCol;
                cout<<"請輸入花色 [輸入方式](1)C (2)D (3)H (4)S : ";
                cin>>choCol;
                if(choCol == 1){
                    cardPointer tmp = firstC;
                    if(!tmp) cout<<"沒有這個花色的牌"<<endl;
                    else print(tmp);
                }
                else if(choCol == 2){
                    cardPointer tmp = firstD;
                    if(!tmp) cout<<"沒有這個花色的牌"<<endl;
                    else print(tmp);
                }
                else if(choCol == 3){
                    cardPointer tmp = firstH;
                    if(!tmp) cout<<"沒有這個花色的牌"<<endl;
                    else print(tmp);
                }
                else if(choCol == 4){
                    cardPointer tmp = firstS;
                    if(!tmp) cout<<"沒有這個花色的牌"<<endl;
                    else print(tmp);
                }
            }
            else if(player == 2){
                int choCol;
                cout<<"請輸入花色 [輸入方式](1)C (2)D (3)H (4)S : ";
                cin>>choCol;
                if(choCol == 1){
                    cardPointer tmp = firstC2;
                    if(!tmp) cout<<"沒有這個花色的牌"<<endl;
                    else print(tmp);
                }
                else if(choCol == 2){
                    cardPointer tmp = firstD2;
                    if(!tmp) cout<<"沒有這個花色的牌"<<endl;
                    else print(tmp);
                }
                else if(choCol == 3){
                    cardPointer tmp = firstH2;
                    if(!tmp) cout<<"沒有這個花色的牌"<<endl;
                    else print(tmp);
                }
                else if(choCol == 4){
                    cardPointer tmp = firstS2;
                    if(!tmp) cout<<"沒有這個花色的牌"<<endl;
                    else print(tmp);
                }
            }  
        }
        else if(choose == 3){
            cout<<"請選擇是Player 1 還是Player 2 [輸入方式] 1 or 2：";
            cin>>player;
            if(player == 1){
                int choCol;
                cardPointer inv;
                cout<<"請輸入花色 [輸入方式](1)C (2)D (3)H (4)S : ";
                cin>>choCol;
                if(choCol == 1){
                    firstC = invert(&firstC);
                    print(firstC);
                }
                else if(choCol == 2){
                    // inv = invert(&firstD);
                    // print(inv);
                    firstD = invert(&firstD);
                    print(firstD);
                }
                else if(choCol == 3){
                    // inv = invert(&firstH);
                    // print(inv);
                    firstH = invert(&firstH);
                    print(firstH);
                }
                else if(choCol == 4){
                    // inv = invert(&firstS);
                    // print(inv);
                    firstS = invert(&firstS);
                    print(firstS);
                }
            }
            else if(player == 2){
                int choCol;
                cardPointer inv;
                cout<<"請輸入花色 [輸入方式](1)C (2)D (3)H (4)S : ";
                cin>>choCol;
                if(choCol == 1){
                    firstC2 = invert(&firstC2);
                    print(firstC2);
                }
                else if(choCol == 2){
                    // inv = invert(&firstD);
                    // print(inv);
                    firstD2 = invert(&firstD2);
                    print(firstD2);
                }
                else if(choCol == 3){
                    // inv = invert(&firstH);
                    // print(inv);
                    firstH2 = invert(&firstH2);
                    print(firstH2);
                }
                else if(choCol == 4){
                    // inv = invert(&firstS);
                    // print(inv);
                    firstS2 = invert(&firstS2);
                    print(firstS2);
                }
            }
        }
        else if(choose == 4){
            cout<<"請選擇是Player 1 還是Player 2 [輸入方式] 1 or 2：";
            cin>>player;
            if(player == 1){
                int choCol;
                cout<<"請輸入花色 [輸入方式](1)C (2)D (3)H (4)S : ";
                cin>>choCol;
                if(choCol == 1){
                    cardPointer tmp = bubbleSortList(&firstC);
                    firstC = tmp;
                    print(tmp);
                }
                else if(choCol == 2){
                    cardPointer tmp = bubbleSortList(&firstD);
                    firstD = tmp;
                    print(tmp);
                }
                else if(choCol == 3){
                    cardPointer tmp = bubbleSortList(&firstH);
                    firstH = tmp;
                    print(tmp);
                }
                else if(choCol == 4){
                    cardPointer tmp = bubbleSortList(&firstS);
                    firstS = tmp;
                    print(tmp);
                }
            }
            else if(player == 2){
                int choCol;
                cout<<"請輸入花色 [輸入方式](1)C (2)D (3)H (4)S : ";
                cin>>choCol;
                if(choCol == 1){
                    cardPointer tmp = bubbleSortList(&firstC2);
                    firstC2 = tmp;
                    print(tmp);
                }
                else if(choCol == 2){
                    cardPointer tmp = bubbleSortList(&firstD2);
                    firstD2 = tmp;
                    print(tmp);
                }
                else if(choCol == 3){
                    cardPointer tmp = bubbleSortList(&firstH2);
                    firstH2 = tmp;
                    print(tmp);
                }
                else if(choCol == 4){
                    cardPointer tmp = bubbleSortList(&firstS2);
                    firstS2 = tmp;
                    print(tmp);
                }
            }
        }
        else if(choose == 5){
            cout<<"請選擇是Player 1 還是Player 2 [輸入方式] 1 or 2：";
            cin>>player;
            if(player == 1){
                int choCol;
                int choNum;
                cout<<"請輸入花色 [輸入方式](1)C (2)D (3)H (4)S : ";
                cin>>choCol;
                cout<<"請輸入大小 [輸入方式]數字 1~13 : ";
                cin>>choNum;
                if(choCol == 1) func5(&firstC, &choNum);
                else if(choCol == 2) func5(&firstD, &choNum);
                else if(choCol == 3) func5(&firstH, &choNum);
                else if(choCol == 4) func5(&firstS, &choNum);
                else cout<<"沒有這個花色"<<endl;
            }
            else if(player == 2){
                int choCol;
                int choNum;
                cout<<"請輸入花色 [輸入方式](1)C (2)D (3)H (4)S : ";
                cin>>choCol;
                cout<<"請輸入大小 [輸入方式]數字 1~13 : ";
                cin>>choNum;
                if(choCol == 1) func5(&firstC, &choNum);
                else if(choCol == 2) func5(&firstD, &choNum);
                else if(choCol == 3) func5(&firstH, &choNum);
                else if(choCol == 4) func5(&firstS, &choNum);
                else cout<<"沒有這個花色"<<endl;
            }
        }
        else if(choose == 6){
            cout<<"Player 2 的各個功能已直接在各個功能讓使用者選擇"<<endl;
        }
        else if(choose == 7){
            cout<<"程式結束"<<endl;
            break;
        }
        else{
            cout<<"沒有這個選項"<<endl;
        }
    }
    return 0;
}