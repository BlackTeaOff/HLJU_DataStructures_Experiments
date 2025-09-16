#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* initList() { // 创建头节点
    Node *head = malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

int insertNode(Node *head, int pos, int e) { // pos从1开始
    if (pos == 0) {
        printf("插入位置错误\n");
        return 0;
    }
    Node *p = head;
    int i = 0;
    while (i < pos - 1) { // 把p指向要插入的位置之前的一个节点
        if (p == NULL) { // 无法尾插
            printf("插入位置超出范围or插在了末尾\n");
            return 0;
        }
        p = p->next;
        i++;
    }

    Node *q = malloc(sizeof(Node)); // 为新数据创建新节点
    q->data = e;
    q->next = p->next;
    p->next = q;
    return 1;
}

int insertTail(Node *head, int e) {
    if (head == NULL) {
        printf("链表表未初始化\n");
        return 0;
    }
    Node *p = head;
    while (p->next != NULL) { // 把p指向最后一个节点
        p = p->next;
    }

    Node *q = malloc(sizeof(Node));
    q->data = e;
    q->next = NULL;
    p->next = q;
    return 1;
}

void increasingOrder(Node *head, int e) {
    Node *p = head;
    Node *q = head->next;
    Node *new = malloc(sizeof(Node));
    new->next = NULL;
    new->data = e;
    while (q != NULL) {
        if (q->data > e) { // 找到要插入的位置
            new->next = p->next;
            p->next = new;
            return;
        }
        p = p->next;
        q = q->next;
    }
    p->next = new; // 值最大的情况
}

void listNode(Node *head) {
    if (head == NULL) {
        printf("链表未初始化\n");
        return;
    }
    Node *p = head->next; // 从头节点的下一个节点开始
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return;
}

int main() {
    Node *L = initList();
    insertTail(L, 1);
    insertTail(L, 2);
    insertTail(L, 3);
    insertTail(L, 5);
    insertTail(L, 6);
    increasingOrder(L, 4);
    listNode(L);
    increasingOrder(L, 0);
    listNode(L);
    increasingOrder(L, 10);
    listNode(L);
}