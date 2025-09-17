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

void reverse(Node *head) {
    if (head == NULL) {
        printf("该链表未初始化\n");
        return;
    }
    else if (head->next == NULL) {
        printf("该链表只有一个节点\n");
        return;
    }
    Node *pre = NULL; // 可以直接让第一个节点(逆转后的最后一个节点next为NULL)
    Node *cur = head->next;
    Node *next = NULL;
    while (cur != NULL) {
        next = cur->next; // 保存目标(cur)的下一个节点
        cur->next = pre; // 反向连接上一个节点
        pre = cur; // 把节点都向后移动一位
        cur = next;
    }
    head->next = pre; // 把原来的最后一个节点，与头节点相连(cur现在指向NULL)
}

/*
void reverse(Node *head) {
    if (head == NULL) {
        printf("链表未初始化\n");
        return;
    }
    Node *pre = head->next;
    if (pre->next == NULL) {
        printf("该链表只有一个节点(除头节点)\n");
        return;
    }
    Node *this = pre->next;
    Node *next;
    if (this->next != NULL) { // 如果this->next == NULL，代表只有两个节点(除头节点)
        next = this->next;
    } else { // 只有两个节点的情况，pre和this，this->next == NULL，直接调换pre和this
        this->next = pre;
        pre->next = NULL;
        head->next = this;
        return;
    }
    pre->next = NULL;
    while (next->next != NULL) { // 三个及三个以上节点的情况，直到next的下一位是NULL，即到了最后一个节点
        this->next = pre; // 反向连接节点
        pre = this; //所有指针后移一位
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