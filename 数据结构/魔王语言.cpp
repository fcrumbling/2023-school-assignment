#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 101

typedef struct Stack{
    int top;
    char *array;
}Stack;

Stack* CreatStack(){
    Stack *S=(Stack*)malloc(sizeof(Stack));
    S->array=(char*)malloc(sizeof(char)*maxsize);
    S->top=0;
    return S;
}

void pushA(Stack*S) {
    S->array[S->top] = 's';
    S->top++;
    S->array[S->top] = 'a';
    S->top++;
    S->array[S->top] = 'e';
    S->top++;
}

void pushB(Stack* S) {
    S->array[S->top] = 't';
    S->top++;
    pushA(S);
    S->array[S->top] = 'd';
    S->top++;
    pushA(S);
}

void push(Stack* S, char ch) {
    if (ch == 'A')pushA(S);
    else if (ch == 'B')pushB(S);
    else {
        S->array[S->top] = ch;
        S->top++;
    }
}

void pop(Stack *S){
    S->top--;
}

int StackEmpty(Stack *S){//1±íÊ¾¿Õ
    if (S->top==0) return 1;
    else return 0;
}

char GetTop(Stack *S){
    return S->array[S->top-1];
}

typedef struct Quene {
    int length;
    char *array;
}Quene;

Quene* head = NULL;

Quene* CreateQuene() {
    Quene* Q = (Quene*)malloc(sizeof(Quene));
    Q->length = 0;
    Q->array = (char*)malloc(sizeof(char) * maxsize);
    return Q;
}

void enQueneA(Quene* Q) {
    Q->array[Q->length] = 's';
    Q->length++;
    Q->array[Q->length] = 'a';
    Q->length++;
    Q->array[Q->length] = 'e';
    Q->length++;
}

void enQueneB(Quene* Q) {
    Q->array[Q->length] = 't';
    Q->length++;
    enQueneA(Q);
    Q->array[Q->length] = 'd';
    Q->length++;
    enQueneA(Q);
}

void enQuene(Quene*Q,char ch) {
    if (ch == 'A') enQueneA(Q);
    else if (ch == 'B') enQueneB(Q);
    else {
        Q->array[Q->length] = ch;
        Q->length++;
    }
}

void enQuenerule(Quene* Q,Stack*S,char t) {
    char top;
    while (GetTop(S) != t) {
        top = GetTop(S);
        enQuene(Q, t);
        enQuene(Q, top);
        pop(S);
    }
    enQuene(Q, t);
    pop(S);
    pop(S);
}


int main() {
    char input[100],t;
    int i,flag=0;
    fgets(input, sizeof(input), stdin);
    Stack *S = CreatStack();
    Quene* Q = CreateQuene();
    head = Q;
    for (i = 0; i < sizeof(input); i++)
    {
        if (flag == 1 && input[i] == ')') {
            flag = 0;
            enQuenerule(Q, S, t);
        }
        else if (flag == 1 && input[i]!=')') {
            push(S, input[i]);
        }
        else if (flag == 0 && input[i] == '(') {
            flag = 1;
            t = input[i + 1];
            push(S, input[i]);
        }
        else {
            enQuene(Q, input[i]);
        }
    }
    if (flag==1)
    {
        enQuenerule(Q, S, t);
    }
    printf("%s", Q->array);
    free(Q);
    free(S);
    return 0;
}