#define MAXSIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int data[MAXSIZE]; // 存下标, 相当于存地址了
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int data) {
    if (s->top >= MAXSIZE - 1) {
        printf("栈已满\n");
        return;
    }
    s->top++;
    s->data[s->top] = data;
    return;
}

int pop(Stack* s) {
    if (s->top < 0) {
        printf("栈为空\n");
        return 0;
    }
    int e = s->data[s->top];
    s->top--;
    return e;
}

int isEmpty(Stack* s) {
    if (s->top <= -1) {
        return 1;
    } else {
        return 0;
    }
}

// void seqPreOrder(char* tree) {
//     Stack s;
//     initStack(&s);
//     int len = strlen(tree);
//     int i = 1;
//     while ((i < len && tree[i] != '#') || !isEmpty(&s)) { // 两个都为空时, 遍历结束
//         if (tree[i] != '#' && i < len) { // 超出数组范围也视为空
//             printf("%c ", tree[i]);
//             push(&s, i);
//             i *= 2;
//         } else {
//             i = pop(&s);
//             i = i * 2 + 1;
//         }
//     }
// }

void seqPreOrder(char* tree) {
    Stack s;
    initStack(&s);
    int len = strlen(tree);
    int i = 1;
    push(&s, i);
    while (!isEmpty(&s)) {
        i = pop(&s); // 栈顶元素出栈
        printf("%c ", tree[i]); // 中

        if (2 * i + 1 < len && tree[2 * i + 1] != '#') { // 右
            push(&s, 2 * i + 1); // 先把该结点(i)的右子树进栈, 因为栈先入后出, 先进栈的后处理
        }
        if (2 * i < len && tree[2 * i] != '#') { // 左
            push(&s, 2 * i);
        }
    }
}

int main() {
    char* tree = "#ABCDEF#";
    seqPreOrder(tree);
}