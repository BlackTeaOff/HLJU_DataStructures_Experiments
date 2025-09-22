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


Node* addFirst(Node *head, int e) { // 头插法(无头节点，非空表时无需更新头指针，交换头指针与新节点的数据)
    Node *new = malloc(sizeof(Node));
    new->data = e;

    if (head == NULL) {
        new->next = new; // 自己指向自己
        return new; // 新节点为头节点
     }

     new->next = head->next;
     head->next = new;

     int temp = head->data;
     head->data = new->data;
     new->data = temp;

     return head;
}

/*
void addFirst(Node *head, int e) { // 头插法(有头节点)
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

Node* deletePrev(Node *head, Node *s) { // 传入头指针，如果头指针被删除，更新其到s(下一节点)
    if (s == NULL) {
        printf("传入节点无效\n");
        return head;
    }
    Node *p = s;
    while (p->next->next != s) { // 遍历直到p的下下个节点为s，则要删除的节点就是p的下个节点
        p = p->next;
    }
    Node *q = p->next;
    if (q == head) { // 被删除的节点是头指针指向的
        head = s; // 把头指针指向下一节点s
    }
    p->next = s; // 直接把p连接到s节点(即被删掉的后一个节点)
    free(q);
    return head;
}
/*
void deletePrev(Node *s) { // 删除单循环链表中s指针指向的节点的前驱
    if (s == NULL) {
        printf("传入节点无效\n");
        return;
    }
    Node *p = s->next;
    Node *q = p->next;
    while (q->next != s) { // q->next == s时，该q指向的节点就是要删除的节点
        p = p->next;
        q = q->next;
    }
    p->next = q->next;
    free(q);
    return;
}
*/

Node* findNode(Node *head, int e) { // 只适用于单向循环链表 
    if (head == NULL) {
        printf("链表未初始化\n");
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
    printf("未找到该节点\n");
    return NULL;
}

/*
void listNode(Node *head) { // 有头节点
    if (head == NULL) {
        printf("链表未初始化\n");
        return;
    }
    Node *p = head->next;
    while (p != head) { // 单项循环链表遍历判断条件是再次经过一次头节点时
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
*/

void listNode(Node *head) { // 无头节点
    if (head == NULL)
    {
        printf("链表未初始化\n");
        return;
    }
    Node *p = head;
    printf("%d ", p->data);
    p = p->next;
    while (p != head)
    { // 单项循环链表遍历判断条件是再次经过一次头节点时
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    Node *L = NULL;
    L = addFirst(L, 5); // 第一个节点返回头节点的地址
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
    printf("请输入某个整数: ");
    int a;
    scanf("%d", &a);
    L = deletePrev(L, findNode(L, a));
    listNode(L);
}

