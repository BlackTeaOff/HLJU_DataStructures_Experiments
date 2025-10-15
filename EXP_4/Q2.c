#define MAXSIZE 100
#include <stdio.h>

typedef struct {
    char data[MAXSIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
    return;
}

void push(Stack *s, char e) {
    if (s->top >= MAXSIZE - 1) {
        printf("’ª“—¬˙\n");
        return;
    }
    s->top++;
    s->data[s->top] = e;
    return;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("’ªŒ™ø’\n");
        return ' ';
    }
    char e = s->data[s->top];
    s->top--;
    return e;
}

void pairedBrackets() {
    char str[100];
    scanf("%s", str);
    Stack s;
    initStack(&s);
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '(') {
            push(&s, str[i]);
        } else if (str[i] == ')') {
            if (s.top == -1) {
                printf("¿®∫≈≤ª≈‰∂‘\n");
                return;
            }
            pop(&s);
        }
        i++;
    }
    if (s.top == -1) {
        printf("¿®∫≈≈‰∂‘\n");
    } else {
        printf("¿®∫≈≤ª≈‰∂‘\n");
    }
    return;
}

int main() {
    pairedBrackets();
}