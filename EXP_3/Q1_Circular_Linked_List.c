#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* initList() {
    Node *head = malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}


Node* addFirst(Node *head, int e) { // ͷ�巨(��ͷ�ڵ㣬�ǿձ�ʱ�������ͷָ�룬����ͷָ�����½ڵ������)
    Node *new = malloc(sizeof(Node));
    new->data = e;

    if (head == NULL) {
        new->next = new; // �Լ�ָ���Լ�
        return new; // �½ڵ�Ϊͷ�ڵ�
     }

     new->next = head->next;
     head->next = new;

     int temp = head->data;
     head->data = new->data;
     new->data = temp;

     return head;
}

/*
void addFirst(Node *head, int e) { // ͷ�巨(��ͷ�ڵ�)
    if (head->next == NULL) {
        Node *new = malloc(sizeof(Node));
        new->data = e;
        head->next = new;
        new->next = head;
        return;
    }
    Node *new = malloc(sizeof(Node));
    new->data = e;
    new->next = head->next;
    head->next = new;
    return;
}
*/

Node* deletePrev(Node *head, Node *s) { // ����ͷָ�룬���ͷָ�뱻ɾ���������䵽s(��һ�ڵ�)
    if (s == NULL) {
        printf("����ڵ���Ч\n");
        return head;
    }
    Node *p = s;
    while (p->next->next != s) { // ����ֱ��p�����¸��ڵ�Ϊs����Ҫɾ���Ľڵ����p���¸��ڵ�
        p = p->next;
    }
    Node *q = p->next;
    if (q == head) { // ��ɾ���Ľڵ���ͷָ��ָ���
        head = s; // ��ͷָ��ָ����һ�ڵ�s
    }
    p->next = s; // ֱ�Ӱ�p���ӵ�s�ڵ�(����ɾ���ĺ�һ���ڵ�)
    free(q);
    return head;
}
/*
void deletePrev(Node *s) { // ɾ����ѭ��������sָ��ָ��Ľڵ��ǰ��
    if (s == NULL) {
        printf("����ڵ���Ч\n");
        return;
    }
    Node *p = s->next;
    Node *q = p->next;
    while (q->next != s) { // q->next == sʱ����qָ��Ľڵ����Ҫɾ���Ľڵ�
        p = p->next;
        q = q->next;
    }
    p->next = q->next;
    free(q);
    return;
}
*/

Node* findNode(Node *head, int e) { // ֻ�����ڵ���ѭ������ 
    if (head == NULL) {
        printf("����δ��ʼ��\n");
        return NULL;
    }
    Node *p = head;
    if (p->data == e) {
        return p;
    } else {
        p = p->next;
    }
    while (p != head) {
        if (p->data == e) {
            return p;
        } else {
            p = p->next;
        }
    }
    printf("δ�ҵ��ýڵ�\n");
    return NULL;
}

/*
void listNode(Node *head) { // ��ͷ�ڵ�
    if (head == NULL) {
        printf("����δ��ʼ��\n");
        return;
    }
    Node *p = head->next;
    while (p != head) { // ����ѭ����������ж��������ٴξ���һ��ͷ�ڵ�ʱ
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
*/

void listNode(Node *head) { // ��ͷ�ڵ�
    if (head == NULL)
    {
        printf("����δ��ʼ��\n");
        return;
    }
    Node *p = head;
    printf("%d ", p->data);
    p = p->next;
    while (p != head)
    { // ����ѭ����������ж��������ٴξ���һ��ͷ�ڵ�ʱ
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    Node *L = NULL;
    L = addFirst(L, 5); // ��һ���ڵ㷵��ͷ�ڵ�ĵ�ַ
    addFirst(L, 4);
    addFirst(L, 3);
    addFirst(L, 2);
    addFirst(L, 1);
    listNode(L);
    // Node *L = malloc(sizeof(Node));
    // L->data = 1;
    // L->next = malloc(sizeof(Node));
    // L->next->data = 2;
    // L->next->next = malloc(sizeof(Node));
    // L->next->next->data = 3;
    // L->next->next->next = malloc(sizeof(Node));
    // L->next->next->next->data = 4;
    // L->next->next->next->next = malloc(sizeof(Node));
    // L->next->next->next->next->data = 5;
    // L->next->next->next->next->next = L;
    printf("������ĳ������: ");
    int a;
    scanf("%d", &a);
    L = deletePrev(L, findNode(L, a));
    listNode(L);
}

