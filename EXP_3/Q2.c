#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct node {
    char data;
    struct node *next;
} Node;

Node* initList() {
    Node *head = malloc(sizeof(Node));
    head->data = '0';
    head->next = NULL;
    return head;
}

void addFirst(Node *head, char e) { // ������ͷ�巨
    if (head == NULL) {
        printf("������δ��ʼ��\n");
        return;
    }
    Node *new = malloc(sizeof(Node));
    new->data = e;
    new->next = head->next;
    head->next = new;
    return;
} 

void listNode(Node *head) { // ������
    if (head == NULL) {
        printf("����δ��ʼ��\n");
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

void listCirNode(Node *head) { // ����ѭ������
    if (head == NULL) {
        printf("������δ��ʼ��\n");
        return;
    }
    Node *p = head->next;
    while (p != head) { // ��head��ֹͣ
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
    return;
}

void classify(Node *head, Node *h1, Node *h2, Node *h3) {
    // Node *h1 = malloc(sizeof(Node)); // ����
    // Node *h2 = malloc(sizeof(Node)); // ��ĸ
    // Node *h3 = malloc(sizeof(Node)); // ����
    Node *t1 = h1; // βָ��(tail), β�巨ʹ��
    Node *t2 = h2; // βָ�벻��Ҫ������, �������ڲ����弴��
    Node *t3 = h3;

    while (head->next != NULL) {
        Node *p = head->next;
        head->next = p->next; // ��p�ڵ�ȡ����
        if (p->data >= '0' && p->data <= '9') { // ʵ����ASCII�ж�(char)
            t1->next = p; // βָ��ָ��Ľڵ����p
            p->next = h1; // β�ڵ�ָ��ͷ�ڵ�
            t1 = t1->next; // ����βָ�뵽p(���µ�β�ڵ�)
        } else if (p->data >= 'a' && p->data <= 'z') {
            t2->next = p;
            p->next = h2;
            t2 = t2->next;
        } else {
            t3->next = p;
            p->next = h3;
            t3 = t3->next;
        }
    }
}

int main() {
    Node *L = initList();
    addFirst(L, 'a');
    addFirst(L, '#');
    addFirst(L, 'n');
    addFirst(L, 'i');
    addFirst(L, '3');
    addFirst(L, '2');
    addFirst(L, '$');
    addFirst(L, 'h');
    addFirst(L, '!');
    addFirst(L, 'c');
    addFirst(L, '1');
    listNode(L);

    Node *h1 = malloc(sizeof(Node)); // ����
    h1->next = h1;
    Node *h2 = malloc(sizeof(Node)); // ��ĸ
    h2->next = h2;
    Node *h3 = malloc(sizeof(Node)); // ����
    h3->next = h3;
    classify(L, h1, h2, h3);
    listCirNode(h1);
    listCirNode(h2);
    listCirNode(h3);
}