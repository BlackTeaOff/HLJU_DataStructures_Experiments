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

void addFirst(Node *head, char e) { // 单链表头插法
    if (head == NULL) {
        printf("该链表未初始化\n");
        return;
    }
    Node *new = malloc(sizeof(Node));
    new->data = e;
    new->next = head->next;
    head->next = new;
    return;
} 

void listNode(Node *head) { // 单链表
    if (head == NULL) {
        printf("链表未初始化\n");
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

void listCirNode(Node *head) { // 遍历循环链表
    if (head == NULL) {
        printf("该链表未初始化\n");
        return;
    }
    Node *p = head->next;
    while (p != head) { // 到head就停止
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
    return;
}

void classify(Node *head, Node *h1, Node *h2, Node *h3) {
    // Node *h1 = malloc(sizeof(Node)); // 数字
    // Node *h2 = malloc(sizeof(Node)); // 字母
    // Node *h3 = malloc(sizeof(Node)); // 符号
    Node *t1 = h1; // 尾指针(tail), 尾插法使用
    Node *t2 = h2; // 尾指针不需要传出来, 所以在内部定义即可
    Node *t3 = h3;

    while (head->next != NULL) {
        Node *p = head->next;
        head->next = p->next; // 把p节点取下来
        if (p->data >= '0' && p->data <= '9') { // 实际用ASCII判断(char)
            t1->next = p; // 尾指针指向的节点接上p
            p->next = h1; // 尾节点指向头节点
            t1 = t1->next; // 更新尾指针到p(最新的尾节点)
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

    Node *h1 = malloc(sizeof(Node)); // 数字
    h1->next = h1;
    Node *h2 = malloc(sizeof(Node)); // 字母
    h2->next = h2;
    Node *h3 = malloc(sizeof(Node)); // 符号
    h3->next = h3;
    classify(L, h1, h2, h3);
    listCirNode(h1);
    listCirNode(h2);
    listCirNode(h3);
}