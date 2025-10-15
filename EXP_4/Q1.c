#define MAXSIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *next;
} Node;

typedef struct {
    char data[MAXSIZE];
    int top;
} Stack;

Node* initList() {
    Node *head = malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

void addFirst(Node *head, char e) {
    if (head == NULL) {
        printf("链表未初始化\n");
        return;
    }

    Node *newNode = malloc(sizeof(Node));
    newNode->data = e;
    newNode->next = head->next;
    head->next = newNode;
    return;
}

void printList(Node *head) {
    if (head == NULL) {
        printf("该链表未初始化\n");
        return;
    }

    Node *p = head->next;
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
    return;
}

void initStack(Stack *s) { // 静态内存分配
    s->top = -1;
    return;
}

void push(Stack *s, char e) { // 入栈
    if (s->top >= MAXSIZE - 1) { // 因为top是数组的下标, 从0开始
        printf("栈已满\n");
        return;
    }

    s->top++;
    s->data[s->top] = e; // 在栈顶放入e
    return;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("栈为空\n");
        return ' ';
    }

    char e = s->data[s->top];
    s->top--;
    return e;
}

void isSym(Node *head) {
    if (head == NULL) {
        printf("链表未初始化\n");
        return;
    }

    Node *fast = head->next; // 快慢指针找中点
    Node *slow = head->next;
    Stack s;
    initStack(&s);

    while (fast != NULL && fast->next != NULL) { // 其中一个为假则为假, 先判断前面的
        push(&s, slow->data);
        fast = fast->next->next;
        slow = slow->next;
    }
    if (fast != NULL) { // 如果fast不是NULL, 代表共有奇数个字符, slow指向最中间的字符
        slow = slow->next; // 需要把slow向后移一位来准备比较
    }
    while (pop(&s) == slow->data) { // 把出栈符号和字符链表后半部分比较
        slow = slow->next;
        if (slow == NULL) { // 全比较完了, 则对称
            printf("该字符串对称\n");
            return;
        }
    }
    printf("该字符串不对称\n"); // 若提前退出循环, 则不对称
    return;
}

int main() {
    Node *L_1 = initList(); // xyzzyx
    addFirst(L_1, 'x');
    addFirst(L_1, 'y');
    addFirst(L_1, 'z');
    addFirst(L_1, 'z');
    addFirst(L_1, 'y');
    addFirst(L_1, 'x');
    printList(L_1);
    isSym(L_1);

    Node *L_2 = initList(); // xyzyx
    addFirst(L_2, 'x');
    addFirst(L_2, 'y');
    addFirst(L_2, 'z');
    addFirst(L_2, 'y');
    addFirst(L_2, 'x');
    printList(L_2);
    isSym(L_2);

    Node *L_3 = initList(); // xxzyx
    addFirst(L_3, 'x');
    addFirst(L_3, 'y');
    addFirst(L_3, 'z');
    addFirst(L_3, 'x');
    addFirst(L_3, 'x');
    printList(L_3);
    isSym(L_3);
}