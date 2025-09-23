#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct node { // Double_List
    struct node *prev;
    int data;
    int freq;
    struct node *next;
} Node;

Node* initDList() {
    Node *head = malloc(sizeof(Node));
    head->prev = NULL;
    head->data = 0;
    head->freq = 0;
    head->next = NULL;
    return head;
}

void addFirst(Node *head, int e) { // 双链表头插法
    if (head == NULL) {
        printf("链表未初始化\n");
        return;
    }
    Node *p = malloc(sizeof(Node));
    p->data = e;
    p->freq = 0;
    p->prev = head;
    p->next = head->next;
    if (head->next != NULL) { // 防止链表只有一个头节点时, head->next为NULL导致异常
        head->next->prev = p;
    }
    head->next = p;
}

void listNode(Node *head) {
    if (head == NULL) {
        printf("链表未初始化\n");
        return;
    }
    if (head->next == NULL) {
        printf("该链表只有头节点\n");
        return;
    }
    Node *p = head->next;
    while (p != NULL) {
        printf("%d(%d) ", p->data, p->freq);
        p = p->next;
    }
    printf("\n");
}

void Locate(Node *head, int x) {
    if (head == NULL)
    {
        printf("链表未初始化\n");
        return;
    }
    if (head->next == NULL)
    {
        printf("该链表只有头节点\n");
        return;
    }
    Node *p = head->next;
    while (p != NULL) { // 找到值为x的节点, 并把freq+1
        if (p->data == x) {
            p->freq++;
            break;
        }
        p = p->next;
    }
    if (p == NULL) {
        printf("未找到该节点\n");
        return;
    }
    // 将p从链表中拆下
    p->prev->next = p->next; // p的前节点的next等于p的下一个节点
    if (p->next != NULL) { // 防止p为最后一个节点, 这样的话p就没有下一个节点了
        p->next->prev = p->prev; // 把p的下一个节点的prev设为p的前一个节点
    }
    p->next = NULL; // p前后都断开
    p->prev = NULL;

    Node *q = head; // 用q指针辅助插入p节点
    while (q->next != NULL) { // 判断q的下一个节点与p的freq大小, 决定插入的位置
        if (q->next->freq < p->freq) { // q->next的freq如果小于p的freq, 就把p插在q与q->next之间
            p->prev = q; // 与头插法类似, 就是把q当成"头指针"了
            p->next = q->next;
            q->next->prev = p;
            q->next = p;
            listNode(head);
            return;
        }
        q = q->next;
    }
    q->next = p; // 插在最后的情况
    p->prev = q;
    listNode(head);
}

int main() {
    Node *DList = initDList();
    addFirst(DList, 6);
    addFirst(DList, 5);
    addFirst(DList, 4);
    addFirst(DList, 3);
    addFirst(DList, 2);
    addFirst(DList, 1);
    listNode(DList);
    printf("输入值x: ");
    int x = 0;
    while ((scanf("%d", &x)) != EOF) {
        Locate(DList, x);
        printf("输入值x: ");
    }
}