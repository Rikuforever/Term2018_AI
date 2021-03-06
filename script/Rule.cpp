#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include "Rule.h"
using namespace std;
enum Direction{cross,horizontal,vertical};

class Grid{
public:
    Grid(){
    };
    Grid(int x, int y){
        this->x=x;
        this->y=y;
    }
    int x=9;
    int y=9;
};

class Block{
public:
    Block(){};
    Block(bool f, Grid p1, Grid p2, Grid p3, Direction d){
        friendly=f;
        position[0]=p1;
        position[1]=p2;
        position[2]=p3;
        direction=d;
    }
    int shape;
    int priority;
    bool friendly;
    Grid position[3];
    Direction direction;
    Grid key,key2;
    Block* next;
};

typedef struct _list{
    Block* head;
    Block* current;
    int count;
}List;

int BitCalculate(List* clist);

void initlist(List* list){
    list->head=NULL;
    list->current=NULL;
    list->count=0;
}

void Add_Block(int s, bool f,Grid p1, Grid p2, Grid p3, Direction d, List* list){
    Block* b=(Block*)malloc(sizeof(Block));
    b->shape=s;
    b->friendly=f;
    b->position[0]=p1;
    b->position[1]=p2;
    b->position[2]=p3;
    b->direction=d;
    b->next=list->head;
    list->head=b;
    list->count++;
}

void Add_Block(Block* block, List* list){   //  overloading
    block->next=list->head;
    list->head=block;
    list->count++;
}

int List_Count(List* list){
    int num=0;
    if(list->head==NULL){
        return num;
    }
    list->current=list->head;
    while (list->current!=NULL) {
        list->current=list->current->next;
        num++;
    }
    list->count=num;
    return num;
}

Block* Select_ith_Block(int i,List* list){
    list->current=list->head;
    for(int n=0; n<i-1;n++){
        list->current=list->current->next;
    }
    return list->current;
}

List* Select_Blocks(int p, bool f, List* list){
    List* newlist = (List*)malloc(sizeof(List));
    initlist(newlist);
    list->current=list->head;
    while (1){
        if(list->current->priority==p && list->current->friendly==f){
            Block* newb = (Block*)malloc(sizeof(Block));
            newb->shape=list->current->shape;
            newb->direction=list->current->direction;
            newb->key=list->current->key;
            newb->friendly=list->current->friendly;
            newb->priority=list->current->priority;
            newb->position[0]=list->current->position[0];
            newb->position[1]=list->current->position[1];
            newb->position[2]=list->current->position[2];
            newb->key2=list->current->key2;
            Add_Block(newb, newlist);
            list->current=list->current->next;
            if(list->current==NULL){
                return newlist;
            }
        }
        else{
            list->current=list->current->next;
            if(list->current==NULL){
                return newlist;
            }
        }
    }
}

List* Select_Blocks(int p, bool f, List* list, List * clist){   //overloading
    List* newlist = (List*)malloc(sizeof(List));
    initlist(newlist);
    list->current=list->head;
    int n= BitCalculate(clist);
    while (1){
        if(list->current->shape==2&&list->current->priority==1){
            if(list->current->priority==p && list->current->friendly==f){
                Block* newb = (Block*)malloc(sizeof(Block));
                newb->shape=list->current->shape;
                newb->direction=list->current->direction;
                newb->key=list->current->key;
                newb->friendly=list->current->friendly;
                newb->priority=list->current->priority;
                newb->position[0]=list->current->position[0];
                newb->position[1]=list->current->position[1];
                newb->position[2]=list->current->position[2];
                newb->key2=list->current->key2;
                Add_Block(newb, newlist);
                list->current=list->current->next;
                if(list->current==NULL){
                    return newlist;
                }
            }
            else{
                list->current=list->current->next;
                if(list->current==NULL){
                    return newlist;
                }
            }
        }
        else{
            if(list->current->priority==p && list->current->friendly==f){
                if(n!=(n|(int)pow(2,list->current->key.x))&&n!=(n|(int)pow(2,list->current->key2.x))){
                Block* newb = (Block*)malloc(sizeof(Block));
                newb->shape=list->current->shape;
                newb->direction=list->current->direction;
                newb->key=list->current->key;
                newb->friendly=list->current->friendly;
                newb->priority=list->current->priority;
                newb->position[0]=list->current->position[0];
                newb->position[1]=list->current->position[1];
                newb->position[2]=list->current->position[2];
                newb->key2=list->current->key2;
                Add_Block(newb, newlist);
                list->current=list->current->next;
                if(list->current==NULL){
                    return newlist;
                }
            }
                else{
                    list->current=list->current->next;
                    if(list->current==NULL){
                        return newlist;
                    }
                }
            }
            else{
                list->current=list->current->next;
                if(list->current==NULL){
                    return newlist;
                }
            }
        }
    }
}

Block* Compare_Block(List* list){
    if(list->head==NULL){
        return NULL;
    }
    List _newlist;
    List* newlist=&_newlist;
    initlist(newlist);
    newlist =Select_Blocks(1,true, list);
    if(newlist->head==NULL){
        newlist=Select_Blocks(1,false, list);
    }
    if(newlist->head==NULL){
        newlist=Select_Blocks(3,true, list);
    }
    if(newlist->head==NULL){
        newlist=Select_Blocks(3,false, list);
    }
    if(newlist->head!=NULL){
        srand(time(NULL));
        
        int i=(int)arc4random()%List_Count(newlist)+1;
        return Select_ith_Block(i, newlist);
    }
    else{
        return NULL;
    }
}

Block* Compare_Block(List* list, List* clist){  //overloading
    if(list->head==NULL){
        return NULL;
    }
    List _newlist;
    List* newlist=&_newlist;
    initlist(newlist);
    newlist =Select_Blocks(1,true, list,clist);
    if(newlist->head==NULL){
        newlist=Select_Blocks(1,false, list,clist);
    }
    if(newlist->head==NULL){
        newlist=Select_Blocks(3,true, list,clist);
    }
    if(newlist->head==NULL){
        newlist=Select_Blocks(3,false, list,clist);
    }
    if(newlist->head!=NULL){
        srand(time(NULL));
        int i=(int)arc4random()%List_Count(newlist)+1;
        return Select_ith_Block(i, newlist);
    }
    else{
        return NULL;
    }
}

void ShowAllList(List* list){
    if(list->head==NULL){
        printf("empty\n");
        return;
    }
    for(int i=0; i<list->count;i++){
        printf("Block number %d\n",i+1);
        printf("shape : %d\n",Select_ith_Block(i+1, list)->shape);
        printf("frinedly : %d\n",Select_ith_Block(i+1, list)->friendly);
        printf("dot1 : %d , %d\n",Select_ith_Block(i+1, list)->position[0].x,Select_ith_Block(i+1, list)->position[0].y);
        printf("dot2 : %d , %d\n",Select_ith_Block(i+1, list)->position[1].x,Select_ith_Block(i+1, list)->position[1].y);
        printf("dot3 : %d , %d\n",Select_ith_Block(i+1, list)->position[2].x,Select_ith_Block(i+1, list)->position[2].y);
        if(Select_ith_Block(i+1, list)->direction==cross)
            printf("cross\n");
        if(Select_ith_Block(i+1, list)->direction==horizontal)
            printf("horizontal\n");
        if(Select_ith_Block(i+1, list)->direction==vertical)
            printf("vertical\n");
        printf("\n");
    }
}

void ShowBlock(Block* b){
    printf("----------------------------\n");
    printf("Data of Key Block\n");
    printf("Shape : %d\n",b->shape);
    printf("Friendly : %d (0:Hostile, 1:Friendly)\n",b->friendly);
    printf("Priority : %d\n",b->priority);
    printf("dot1 : (%d , %d)\n",b->position[0].x,b->position[0].y);
    printf("dot2 : (%d , %d)\n",b->position[1].x,b->position[1].y);
    if(b->shape==1||b->shape==2){
        printf("dot3 : (%d , %d)\n",b->position[2].x,b->position[2].y);
    }
    switch (b->direction) {
        case cross:
            printf(("Direction : Cross"));
            break;
        case horizontal:
            printf(("Direction : Horizontal"));
            break;
        case vertical:
            printf(("Direction : Vertical"));
            break;
    }
    printf("\n");
    printf("Key : (%d , %d)\n",b->key.x,b->key.y);
    printf("----------------------------\n\n");
}

void ShowMethod(Block*b){
    printf("----------------------------\n");
    printf("Printing part of rule...\n");
    printf("Shape : %d, Priority : %d\n",b->shape,b->priority);
    printf("Uesd Method : Solution %d\n",(int)floor((b->shape*12+b->priority*4)/10));
    printf("----------------------------\n");
}

void AddCautionList(List* list, List* clist){
    if(list->head==NULL){
        return;
    }
    List * newlist;
    newlist=Select_Blocks(2,false, list);
    for(int i=0; i<List_Count(newlist); i++){
        Block* temp =Select_ith_Block(i+1, newlist);
        Block* newb = (Block*)malloc(sizeof(Block));
        newb->shape=temp->shape;
        newb->direction=temp->direction;
        newb->key=temp->key;
        newb->friendly=temp->friendly;
        newb->priority=temp->priority;
        newb->position[0]=temp->position[0];
        newb->position[1]=temp->position[1];
        newb->position[2]=temp->position[2];
        newb->key2=temp->key2;
        Add_Block(newb, clist);
    }
}

int BitCalculate(List* clist){
    int n=0;
    for(int i=0; i<List_Count(clist); i++){
        int m = Select_ith_Block(i+1, clist)->key.x;
        int k = Select_ith_Block(i+1, clist)->key2.x;
        for(int p=0;p<7;p++){
            if(m==p){
                n=n|(int)pow(2,p);
            }
            if(k==p){
                n=n|(int)pow(2,p);
            }
        }
    }
    return n;
}

int RandomPick(List* clist){
    srand((unsigned int)time(NULL));
    int n = BitCalculate(clist);
    int s= arc4random()%7;
    s=(int)pow(2, s);
    while (1) {
        if(n!=(n|s)){
            return log2(s);
        }
        s= arc4random()%7;
        s=(int)pow(2, s);
    }
}

bool First_shot(int example [][6]){
    int n=0;
    for(int i=0; i<7; i++){
        if(example[i][0]!=0){
            n++;
        }
    }
    if(n!=0){
        return false;
    }
    return true;
}

bool Find_Shape_1(List* list, int example[][6]);
bool Find_Shape_2(List* list, int example[][6]);
bool Find_Shape_3(List* list, int example[][6]);
bool Find_Shape_4(List* list, int example[][6]);
bool Find_Shape_5(List* list, int example[][6]);
void Define_Block(Block* a, int example[][6]);

int Rule(std::vector<std::vector<int>> board){              // return 형이 int 형이며 게임보드 data를 vector<std::vector<int>> 형으로 받는 함수 Rule
    List mlist,m2list;                                      // mlist와 m2List 선언
    List* list=&mlist;                                      // list는 mlist의 주소값을 담고있다.
    List* clist=&m2list;                                    // clist는 m2list의 주소값을 담고있다.
    initlist(list);                                         // list 초기화
    initlist(clist);                                        // clist 초기화

    int example[7][6];                                      // 게임판의 data를 담을 int형 2차원배열 선언
    
    for (int x = 0; x < 7; x++) {                           // vector<std::vector<int>> 의 데이터를 int형 2차원배열에 담는다
        for (int y = 0; y < 6; y++) {
            example[x][y] = board[x][y];
        }
    }
    
    if(First_shot(example)){                                // 게임의 첫수를 두는지 판별하는 함수 return값이 true라면 첫수를 두는 것이다.
        printf("----------------------------\n");
        printf("Printing part of rule...\n");
        printf("Shape : Not Detected, Priority : Not Detected\n");
        printf("Uesd Method : Solution 0\n");
        printf("----------------------------\n");
        return 2;                                           // 첫수를 둔다면 Grid 기준 (2,0) 에 둔다.
    }
    
    if(Find_Shape_1(list,example)){                         // Shape 가 1인 블록을 찾아서 List에 추가하는 과정을 담고있는 함수
        for(int i=1; i<=List_Count(list);i++){              // List내의 존재하는 모든 Block 에 접근하기 위한 반복문
            Block* temp= Select_ith_Block(i, list);
            Define_Block(temp, example);                    // Block 의 Priority와 key1,key2값을 지정해주기위한 함수
        }
        AddCautionList(list,clist);                         // 두면 안되는 착수점 정보를 담고있는 모든 Block들을 clist에 추가
        Block* result =Compare_Block(list);                 // 현재 List에 저장된 모든 Block들을 비교해 적합한 Block을 추려주는 함수
        if(result!=NULL){                                   // 만약 찾은 Block 이 없다면 다른 Shape 의 Block을 찾으로 이동하고 만약 찾았다면
            ShowBlock(result);                              // 찾은 Block 의 data를 출력한다
            ShowMethod(result);
            int r= result->key.x;                           // 착수점의 위치를 추려낸다
            return r;                                       // 착수점을 반환한다
        }
    }
    if(Find_Shape_2(list,example)){                         // Shape 가 2인 블록을 찾아서 List에 추가하는 과정을 담고있는 함수
        for(int i=0; i<List_Count(list);i++){               // List내의 존재하는 모든 Block 에 접근하기 위한 반복문
            Block* temp = Select_ith_Block(i+1, list);
            Define_Block(temp, example);                    // Block 의 Priority와 key1,key2값을 지정해주기위한 함수
        }
        AddCautionList(list,clist);                         // 두면 안되는 착수점 정보를 담고있는 모든 Block들을 clist에 추가
        Block* result =Compare_Block(list,clist);           // 현재 List에 저장된 모든 Block들을 비교해 적합한 Block을 추려주는 함수
        if(result!=NULL){                                   // 만약 찾은 Block 이 없다면 다른 Shape 의 Block을 찾으로 이동하고 만약 찾았다면
            ShowBlock(result);                              // 찾은 Block 의 data를 출력한다
            ShowMethod(result);
            int r= result->key.x;                           // 착수점의 위치를 추려낸다
            return r;                                       // 착수점을 반환한다
        }
    }
    if(Find_Shape_3(list,example)){                         // Shape 가 3인 블록을 찾아서 List에 추가하는 과정을 담고있는 함수
        for(int i=0; i<List_Count(list);i++){               // List내의 존재하는 모든 Block 에 접근하기 위한 반복문
            Block* temp = Select_ith_Block(i+1, list);
            Define_Block(temp, example);                    // Block 의 Priority와 key1,key2값을 지정해주기위한 함수
        }
        AddCautionList(list, clist);                        // 두면 안되는 착수점 정보를 담고있는 모든 Block들을 clist에 추가
        Block* result =Compare_Block(list,clist);           // 현재 List에 저장된 모든 Block들을 비교해 적합한 Block을 추려주는 함수
        if(result!=NULL){                                   // 만약 찾은 Block 이 없다면 다른 Shape 의 Block을 찾으로 이동하고 만약 찾았다면
            ShowBlock(result);                              // 찾은 Block 의 data를 출력한다
            ShowMethod(result);
            int r= result->key.x;                           // 착수점의 위치를 추려낸다
            return r;                                       // 착수점을 반환한다
        }
    }
    if(Find_Shape_4(list,example)){                         // Shape 가 4인 블록을 찾아서 List에 추가하는 과정을 담고있는 함수
        for(int i=0; i<List_Count(list);i++){               // List내의 존재하는 모든 Block 에 접근하기 위한 반복문
            Block* temp = Select_ith_Block(i+1, list);
            Define_Block(temp, example);                    // Block 의 Priority와 key1,key2값을 지정해주기위한 함수
        }
        AddCautionList(list, clist);                        // 두면 안되는 착수점 정보를 담고있는 모든 Block들을 clist에 추가
        Block* result =Compare_Block(list,clist);           // 현재 List에 저장된 모든 Block들을 비교해 적합한 Block을 추려주는 함수
        if(result!=NULL){                                   // 만약 찾은 Block 이 없다면 다른 Shape 의 Block을 찾으로 이동하고 만약 찾았다면
            ShowBlock(result);                              // 찾은 Block 의 data를 출력한다
            ShowMethod(result);
            int r = result->key.x;                          // 착수점의 위치를 추려낸다
            return r;                                       // 착수점을 반환한다
        }
    }
    if(Find_Shape_5(list,example)){                         // Shape 가 5인 블록을 찾아서 List에 추가하는 과정을 담고있는 함수
        for(int i=0; i<List_Count(list);i++){               // List내의 존재하는 모든 Block 에 접근하기 위한 반복문
            Block* temp = Select_ith_Block(i+1, list);
            Define_Block(temp, example);                    // Block 의 Priority와 key1,key2값을 지정해주기위한 함수
        }
        AddCautionList(list, clist);                        // 두면 안되는 착수점 정보를 담고있는 모든 Block들을 clist에 추가
        Block* result =Compare_Block(list,clist);           // 현재 List에 저장된 모든 Block들을 비교해 적합한 Block을 추려주는 함수
        if(result!=NULL){                                   // 만약 찾은 Block 이 없다면 다른 Shape 의 Block을 찾으로 이동하고 만약 찾았다면
            ShowBlock(result);                              // 찾은 Block 의 data를 출력한다
            ShowMethod(result);
            int r = result->key.x;                          // 착수점의 위치를 추려낸다
            return r;                                       // 착수점을 반환한다
        }
    }
    printf("----------------------------\n");
    printf("Printing part of rule...\n");
    printf("Shape : Not Detected, Priority : Not Detected\n");
    printf("Uesd Method : Solution 7\n");
    printf("----------------------------\n");
    return RandomPick(clist);                               // 위에서 아무런 착수점도 찾지 못했다면 절대 두면 않되는 자리를 제외한 자리에 둔다
}


bool Find_Shape_1(List* list, int example[][6]) {
    
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 5; j++) {
            
            if (i + 2 <= 6) {
                if ((example[i][j] == example[i + 1][j]) && (example[i][j] == example[i + 2][j]) && example[i][j] != 0) {
					//가로로 '000'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    
                    p1.x = i;    p1.y = j;
                    p2.x = i + 1;    p2.y = j;
                    p3.x = i + 2;    p3.y = j;
                    
                    d = horizontal;
                    Add_Block(1,f, p1, p2, p3, d, list);
                }
            }
            
            if (j + 2 <= 5) {
                if ((example[i][j] == example[i][j + 1]) && (example[i][j] == example[i][j + 2]) && example[i][j] != 0) {
					//세로로 '000'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i;    p2.y = j + 1;
                    p3.x = i;    p3.y = j + 2;
                    
                    d = vertical;
                    Add_Block(1,f, p1, p2, p3, d, list);
                }
            }
            
            if (i + 2 <= 6 && j + 2 <= 5) {
                if ((example[i][j] == example[i + 1][j + 1]) && (example[i][j] == example[i + 2][j + 2]) && example[i][j] != 0) {
					//우상향 대각선으로 '000'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    
                    p1.x = i;    p1.y = j;
                    p2.x = i + 1;    p2.y = j + 1;
                    p3.x = i + 2;    p3.y = j + 2;
                    
                    d = cross;
                    Add_Block(1,f, p1, p2, p3, d, list);
                }
            }
            
            if (i - 2 >= 0 && j + 2 <= 5) {
                if ((example[i][j] == example[i - 1][j + 1]) && (example[i][j] == example[i - 2][j + 2]) && example[i][j] != 0) {
					//좌상향 대각선으로 '000'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    
                    p1.x = i;    p1.y = j;
                    p2.x = i - 1;    p2.y = j + 1;
                    p3.x = i - 2;    p3.y = j + 2;
                    
                    d = cross;
                    Add_Block(1,f, p1, p2, p3, d, list);
                }
            }
        }
    }
    return true;
}

bool Find_Shape_2(List* list, int example[][6]) {
    
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 5; j++) {
            
            if (i + 3 <= 6) {
                if (example[i][j] == example[i + 1][j] && example[i][j] == example[i + 3][j] && example[i][j] != 0) {
					//오른쪽 방향 가로 : '00 0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    
                    p1.x = i;    p1.y = j;
                    p2.x = i + 1;    p2.y = j;
                    p3.x = i + 3;    p3.y = j;
                    
                    d = horizontal;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(2,f, p1, p2, p3, d, list);
                }
            }
            
            if (i - 3 >= 0) {
                if (example[i][j] == example[i - 1][j] && example[i][j] == example[i - 3][j] && example[i][j] != 0) {
					//왼쪽 방향 가로 : '0 00'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    
                    p1.x = i;    p1.y = j;
                    p2.x = i - 1;    p2.y = j;
                    p3.x = i - 3;    p3.y = j;
                    
                    d = horizontal;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(2,f, p1, p2, p3, d, list);
                }
            }
            
            if (i + 3 <= 6 && j + 3 <= 5) {
                if (example[i][j] == example[i + 1][j + 1] && example[i][j] == example[i + 3][j + 3] && example[i][j] != 0) {
					//우상향 대각선 '00 0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    
                    p1.x = i;    p1.y = j;
                    p2.x = i + 1;    p2.y = j + 1;
                    p3.x = i + 3;    p3.y = j + 3;
                    
                    d = cross;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(2,f, p1, p2, p3, d, list);
                }
            }
            
            if (i - 3 >= 0 && j + 3 <= 5) {
                if (example[i][j] == example[i - 1][j + 1] && example[i][j] == example[i - 3][j + 3] && example[i][j] != 0) {
					//좌상향 대각선 '00 0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    
                    p1.x = i;    p1.y = j;
                    p2.x = i - 1;    p2.y = j + 1;
                    p3.x = i - 3;    p3.y = j + 3;
                    
                    d = cross;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(2,f, p1, p2, p3, d, list);
                }
            }
            
            if (i + 3 <= 6 && j - 3 >= 0) {
                if (example[i][j] == example[i + 1][j - 1] && example[i][j] == example[i + 3][j - 3] && example[i][j] != 0) {
					//우하향 대각선 '00 0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    
                    p1.x = i;    p1.y = j;
                    p2.x = i + 1;    p2.y = j - 1;
                    p3.x = i + 3;    p3.y = j - 3;
                    
                    d = cross;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(2,f, p1, p2, p3, d, list);
                }
            }
            
            if (i - 3 >= 0 && j - 3 >= 0) {
                if (example[i][j] == example[i - 1][j - 1] && example[i][j] == example[i - 3][j - 3] && example[i][j] != 0) {
					//좌하향 대각선 '00 0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    
                    p1.x = i;    p1.y = j;
                    p2.x = i - 1;    p2.y = j - 1;
                    p3.x = i - 3;    p3.y = j - 3;
                    
                    d = cross;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(2,f, p1, p2, p3, d, list);
                }
            }
            
            
        }
    }
    
    return true;
}

bool Find_Shape_3(List* list, int example[][6]) {
    
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 5; j++) {
            if (i + 1 <= 6) {
                if (example[i][j] == example[i + 1][j] && example[i][j] != 0) {
					//가로 '00'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i + 1;    p2.y = j;
                    
                    d = horizontal;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(3,f, p1, p2, p3, d, list);
                }
            }
            if (j + 1 <= 5) {
                if (example[i][j] == example[i][j + 1] && example[i][j] != 0) {
					//세로 '00'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i;    p2.y = j + 1;
                    
                    d = vertical;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(3,f, p1, p2, p3, d, list);
                }
            }
            if (i + 1 <= 6 && j + 1 <= 5) {
                if (example[i][j] == example[i + 1][j + 1] && example[i][j] != 0) {
					//우상향 대각선 '00'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i + 1;    p2.y = j + 1;
                    
                    d = cross;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(3,f, p1, p2, p3, d, list);
                }
            }
            if (i - 1 >= 0 && j + 1 <= 5) {
                if (example[i][j] == example[i - 1][j + 1] && example[i][j] != 0) {
					//좌상향 대각선 '00'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i - 1;    p2.y = j + 1;
                    
                    d = cross;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(3,f, p1, p2, p3, d, list);
                }
            }
            
        }
    }
    
    
    return true;
}

bool Find_Shape_4(List* list, int example[][6]) {
    
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 5; j++) {
            if (i + 2 <= 6) {
                if (example[i][j] == example[i + 2][j] && example[i][j] != 0) {
					//가로 '0 0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i + 2;    p2.y = j;
                    
                    d = horizontal;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(4,f, p1, p2, p3, d, list);
                }
            }
            if (i + 2 <= 6 && j + 2 <= 5) {
                if (example[i][j] == example[i + 2][j + 2] && example[i][j] != 0) {
					//우상향 대각선 '0 0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i + 2;    p2.y = j + 2;
                    
                    d = cross;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(4,f, p1, p2, p3, d, list);
                }
            }
            if (i - 2 >= 0 && j + 2 <= 5) {
                if (example[i][j] == example[i - 2][j + 2] && example[i][j] != 0) {
					//우상향 대각선 '0 0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i - 2;    p2.y = j + 2;
                    
                    d = cross;
                    Block block(f,p1,p2,p3,d);
                    Add_Block(4,f, p1, p2, p3, d, list);
                }
            }
            
        }
    }
    
    return true;
}

bool Find_Shape_5(List* list, int example[][6]) {
    
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 5; j++) {
            if (i + 3 <= 6) {
                if (example[i][j] == example[i + 3][j] && example[i][j] != 0) {
					//가로 '0  0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i + 3;    p2.y = j;
                    
                    d = horizontal;
                    Add_Block(5,f, p1, p2, p3, d, list);
                }
            }
            if (i + 3 <= 6 && j + 3 <= 5) {
                if (example[i][j] == example[i + 3][j + 3] && example[i][j] != 0) {
					//우상향 대각선 '0  0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i + 3;    p2.y = j + 3;
                    
                    d = cross;
                    Add_Block(5,f, p1, p2, p3, d, list);
                }
            }
            if (i - 3 >= 0 && j + 3 <= 5) {
                if (example[i][j] == example[i - 3][j + 3] && example[i][j] != 0) {
					//우상향 대각선 '0  0'
                    bool f;
                    Grid p1, p2, p3;
                    Direction d;
                    if (example[i][j] == 1) {
                        f = true;
                    }
                    else if (example[i][j] == 2) {
                        f = false;
                    }
                    p1.x = i;    p1.y = j;
                    p2.x = i - 3;    p2.y = j + 3;
                    
                    d = cross;
                    Add_Block(5,f, p1, p2, p3, d, list);
                }
            }
            
        }
    }
    return true;
}

void Define_Block(Block* a, int example[][6]) {
    if (a->shape == 1) {
        if (a->direction == horizontal) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[2].x;
            int y2 = a->position[2].y;
            
            if (x1 >= 1) {                                                    // 'S000'
                if (example[x1 - 1][y1] == 0 && y1 == 0) {
                    //S가 비어있고 S아래가 벽일때
                    a->priority = 1;                                        //두어야할 곳
                    Grid x(x1 - 1, y1);
                    a->key = x;
                }
                else if (example[x1 - 1][y1] == 0 && y1 >= 1 && example[x1 - 1][y1 - 1] != 0) {
                    //S가 비어있고 그 아래가 차있을때
                    a->priority = 1;                                        //두어야할 곳
                    Grid x(x1 - 1, y1);
                    a->key = x;
                }
                else if (y1 == 1 && example[x1 - 1][y1 - 1] != 0) {
                    //S아래가 비어있고 그 아래가 벽일때
                    a->priority = 2;                                        //두면 안되는 곳
                    Grid x(x1 - 1, y1 - 1);
                    a->key = x;
                }
                else if (y1 >= 2 && example[x1 - 1][y1 - 1] == 0 && example[x1 - 1][y1 - 2] != 0) {
                    //S아래가 비어있고 그 아래가 차있을때
                    a->priority = 2;                                        //두면 안되는 곳
                    Grid x(x1 - 1, y1 - 1);
                    a->key = x;
                }
            }
            if (a->priority != 1 && x2 <= 5) {                                // '000S'
                if (example[x2 + 1][y2] == 0 && y2 == 0) {
                    //S가 비어있고 S아래가 벽일때
                    a->priority = 1;                                        //두어야할 곳
                    Grid x(x2 + 1, y2);
                    a->key = x;
                }
                else if (example[x2 + 1][y2] == 0 && y2 >= 1 && example[x2 + 1][y2 - 1] != 0) {
                    //S가 비어있고 그 아래가 차있을때
                    a->priority = 1;                                        //두어야할 곳
                    Grid x(x2 + 1, y2);
                    a->key = x;
                }
                else if (y2 == 1 && example[x2 + 1][y2 - 1] != 0) {
                    //S아래가 비어있고 그 아래가 벽일때
                    a->priority = 2;                                        //두면 안되는 곳
                    Grid x(x2 + 1, y2 - 1);
                    a->key2 = x;
                }
                else if (y2 >= 2 && example[x2 + 1][y2 - 1] == 0 && example[x2 + 1][y2 - 2] != 0) {
                    //S아래가 비어있고 그 아래가 차있을때
                    a->priority = 2;                                        //두면 안되는 곳
                    Grid x(x2 + 1, y2 - 1);
                    a->key2 = x;
                }
            }
            
        }
        else if (a->direction == vertical) {
            int x2 = a->position[2].x;
            int y2 = a->position[2].y;
            //세로로 000일때에는 무조건 위를 막아야 하고 그곳은 벽이 아닌 이상 무조건 둘수 있다.
            if (y2 <= 4 && example[x2][y2 + 1] == 0) {
                a->priority = 1;
                Grid x(x2, y2 + 1);
                a->key = x;
            }
        }
        else if (a->direction == cross) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[2].x;
            int y2 = a->position[2].y;
            if (x2 == x1 + 2 && y2 == y1 + 2) {                                //우상향으로 'S000S'
                if (x1 >= 1) {                                                //모양의 왼쪽
                    if (y1 == 1 && example[x1 - 1][y1 - 1] == 0) {
                        //S가 비어있고 S아래가 벽일때
                        a->priority = 1;
                        Grid x(x1 - 1, y1 - 1);
                        a->key = x;
                    }
                    else if (y1 >= 2 && example[x1 - 1][y1 - 1] == 0 && example[x1 - 1][y1 - 2] != 0) {
                        //S가 비어있고 S아래가 차있을때
                        a->priority = 1;
                        Grid x(x1 - 1, y1 - 1);
                        a->key = x;
                    }
                    else if (y1 == 2 && example[x1 - 1][y1 - 2] == 0) {
                        //S의 아래가 비어있고 그아래가 벽일때
                        a->priority = 2;
                        Grid x(x1 - 1, y1 - 2);
                        a->key = x;
                    }
                    else if (y1 >= 3 && example[x1 - 1][y1 - 2] == 0 && example[x1 - 1][y1 - 3] != 0) {
                        //S의 아래가 비어있고 그아래가 차있을때
                        a->priority = 2;
                        Grid x(x1 - 1, y1 - 2);
                        a->key = x;
                    }
                }
                if (a->priority != 1 && x2 <= 5 && y2 <= 4) {                //모양의 오른쪽
                    if (example[x2 + 1][y2 + 1] == 0 && example[x2 + 1][y2] != 0) {
                        //S가 비어있고 그아래가 차있을때 (아래가 벽이 될수없다)
                        a->priority = 1;
                        Grid x(x2 + 1, y2 + 1);
                        a->key = x;
                    }
                    else if (example[x2 + 1][y2] == 0 && example[x2 + 1][y2 - 1] != 0) {
                        //S아래가 비어있고 그아래가 차있을때 (그아래는 벽이 될수없다)
                        a->priority = 2;
                        Grid x(x2 + 1, y2);
                        a->key2 = x;                                        //모양의 왼쪽에서 찾은 key와 겹쳐질수 있으므로 새로운 key2에 저장
                    }
                }
            }
            else if (x2 == x1 - 2 && y2 == y1 + 2) {                        //좌상향으로 'S000S'
                if (x1 <= 5) {                                                //모양의 오른쪽
                    if (y1 == 1 && example[x1 + 1][y1 - 1] == 0) {
                        //S가 비어있고 S아래가 벽일때
                        a->priority = 1;
                        Grid x(x1 + 1, y1 - 1);
                        a->key = x;
                    }
                    else if (y1 >= 2 && example[x1 + 1][y1 - 1] == 0 && example[x1 + 1][y1 - 2] != 0) {
                        //S가 비어있고 S아래가 차있을때
                        a->priority = 1;
                        Grid x(x1 + 1, y1 - 1);
                        a->key = x;
                    }
                    else if (y1 == 2 && example[x1 + 1][y1 - 2] == 0) {
                        //S의 아래가 비어있고 그아래가 벽일때
                        a->priority = 2;
                        Grid x(x1 + 1, y1 - 2);
                        a->key = x;
                    }
                    else if (y1 >= 3 && example[x1 + 1][y1 - 2] == 0 && example[x1 + 1][y1 - 3] != 0) {
                        //S의 아래가 비어있고 그아래가 차있을때
                        a->priority = 2;
                        Grid x(x1 + 1, y1 - 2);
                        a->key = x;
                    }
                }
                if (a->priority != 1 && x2 >= 1 && y2 <= 4) {                //모양의 왼쪽
                    if (example[x2 - 1][y2 + 1] == 0 && example[x2 - 1][y2] != 0) {
                        //S가 비어있고 그아래가 차있을때 (아래가 벽이 될수없다)
                        a->priority = 1;
                        Grid x(x2 - 1, y2 + 1);
                        a->key = x;
                    }
                    else if (example[x2 - 1][y2] == 0 && example[x2 - 1][y2 - 1] != 0) {
                        //S아래가 비어있고 그아래가 차있을때 (그아래는 벽이 될수없다)
                        a->priority = 2;
                        Grid x(x2 - 1, y2);
                        a->key2 = x;                                        //모양의 왼쪽에서 찾은 key와 겹쳐질수 있으므로 새로운 key2에 저장
                    }
                }
            }
            
            
        }
    }
    else if (a->shape == 2) {
        if (a->direction == horizontal) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[2].x;
            int y2 = a->position[2].y;
            
            if (x2 == x1 + 3 && y2 == y1) {                                    //모양이 가로로 '00S0'일때    S는 빈곳
                if (y1 == 0 && example[x2 - 1][y1] == 0) {
                    //S가 비어있고 그 아래가 벽일때
                    a->priority = 1;                                        //두어야 할곳
                    Grid x(x2 - 1, y1);
                    a->key = x;
                }
                else if (y1 >= 1 && example[x2 - 1][y1] == 0 && example[x2 - 1][y1 - 1] != 0) {
                    //S가 비어있고 그 아래가 차있을때
                    a->priority = 1;                                        //두어야 할곳
                    Grid x(x2 - 1, y1);
                    a->key = x;
                }
                else if (y1 == 1 && example[x2 - 1][y1 - 1] == 0) {
                    //이 모양 아래아래가 벽이고 S의 아래가 비어있을때
                    a->priority = 2;                                        //두면 안되는 곳
                    Grid x(x2 - 1, y1 - 1);
                    a->key = x;
                }
                else if (y1 >= 2 && example[x2 - 1][y1 - 1] == 0 && example[x2 - 1][y1 - 2] != 0) {
                    //S의 아래가 비어있고 그 아래가 차있을때
                    a->priority = 2;                                        //두면 안되는 곳
                    Grid x(x2 - 1, y1 - 1);
                    a->key = x;
                }
                if (a->priority != 1 && y1 == 0 && x1 >= 1 && example[x1 - 1][y1] == 0) {
                    //priority가 1이 아니고 모양의 왼쪽이 비어있고 아래가 벽일때
                    a->priority = 3;                                        //priority가 1이 아닐때 두어야할 곳
                    Grid x(x1 - 1, y1);
                    a->key = x;
                }
                else if (a->priority != 1 && y1 >= 1 && x1 >= 1 && example[x1 - 1][y1] == 0 && example[x1 - 1][y1 - 1] != 0) {
                    //priority가 1이 아니고 모양의 왼쪽이 비어있고 그 아래가 차있을 때
                    a->priority = 3;                                        //priority가 1이 아닐때 두어야할 곳
                    Grid x(x1 - 1, y1);
                    a->key = x;
                }
            }
            
            else if (x2 == x1 - 3 && y2 == y1) {                                    //모양이 가로로 '0S00'일때
                if (y1 == 0 && example[x2 + 1][y1] == 0) {
                    //S가 비어있고 그 아래가 벽일때
                    a->priority = 1;                                        //두어야 할곳
                    Grid x(x2 + 1, y1);
                    a->key = x;
                }
                else if (y1 >= 1 && example[x2 + 1][y1] == 0 && example[x2 + 1][y1 - 1] != 0) {
                    //S가 비어있고 그 아래가 차있을때
                    a->priority = 1;                                        //두어야 할곳
                    Grid x(x2 + 1, y1);
                    a->key = x;
                }
                else if (y1 == 1 && example[x2 + 1][y1 - 1] == 0) {
                    //이 모양 아래아래가 벽이고 S의 아래가 비어있을때
                    a->priority = 2;                                        //priority가 1이 아닐때 두면 안되는 곳
                    Grid x(x2 + 1, y1 - 1);
                    a->key = x;
                }
                else if (y1 >= 2 && example[x2 + 1][y1 - 1] == 0 && example[x2 + 1][y1 - 2] != 0) {
                    //S의 아래가 비어있고 그 아래가 차있을때
                    a->priority = 2;                                        //priority가 1이 아닐때 두면 안되는 곳
                    Grid x(x2 + 1, y1 - 1);
                    a->key = x;
                }
                if (a->priority != 1 && y1 == 0 && x1 <= 5 && example[x1 + 1][y1] == 0) {
                    //priority가 1이 아니고 모양의 오른쪽이 비어있고 아래가 벽일때
                    a->priority = 3;                                        //priority가 1이 아닐때 두어야할 곳
                    Grid x(x1 + 1, y1);
                    a->key = x;
                }
                else if (a->priority != 1 && y1 >= 1 && x1 <= 5 && example[x1 + 1][y1] == 0 && example[x1 + 1][y1 - 1] != 0) {
                    //priority가 1이 아니고 모양의 오른쪽이 비어있고 그 아래가 차있을 때
                    a->priority = 3;                                        //priority가 1이 아닐때 두어야할 곳
                    Grid x(x1 + 1, y1);
                    a->key = x;
                }
            }
            
        }
        else if (a->direction == cross) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[2].x;
            int y2 = a->position[2].y;
            if (x2 == x1 + 3 && y2 == y1 + 3) {                                //모양이 우상향으로 '00S0'일때    S는 빈곳
                if (example[x2 - 1][y2 - 1] == 0 && example[x2 - 1][y2 - 2] != 0) {
                    //S가 비어있고 그 아래가 차있을 때
                    a->priority = 1;                                        //두어야 할곳
                    Grid x(x2 - 1, y2 - 1);
                    a->key = x;
                }
                else if (example[x2 - 1][y2 - 2] == 0 && example[x2 - 1][y2 - 3] != 0) {
                    //S 아래가 비어있고 그 아래가 차있을때
                    a->priority = 2;                                        //priority가 1이 아닐때 두면 안되는 곳
                    Grid x(x2 - 1, y2 - 2);
                    a->key = x;
                }
                if (a->priority != 1 && y1 == 1 && x1 >= 1 && example[x1 - 1][y1 - 1] == 0) {
                    //priority가 1이 아닐때 두개 옆이 비어있고 그 비어있는 칸 아래가 벽일때
                    a->priority = 3;                                        //priority가 1이 아닐때 두어야 하는 곳
                    Grid x(x1 - 1, y1 - 1);
                    a->key = x;
                }
                else if (a->priority != 1 && y1 >= 2 && x1 >= 1 && example[x1 - 1][y1 - 1] == 0 && example[x1 - 1][y1 - 2] != 0) {
                    //priority가 1이 아닐때 두개 옆이 비어있고 그 비어있는 칸 아래가 차있을때
                    a->priority = 3;                                        //priority가 1이 아닐때 두어야 하는 곳
                    Grid x(x1 - 1, y1 - 1);
                    a->key = x;
                }
            }
            else if (x2 == x1 - 3 && y2 == y1 + 3) {                                //모양이 좌상향으로 '00S0'일때
                if (example[x2 + 1][y2 - 1] == 0 && example[x2 + 1][y2 - 2] != 0) {
                    //S가 비어있고 그 아래가 차있을 때
                    a->priority = 1;                                        //두어야 할곳
                    Grid x(x2 + 1, y2 - 1);
                    a->key = x;
                }
                else if (example[x2 + 1][y2 - 2] == 0 && example[x2 + 1][y2 - 3] != 0) {
                    //S 아래가 비어있고 그 아래가 차있을때
                    a->priority = 2;                                        //priority가 1이 아닐때 두면 안되는 곳
                    Grid x(x2 + 1, y2 - 2);
                    a->key = x;
                }
                if (a->priority != 1 && y1 == 1 && x1 <= 5 && example[x1 + 1][y1 - 1] == 0) {
                    //priority가 1이 아닐때 두개 옆이 비어있고 그 칸 아래가 벽일때
                    a->priority = 3;                                        //priority가 1이 아닐때 두어야 하는 곳
                    Grid x(x1 + 1, y1 - 1);
                    a->key = x;
                }
                else if (a->priority != 1 && y1 >= 2 && x1 <= 5 && example[x1 + 1][y1 - 1] == 0 && example[x1 + 1][y1 - 2] != 0) {
                    //priority가 1이 아닐때 두개 옆이 비어있고 그 칸 아래가 차있을때
                    a->priority = 3;                                        //priority가 1이 아닐때 두어야 하는 곳
                    Grid x(x1 + 1, y1 - 1);
                    a->key = x;
                }
            }
            else if (x2 == x1 + 3 && y2 == y1 - 3) {                        //모양이 우하향으로 '00S0'일때
                if (example[x2 - 1][y2 + 1] == 0 && example[x2 - 1][y2] != 0) {
                    //S가 비어 있고 그 아래가 차있을때
                    a->priority = 1;                                        //두어야할 곳
                    Grid x(x2 - 1, y2 + 1);
                    a->key = x;
                }
                else if (y2 == 0 && example[x2 - 1][y2] == 0) {
                    //S 아래가 비어있고 그 아래가 벽일떄
                    a->priority = 2;                                        //priority가 1이 아닐떄 두면 안되는곳
                    Grid x(x2 - 1, y2);
                    a->key = x;
                }
                else if (y2 >= 1 && example[x2 - 1][y2] == 0 && example[x2 - 1][y2 - 1] != 0) {
                    //S 아래가 비어있고 그 아래가 차있을때
                    a->priority = 2;                                        //priority가 1이 아닐떄 두면 안되는곳
                    Grid x(x2 - 1, y2);
                    a->key = x;
                }
                if (a->priority != 1 && x1 >= 1 && example[x1 - 1][y1 + 1] == 0 && example[x1 - 1][y1] != 0) {
                    //priority가 1이 아니고 두개 옆이 비어있고 그 아래가 차있을때
                    a->priority = 3;
                    Grid x(x1 - 1, y1 + 1);
                    a->key = x;
                }
            }
            else if (x2 == x1 - 3 && y2 == y1 - 3) {                        //모양이 좌하향으로 '00S0'일때
                if (example[x2 + 1][y2 + 1] == 0 && example[x2 + 1][y2] != 0) {
                    //S가 비어 있고 그 아래가 차있을때
                    a->priority = 1;                                        //두어야할 곳
                    Grid x(x2 + 1, y2 + 1);
                    a->key = x;
                }
                else if (y2 == 0 && example[x2 + 1][y2] == 0) {
                    //S 아래가 비어있고 그 아래가 벽일떄
                    a->priority = 2;                                        //priority가 1이 아닐떄 두면 안되는곳
                    Grid x(x2 + 1, y2);
                    a->key = x;
                }
                else if (y2 >= 1 && example[x2 + 1][y2] == 0 && example[x2 + 1][y2 - 1] != 0) {
                    //S 아래가 비어있고 그 아래가 차있을때
                    a->priority = 2;                                        //priority가 1이 아닐떄 두면 안되는곳
                    Grid x(x2 + 1, y2);
                    a->key = x;
                }
                if (a->priority != 1 && x1 <= 5 && example[x1 + 1][y1 + 1] == 0 && example[x1 + 1][y1] != 0) {
                    //priority가 1이 아니고 두개 옆이 비어있고 그 아래가 차있을때
                    a->priority = 3;
                    Grid x(x1 + 1, y1 + 1);
                    a->key = x;
                }
            }
        }
        
    }
    else if (a->shape == 3) {
        if (a->direction == horizontal) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[1].x;
            int y2 = a->position[1].y;
            if (x1 >= 1) {                                                    //'S00'
                if (y1 == 0 && example[x1 - 1][y1] == 0) {
                    //S가 비어있고 S아래가 벽일때
                    a->priority = 1;
                    Grid x(x1 - 1, y1);
                    a->key = x;
                }
                else if (y1 >= 1 && example[x1 - 1][y1] == 0 && example[x1 - 1][y1 - 1] != 0) {
                    //S가 비어있고 S아래가 차있을때
                    a->priority = 1;
                    Grid x(x1 - 1, y1);
                    a->key = x;
                }
            }
            if (a->priority != 1 && x2 <= 5) {                                //'00S'
                if (y2 == 0 && example[x2 + 1][y2] == 0) {
                    //S가 비어있고 S아래가 벽일때
                    a->priority = 1;
                    Grid x(x2 + 1, y2);
                    a->key = x;
                }
                else if (y2 >= 1 && example[x2 + 1][y2] == 0 && example[x2 + 1][y2 - 1] != 0) {
                    //S가 비어있고 S아래가 차있을때
                    a->priority = 1;
                    Grid x(x2 + 1, y2);
                    a->key = x;
                }
            }
        }
        else if (a->direction == vertical) {
            int x2 = a->position[1].x;
            int y2 = a->position[1].y;
            //세로로 두칸인경우 그 위에 둔다
            if (y2 <= 3 && example[x2][y2 + 1] == 0) {
                a->priority = 1;
                Grid x(x2, y2 + 1);
                a->key = x;
            }
        }
        else if (a->direction == cross) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[1].x;
            int y2 = a->position[1].y;
            if (x2 == x1 + 1 && y2 == y1 + 1) {                                //우상향
                if (x1 >= 1) {                                                //'S00' 왼쪽
                    if (y1 == 1 && example[x1 - 1][y1 - 1] == 0) {
                        //S가 비어있고 그 아래가 벽일때
                        a->priority = 1;
                        Grid x(x1 - 1, y1 - 1);
                        a->key = x;
                    }
                    else if (y1 >= 2 && example[x1 - 1][y1 - 1] == 0 && example[x1 - 1][y1 - 2] != 0) {
                        //S가 비어있고 그 아래가 차있을때
                        a->priority = 1;
                        Grid x(x1 - 1, y1 - 1);
                        a->key = x;
                    }
                }
                if (a->priority != 1 && x2 <= 5 && y2 <= 3) {                //'00S' 오른쪽
                    //2개가 연속으로 놓인경우 이기려면 2개가 더필요하므로 높이 2가 더필요
                    if (example[x2 + 1][y2 + 1] == 0 && example[x2 + 1][y2] != 0) {
                        //S가 비어있고 그 아래가 차있을때
                        a->priority = 1;
                        Grid x(x2 + 1, y2 + 1);
                        a->key = x;
                    }
                }
            }
            else if (x2 == x1 - 1 && y2 == y1 + 1) {                        //좌상향
                if (x1 <= 5) {                                                //'00S' 오른쪽
                    if (y1 == 1 && example[x1 + 1][y1 - 1] == 0) {
                        //S가 비어있고 그 아래가 벽일때
                        a->priority = 1;
                        Grid x(x1 + 1, y1 - 1);
                        a->key = x;
                    }
                    else if (y1 >= 2 && example[x1 + 1][y1 - 1] == 0 && example[x1 + 1][y1 - 2] != 0) {
                        //S가 비어있고 그 아래가 차있을때
                        a->priority = 1;
                        Grid x(x1 + 1, y1 - 1);
                        a->key = x;
                    }
                }
                if (a->priority != 1 && x2 >= 1 && y2 <= 3) {                //'S00' 왼쪽
                    //2개가 연속으로 놓인경우 이기려면 2개가 더필요하므로 높이 2가 더필요
                    if (example[x2 - 1][y2 + 1] == 0 && example[x2 - 1][y2] != 0) {
                        //S가 비어있고 그 아래가 차있을때
                        a->priority = 1;
                        Grid x(x2 - 1, y2 + 1);
                        a->key = x;
                    }
                }
            }
        }
    }
    else if (a->shape == 4) {
        if (a->direction == horizontal) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[1].x;
            int y2 = a->position[1].y;
            //'0S0'
            if (y1 == 0 && example[x1 + 1][y1] == 0) {
                //S가 비어있고 S아래가 벽일때
                a->priority = 1;
                Grid x(x1 + 1, y1);
                a->key = x;
            }
            else if (y1 >= 1 && example[x1 + 1][y1] == 0 && example[x1 + 1][y1 - 1] != 0) {
                //S가 비어있고 S아래가 차있을때
                a->priority = 1;
                Grid x(x1 + 1, y1);
                a->key = x;
            }
        }
        else if (a->direction == cross) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[1].x;
            int y2 = a->position[1].y;
            if (x2 == x1 + 2 && y2 == y1 + 2) {                        //우상향
                if (example[x1 + 1][y1 + 1] == 0 && example[x1 + 1][y1] != 0) {
                    //S가 비어있고 아래가 차있을때
                    a->priority = 1;
                    Grid x(x1 + 1, y1 + 1);
                    a->key = x;
                }
            }
            else if (x2 == x1 - 2 && y2 == y1 + 2) {                //좌상향
                if (example[x1 - 1][y1 + 1] == 0 && example[x1 - 1][y1] != 0) {
                    //S가 비어있고 아래가 차있을때
                    a->priority = 1;
                    Grid x(x1 - 1, y1 + 1);
                    a->key = x;
                }
            }
        }
    }
    else if (a->shape == 5) {
        if (a->direction == horizontal) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[1].x;
            int y2 = a->position[1].y;
            //'0SP0'
            if (y1 == 0 && example[x1 + 1][y1] == 0) {
                //S가 비었고 S아래가 벽일때
                a->priority = 1;
                Grid x(x1 + 1, y1);
                a->key = x;
            }
            else if (y1 == 0 && example[x1 + 2][y1] == 0) {
                //P가 비었고 P아래가 벽일때
                a->priority = 1;
                Grid x(x1 + 2, y1);
                a->key = x;
            }
            else if (y1 >= 1 && example[x1 + 1][y1] == 0 && example[x1 + 1][y1 - 1] != 0) {
                //S가 비었고 S아래가 차있을때
                a->priority = 1;
                Grid x(x1 + 1, y1);
                a->key = x;
            }
            else if (y1 >= 1 && example[x1 + 2][y1] == 0 && example[x1 + 2][y1 - 1] != 0) {
                //S가 비었고 S아래가 차있을때
                a->priority = 1;
                Grid x(x1 + 2, y1);
                a->key = x;
            }
        }
        else if (a->direction == cross) {
            int x1 = a->position[0].x;
            int y1 = a->position[0].y;
            int x2 = a->position[1].x;
            int y2 = a->position[1].y;
            //'0SP0'
            if (x2 == x1 + 3 && y2 == y1 + 3) {                    //우상향
                if (example[x1 + 1][y1 + 1] == 0 && example[x1 + 1][y1] != 0) {
                    //S가 비어있고 S아래가 차있을때
                    a->priority = 1;
                    Grid x(x1 + 1, y1 + 1);
                    a->key = x;
                }
                else if (example[x1 + 2][y1 + 2] == 0 && example[x1 + 2][y1 + 1] != 0) {
                    //P가 비어있고 P아래가 차있을때
                    a->priority = 1;
                    Grid x(x1 + 2, y1 + 2);
                    a->key = x;
                }
            }
            else if (x2 == x1 - 3 && y2 == y1 + 3) {            //좌상향
                if (example[x1 - 1][y1 + 1] == 0 && example[x1 - 1][y1] != 0) {
                    //S가 비어있고 S아래가 차있을때
                    a->priority = 1;
                    Grid x(x1 - 1, y1 + 1);
                    a->key = x;
                }
                else if (example[x1 - 2][y1 + 2] == 0 && example[x1 - 2][y1 + 1] != 0) {
                    //P가 비어있고 P아래가 차있을때
                    a->priority = 1;
                    Grid x(x1 - 2, y1 + 2);
                    a->key = x;
                }
            }
        }
    }
}

