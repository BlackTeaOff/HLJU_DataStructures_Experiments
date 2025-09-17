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

void reverse(Node *head) {
    if (head == NULL) {
        printf("������δ��ʼ��\n");
        return;
    }
    else if (head->next == NULL) {
        printf("������ֻ��һ���ڵ�\n");
        return;
    }
    Node *pre = NULL; // ����ֱ���õ�һ���ڵ�(��ת������һ���ڵ�nextΪNULL)
    Node *cur = head->next;
    Node *next = NULL;
    while (cur != NULL) {
        next = cur->next; // ����Ŀ��(cur)����һ���ڵ�
        cur->next = pre; // ����������һ���ڵ�
        pre = cur; // �ѽڵ㶼����ƶ�һλ
        cur = next;
    }
    head->next = pre; // ��ԭ�������һ���ڵ㣬��ͷ�ڵ�����(cur����ָ��NULL)
}

/*
void reverse(Node *head) {
    if (head == NULL) {
        printf("����δ��ʼ��\n");
        return;
    }
    Node *pre = head->next;
    if (pre->next == NULL) {
        printf("������ֻ��һ���ڵ�(��ͷ�ڵ�)\n");
        return;
    }
    Node *this = pre->next;
    Node *next;
    if (this->next != NULL) { // ���this->next == NULL������ֻ�������ڵ�(��ͷ�ڵ�)
        next = this->next;
    } else { // ֻ�������ڵ�������pre��this��this->next == NULL��ֱ�ӵ���pre��this
        this->next = pre;
        pre->next = NULL;
        head->next = this;
        return;
    }
    pre->next = NULL;
    while (next->next != NULL) { // �������������Ͻڵ�������ֱ��next����һλ��NULL�����������һ���ڵ�
        this->next = pre; // �������ӽڵ�
        pre = this; //����ָ�����һλ
        this = next;
        next = next->next;
    }
    next->next = this;
    this->next = pre;
    head->next = next;
    return;
}
*/

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
    reverse(L);
    listNode(L);

    Node *list = initList();
    insertTail(list, 1);
    insertTail(list, 2);
    insertTail(list, 3);
    listNode(list);
    reverse(list);
    listNode(list);
}