#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <fstream>
#include <vector>
#define INF 10000
using namespace std;


int k = 0;
char obstacle[100];
int cost[100];
int vertice = 0;
int edge = 0;
int G[100][100];
int N = 0;
bool book[100];
int dist[100] = {0};
int test = 0;
FILE *pFile = NULL;
char filename[32] = {0};


struct ajList_{
    int node;
    int w;
}ajList;
vector<ajList_> list[100];


void insert(int a, int b, int w){
    ajList_ tmp;
    tmp.node = b;
    tmp.w = w;
    list[a].push_back(tmp);
    tmp.node = a;
    tmp.w = w;
    list[b].push_back(tmp);
}


int Prim(int cur) {//選擇起始點
    int index = cur;
    int sum = 0;
    int i = 0;
    int j = 0;
    // cout << index << " ";//輸出index可以輸出路徑
    memset(book, false, sizeof(book));//初始化
    book[cur] = true;//標記初始點
    for (i = 0; i < N; ++i){
        dist[i] = G[cur][i];//初始化，並令每個與cur點鄰接點的距離存入dist
        // printf("dist[%d] = %d\n",i,dist[i]);
    }
    for (i = 1; i < N; ++i) {
        int minor = INF;
        for (j = 0; j < N; ++j) {//找到與index相接的最短路徑
            if (!book[j] && dist[j] < minor) {
                minor = dist[j];
                index = j;
            }
        }
        book[index] = true;
        // cout << index << " ";
        sum += minor;
        for (j = 0; j < N; ++j) {//重新初始化dist，找到與index鄰接的點
            if (!book[j] && dist[j] > G[index][j])
                dist[j] = G[index][j];
                // printf("dist[%d] = %d\n",j,dist[j]);
        }
    }
    // cout << endl;
    return sum;//返回最小生成樹的總路徑值
}

void menu(){

    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"                    Data Structure Homework 12"<<endl;;
    cout<<"                     40947007S 資工113 張欀齡"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
} 


int main(){
    menu();
    printf( "Please enter the file name: " );
    if( fgets( filename, sizeof( filename ), stdin ) == NULL ){
        printf( "Error!\n" );
        return 0;
    }
    if( filename[ strlen( filename ) - 1 ] == '\n' ){
        filename[ strlen( filename ) - 1 ] = 0;
    }
    if( ( pFile = fopen( filename, "r" ) ) == NULL ){
        printf( "File could not be opened!\n" );
        perror( "Error" );
        return 0;
    }
    int check = 0;
    // while(!feof(pFile)){
    //     fscanf( pFile, "%d", &test);
    // }
    // cout<<test<<endl;
    // cin>>test;
    while(!feof(pFile)){
        if(check == 0){
            fscanf( pFile, "%d", &test);
            check = 1;
        }
        // cout<<test<<endl;
        while(test--){
            // cout<<"in"<<endl;
            fscanf( pFile, "%d", &k);
            // cout<<k<<endl;
            // cin>>k;
            for(int i = 0; i < k; i++){
                fscanf( pFile, "%s%d", &obstacle[i], &cost[i]);
                // cout<<obstacle[i]<<" ";
                // cout<<cost[i]<<endl;
                // cin>>obstacle[i];
                // cin>>cost[i];
            }
            fscanf( pFile, "%d%d", &vertice, &edge);
            // cout<<vertice<<" "<<edge<<endl;
            // cin>>vertice>>edge;
            N = vertice;
            // cin.get();
            for(int i = 0; i < vertice; i++){
                for(int j = 0; j < vertice; j++){
                    G[i][j] = INF;
                }
            }
            //memset(G,0,sizeof(G));
            char f;
            fscanf( pFile, "%c ", &f);
            for(int i = 0; i < edge; i++){
                char input[100] = {0};
                int a, b, w;
                w = 0;
                fscanf(pFile, "%[^\n] ", input);
                // cout<<input<<endl;
                // getline(cin, input);
                a = input[0];
                b = input[2];
                a = a -'0';
                b = b -'0';
                a--;
                b--;
                for(int j = 4; j < strlen(input); j++){
                    for(int x = 0; x < k; x++){
                        if(input[j] == obstacle[x]){
                            w += cost[x] * (input[j+1]-'0');

                        }
                    }
                }
                // cout<<w<<endl;
                // cout<<"a "<<a<<endl;
                // cout<<"b "<<b<<endl;
                G[a][b] = w;
                G[b][a] = w;
                insert(a, b, w);
            }
            cout << Prim(0) << endl;
        }
    }
    
    return 0;
}