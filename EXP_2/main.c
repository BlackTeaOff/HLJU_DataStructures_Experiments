#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* initList() { // ����ͷ�ڵ�
    Node *head = malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

int insertNode(Node *head, int pos, int e) { // pos��1��ʼ
    if (pos == 0) {
        printf("����λ�ô���\n");
        return 0;
    }
    Node *p = head;
    int i = 0;
    while (i < pos - 1) { // ��pָ��Ҫ�����λ��֮ǰ��һ���ڵ�
        if (p == NULL) { // �޷�β��
            printf("����λ�ó�����Χor������ĩβ\n");
            return 0;
        }
        p = p->next;
        i++;
    }

    Node *q = malloc(sizeof(Node)); // Ϊ�����ݴ����½ڵ�
    q->data = e;
    q->next = p->next;
    p->next = q;
    return 1;
}

int insertTail(Node *head, int e) {
    if (head == NULL) {
        printf("�����δ��ʼ��\n");
        return 0;
    }
    Node *p = head;
    while (p->next != NULL) { // ��pָ�����һ���ڵ�
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
        if (q->data > e) { // �ҵ�Ҫ�����λ��
            new->next = p->next;
            p->next = new;
            return;
        }
        p = p->next;
        q = q->next;
    }
    p->next = new; // ֵ�������
}

void listNode(Node *head) {
    if (head == NULL) {
        printf("����δ��ʼ��\n");
        return;
    }
    Node *p = head->next; // ��ͷ�ڵ����һ���ڵ㿪ʼ
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