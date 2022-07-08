#include <iostream>
#include <vector>
using namespace std;
#define MAX_TERMS 200

typedef struct{
    float coef;
    int exp;
}polynomial;

polynomial terms_p[MAX_TERMS];
polynomial terms[MAX_TERMS];

vector<int> p2;//定义除式
vector<int> p1;//定义被除式
vector<int> k;

int avail = 0;
int sa,fa,sb,fb,sd,fd,se,fe;
int tmp = 1;

void attach(float coefficient, int exponent){
    /* add a new term to the polynomial */
    if(avail >= MAX_TERMS){
        fprintf(stderr, "too many terms in the polynomials\n");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail].exp = exponent;
    avail++;
}

int compare(int expa, int expb){
    if(expb > expa){
        return -1;
    }
    else if(expa == expb){
        return 0;
    }
    else{
        return 1;
    }
}

void padd(){
    sd = avail;
    float coefficient;
    while(sa <= fa && sb <= fb){
        switch (compare(terms[sa].exp, terms[sb].exp)){
        case -1://a exp < b
            attach(terms[sb].coef, terms[sb].exp);
            sb++;
            break;
        case 0://equal exp
            coefficient = terms[sa].coef + terms[sb].coef;
            if(coefficient){
                attach(coefficient, terms[sa].exp);
            }
            sa++;
            sb++;
            break;
        case 1://a exp > b
            attach(terms[sa].coef, terms[sa].exp);
            sa++;
            break;
        default:
            break;
        }
    }
    /* add in remaining terms of A(x)*/
    for(; sa <= fa; sa++){
        attach(terms[sa].coef, terms[sa].exp);
    }
    /* add in remaining terms of B(x)*/
    for(; sb <= fb; sb++){
        attach(terms[sb].coef, terms[sb].exp);
    }
    fd = avail - 1;
}

void sub(){
    sd = avail;
    float coefficient;
    while(sa <= fa && sb <= fb){
        switch (compare(terms[sa].exp, terms[sb].exp)){
        case -1:
            attach(-terms[sb].coef, terms[sb].exp);
            sb++;
            break;
        case 0:
            coefficient = terms[sa].coef - terms[sb].coef;
            if(coefficient){
                attach(coefficient, terms[sa].exp);
            }
            sa++;
            sb++;
            break;
        case 1:
            attach(terms[sa].coef, terms[sa].exp);
            sa++;
            break;
        default:
            break;
        }
    }
    /* add in remaining terms of A(x)*/
    for(; sa <= fa; sa++){
        attach(terms[sa].coef, terms[sa].exp);
    }
    /* add in remaining terms of B(x)*/
    for(; sb <= fb; sb++){
        attach(-terms[sb].coef, terms[sb].exp);
    }
    fd = avail - 1;
}


void mul(){
    sd = avail;
    while(sa <= fa){
        for(int i = sb; i <= fb; i++){
            terms[avail].coef = terms[sa].coef * terms[i].coef;
            terms[avail].exp = terms[sa].exp + terms[i].exp;
            avail++;
        }
        sa++;
    }
    fd = avail - 1;
    se = avail;
    int maxE = terms[sd].exp;
    int maxEI = sd;
    terms[avail].exp = terms[maxEI].exp;
    terms[avail].coef = terms[maxEI].coef;
    avail++;    
    sd++;
    while(sd <= fd){
        maxE = terms[sd].exp;
        maxEI = sd;
        for(int i = sd; i <= fd; i++){
            if(maxE < terms[i].exp){
                maxE = terms[i].exp;
                maxEI = i;
            }
        }
        if(terms[maxEI].exp == terms[avail-1].exp){
            terms[avail-1].coef += terms[maxEI].coef;
            sd++;
        }
        else{
            terms[avail].exp = terms[maxEI].exp;
            terms[avail].coef = terms[maxEI].coef;
            avail++;    
            sd++;
        }
    }
    fe = avail - 1;
}

void div(){
    int n;
    int m;
    n = p1.size() - 1;
    m = p2.size() - 1;
    if(n < m){
        cout<<"商式：0"<<endl;
        cout<<"餘式：";
        for(int c = n-m+1; c <= n; c++){
            if(p1[c] != 0 && c != n){
                cout << p1[c] << "x^" << n - c << " + ";
            }
            if(c == n){
                cout << p1[c];
            }
        }
        cout<<endl;
    }
    else{
        int temp = 0;
        int t = 0;
        for(int i = 0; i <= n-m; i++){
            temp = -(p1[i] / p2[0]);
            k.push_back(temp);
            int t = 0;
            for(int j = i; j <= i+m; j++){
                p1[j] = p1[j] + k[i] * p2[t];
                t++;
            }
        }
        int num = k.size();
        int c = 0;
        cout<<"商式：";
        for(; c < num; c++){
            if(k[c] != 0 && c != n-m){
                cout<< -k[c] << "x^"<< n-m-c << " + ";
            }
            if(c == n-m){
                cout<< -k[c];
            }
        }
        cout<<endl;
        cout<<"餘式：";
        for(c = n-m+1; c <= n; c++){
            if(p1[c] != 0 && c != n){
                cout << p1[c] << "x^" << n - c << " + ";
            }
            if(c == n){
                cout << p1[c];
            }
        }
        cout<<endl;
    }
}

int main(){
    cout<<"\033[33m------------------------------------------------------------------\033[m"<<endl;
    cout<<"                     Data Structure Homework 3"<<endl;;
    cout<<"                     40947007S 資工113 張欀齡"<<endl;
    cout<<"                     輸入多項式時次方由大到小"<<endl;
    int choose = 0;

    while(1){
        cout<<"\033[33m------------------------------主選單------------------------------\033[m"<<endl;
        cout<<"\033[33m(1)\033[m輸入一個 X 的多項式 P"<<endl;
        cout<<"\033[33m(2)\033[m由螢幕顯示多項式 P 的內容"<<endl;
        cout<<"\033[33m(3)\033[m指定多項式 P 之指數次方，顯示該項的係數值"<<endl;
        cout<<"\033[33m(4)\033[m可新增/移除多項式 P 的非零項"<<endl;
        cout<<"\033[33m(5)\033[m讀入兩個多項式 P1 及 P2，做 P1 及 P2 的相加，並顯示 P1+P2 的結果"<<endl;
        cout<<"\033[33m(6)\033[m讀入兩個多項式 P1 及 P2，做 P1 及 P2 的相減，並顯示 P1-P2 的結果"<<endl;
        cout<<"\033[33m(7)\033[m讀入兩個多項式 P1 及 P2，做 P1 及 P2 的相乘，並顯示 P1*P2 的結果"<<endl;
        cout<<"\033[33m(8)\033[m結束"<<endl;
        cout<<"\033[33m(9)\033[m讀入兩個多項式 P1 及 P2，做 P1 及 P2 的相除，並顯示 P1除P2 的商及餘數[額外功能]"<<endl;
        cout<<"\033[33m------------------------------------------------------------------\033[m"<<endl;
        cout<<"請輸入選項(1-9)：";
        cin>>choose;
        int p_index = 0;
        int sp = p_index;
        int fp;
        int sn;
        if(choose == 1){
            cout<<"輸入P(x)的多項式 / [輸入方式]：係數 次方 / 輸入結束請輸入：0 0"<<endl;
            while(1){
                cin>>terms_p[p_index].coef>>terms_p[p_index].exp;
                if(terms_p[p_index].coef == 0 && terms_p[p_index].exp == 0){
                    fp = p_index - 1;
                    sn = p_index;
                    break;
                }
                p_index++;
            }
            cout<<"輸入完畢"<<endl;
        }
        else if(choose == 2){
            cout<<"P(x) = ";
            int tmp = 0;
            for(int i = sp; i <= fp; i++){
                if(terms_p[i].exp != 0){
                    if(terms_p[sp].coef == -1 && tmp == 0){
                        cout<<"-x^"<<terms_p[i].exp;
                        tmp = 1;
                    }
                    else if((terms_p[i].coef == 1 || terms_p[i].coef == -1)){
                        cout<<"x^"<<terms_p[i].exp;
                    }
                    else{
                        cout<<abs(terms_p[i].coef)<<"x^"<<terms_p[i].exp;
                    }
                }
                else{
                        cout<< abs(terms_p[i].coef);
                }
                if(i < fp){
                    if(terms_p[i+1].coef < 0){
                        cout<<" - ";
                    }
                    else{
                        cout<<" + ";
                    }
                }
            }
            cout<<endl;
        }
        else if(choose == 3){
            int p_exp;
            int ind;
            cout<<"輸入欲指定多項式P之指數次方：";
            cin>>p_exp;
            for(int i = sp; i <= fp; i++){
                if(terms_p[i].exp == p_exp){
                    ind = i;
                }
            }
            cout<<"x^"<<terms_p[ind].exp<<"的係數為："<<terms_p[ind].coef<<endl;
        }
        else if(choose == 4){
            int cho = 0;
            cout<<"(1)新增選項"<<endl;
            cout<<"(2)移除選項"<<endl;
            cout<<"請輸入選項：";
            cin>>cho;
            if(cho == 1){
                cout<<"輸入欲新增之係數與次方(輸入方式：係數 次方)"<<endl;
                int newE,newC;
                cin>>newC>>newE;
                for(int i = sp; i <= fp; i++){
                    if(newE < terms_p[i].exp && newE > terms_p[i+1].exp){
                        int ne = i+1;
                        // cout<<"ne = "<<ne<<endl;
                        for(int j = fp; j >= ne; j--){
                            terms_p[j+1].exp = terms_p[j].exp;
                            terms_p[j+1].coef = terms_p[j].coef;
                        }
                        terms_p[ne].exp = newE;
                        terms_p[ne].coef = newC;
                        fp++;
                        break;
                    }
                    else if(newE > terms_p[sp].exp){
                        int ne = i+1;
                        // cout<<"ne = "<<ne<<endl;
                        for(int j = fp; j >= sp; j--){
                            terms_p[j+1].exp = terms_p[j].exp;
                            terms_p[j+1].coef = terms_p[j].coef;
                        }
                        terms_p[sp].exp = newE;
                        terms_p[sp].coef = newC;
                        fp++;
                        break;
                    }
                    else if(newE < terms_p[fp].exp){
                        terms_p[fp+1].coef = newC;
                        terms_p[fp+1].exp = newE;
                        fp++;
                        break;
                    }
                    else if(newE == terms_p[i].exp){
                        terms_p[i].coef += newC;
                    }
                }
                cout<<"新增完畢"<<endl;
            }
            else if(cho == 2){
                cout<<"輸入欲移除之次方(輸入方式：次方):";
                int newE;
                cin>>newE;
                int check = 0;
                for(int i = 0; i <= fp; i++){
                    if(terms_p[i].exp == newE){
                        int ne = i;
                        for(int j = ne+1; j <= fp; j++){
                            terms_p[j-1].exp = terms_p[j].exp;
                            terms_p[j-1].coef = terms_p[j].coef;
                            check = 1;
                        }
                        fp--;
                        check = 1;
                        break;
                    }
                }
                if(check == 1){
                    cout<<"移除完畢"<<endl;
                }
                else{
                    cout<<"沒有該次方項"<<endl;
                }
                
            }
            else{
                cout<<"沒有這個選項"<<endl;
            }

        }
        else if(choose == 5){
            int i = 0;
            sa = i;
            cout<<"輸入P1(x)的多項式/ [輸入方式]：係數 次方 / 輸入結束請輸入：0 0"<<endl;
            while(1){
                cin>>terms[i].coef>>terms[i].exp;
                if(terms[i].coef == 0 && terms[i].exp == 0){
                    sb = i;
                    fa = i - 1;
                    break;
                }
                i++;
            }
            cout<<"輸入P2(x)的多項式/ [輸入方式]：係數 次方 / 輸入結束請輸入：0 0"<<endl;
            while(1){
                cin>>terms[i].coef>>terms[i].exp;
                if(terms[i].coef == 0 && terms[i].exp == 0){
                    avail = i;
                    sd = avail;
                    fb = i - 1;
                    break;
                }
                i++;
            }
            padd();
            cout<<"P1(x) + P2(x) = ";
            for(int i = sd; i <= fd; i++){
                if(terms[i].exp != 0){
                    if(terms[i].coef == 1 || terms[i].coef == -1){
                        cout<<"x^"<<terms[i].exp;
                    }
                    else{
                        cout<<abs(terms[i].coef)<<"x^"<<terms[i].exp;
                    }
                }
                else{
                        cout<< abs(terms[i].coef);
                }
                if(i < fd){
                    if(terms[i+1].coef < 0){
                        cout<<" - ";
                    }
                    else{
                        cout<<" + ";
                    }
                }
            }
            cout<<endl;
        }
        else if(choose == 6){
            int i = 0;
            sa = i;
            cout<<"輸入P1(x)的多項式 / [輸入方式]：係數 次方 / 輸入結束請輸入：0 0"<<endl;
            while(1){
                cin>>terms[i].coef>>terms[i].exp;
                if(terms[i].coef == 0 && terms[i].exp == 0){
                    sb = i;
                    fa = i - 1;
                    break;
                }
                i++;
            }
            cout<<"輸入P2(x)的多項式 / [輸入方式]：係數 次方 / 輸入結束請輸入：0 0"<<endl;
            while(1){
                cin>>terms[i].coef>>terms[i].exp;
                if(terms[i].coef == 0 && terms[i].exp == 0){
                    avail = i;
                    sd = avail;
                    fb = i - 1;
                    break;
                }
                i++;
            }
            sub();
            cout<<"P1(x) - P2(x) = ";
            for(int i = sd; i <= fd; i++){
                if(terms[i].exp != 0){
                    if(terms[i].coef == 1 || terms[i].coef == -1){
                        cout<<"x^"<<terms[i].exp;
                    }
                    else{
                        cout<<abs(terms[i].coef)<<"x^"<<terms[i].exp;
                    }
                }
                else{
                        cout<< abs(terms[i].coef);
                }
                if(i < fd){
                    if(terms[i+1].coef < 0){
                        cout<<" - ";
                    }
                    else{
                        cout<<" + ";
                    }
                }
            }
            cout<<endl;
        }
        else if(choose == 7){
            int i = 0;
            sa = i;
            cout<<"輸入P1(x)的多項式 / [輸入方式]：係數 次方 / 輸入結束請輸入：0 0"<<endl;
            while(1){
                cin>>terms[i].coef>>terms[i].exp;
                if(terms[i].coef == 0 && terms[i].exp == 0){
                    sb = i;
                    fa = i - 1;
                    break;
                }
                i++;
            }
            cout<<"輸入P2(x)的多項式 / [輸入方式]：係數 次方 / 輸入結束請輸入：0 0"<<endl;
            while(1){
                cin>>terms[i].coef>>terms[i].exp;
                if(terms[i].coef == 0 && terms[i].exp == 0){
                    avail = i;
                    sd = avail;
                    fb = i - 1;
                    break;
                }
                i++;
            }
            mul();
            cout<<"P1(x) * P2(x) = ";
            for(int i = se; i <= fe; i++){
                if(terms[i].exp != 0){
                    if(terms[i].coef == 1 || terms[i].coef == -1){
                        cout<<"x^"<<terms[i].exp;
                    }
                    else{
                        cout<<abs(terms[i].coef)<<"x^"<<terms[i].exp;
                    }
                }
                else{
                        cout<< abs(terms[i].coef);
                }
                if(i < fe){
                    if(terms[i+1].coef < 0){
                        cout<<" - ";
                    }
                    else{
                        cout<<" + ";
                    }
                }
            }
            cout<<endl;
        }
        else if(choose == 8){
            cout<<"程式結束"<<endl;
            break;
        }
        else if(choose == 9){
            while(p1.empty() == false){
                p1.pop_back();
            }
            while(p2.empty() == false){
                p2.pop_back();
            }
            int num;
            int val;
            cout<<"輸入P1<被除式>項數（總共有幾項）：";
            cin>>num;
            cout<<"輸入P1(x)<被除式>的多項式(輸入方式：次方由大到小，存在的項輸入系數，不存在就輸入0："<<endl;
            for(int i = 0; i < num; i++){
                cin>>val;
                p1.push_back(val);
            }
            num = 0;
            cout<<"輸入P2<除式>項數（總共有幾項）：";
            cin>>num;
            cout<<"輸入P2(x)<除式>的多項式(輸入方式：次方由大到小，存在的項輸入系數，不存在就輸入0："<<endl;
            for(int i = 0; i < num; i++){
                cin>>val;
                p2.push_back(val);
            }
            div();
        }
        else{
            cout<<"沒有這個選項"<<endl;
        }
    }
    return 0;
}