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

void addFirst(Node *head, int e) { // ˫����ͷ�巨
    if (head == NULL) {
        printf("����δ��ʼ��\n");
        return;
    }
    Node *p = malloc(sizeof(Node));
    p->data = e;
    p->freq = 0;
    p->prev = head;
    p->next = head->next;
    if (head->next != NULL) { // ��ֹ����ֻ��һ��ͷ�ڵ�ʱ, head->nextΪNULL�����쳣
        head->next->prev = p;
    }
    head->next = p;
}

void listNode(Node *head) {
    if (head == NULL) {
        printf("����δ��ʼ��\n");
        return;
    }
    if (head->next == NULL) {
        printf("������ֻ��ͷ�ڵ�\n");
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
        printf("����δ��ʼ��\n");
        return;
    }
    if (head->next == NULL)
    {
        printf("������ֻ��ͷ�ڵ�\n");
        return;
    }
    Node *p = head->next;
    while (p != NULL) { // �ҵ�ֵΪx�Ľڵ�, ����freq+1
        if (p->data == x) {
            p->freq++;
            break;
        }
        p = p->next;
    }
    if (p == NULL) {
        printf("δ�ҵ��ýڵ�\n");
        return;
    }
    // ��p�������в���
    p->prev->next = p->next; // p��ǰ�ڵ��next����p����һ���ڵ�
    if (p->next != NULL) { // ��ֹpΪ���һ���ڵ�, �����Ļ�p��û����һ���ڵ���
        p->next->prev = p->prev; // ��p����һ���ڵ��prev��Ϊp��ǰһ���ڵ�
    }
    p->next = NULL; // pǰ�󶼶Ͽ�
    p->prev = NULL;

    Node *q = head; // ��qָ�븨������p�ڵ�
    while (q->next != NULL) { // �ж�q����һ���ڵ���p��freq��С, ���������λ��
        if (q->next->freq < p->freq) { // q->next��freq���С��p��freq, �Ͱ�p����q��q->next֮��
            p->prev = q; // ��ͷ�巨����, ���ǰ�q����"ͷָ��"��
            p->next = q->next;
            q->next->prev = p;
            q->next = p;
            listNode(head);
            return;
        }
        q = q->next;
    }
    q->next = p; // �����������
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
    printf("����ֵx: ");
    int x = 0;
    while ((scanf("%d", &x)) != EOF) {
        Locate(DList, x);
        printf("����ֵx: ");
    }
}