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

Node* merge(Node *head_a, Node *head_b) {
    if (head_a == NULL || head_b == NULL) {
        printf("有一链表未初始化\n");
        return NULL;
    }
    if (head_a->next == NULL || head_b->next == NULL) {
        printf("有一个链表为空表\n");
        return NULL;
    }
    Node *p = head_a->next;
    Node *q = head_b->next;
    Node *temp;
    Node *head_c = head_a; // 用a链表的头(用原表的空间)
    head_c->next = NULL; // 重置头节点
    while (p != NULL && q != NULL) { // 遍历到直到有一个链表为空
        if (p->data < q->data) { // 选小的值头插到c中，实现倒序(此为p更小的情况)
            temp = p; // 用temp临时存储要头插的节点
            p = p->next; // 节点p继续向下移动
        } else { // 此为q更小的情况
            temp = q; // 用temp存q(q更小)
            q = q->next;
        }
        temp->next = head_c->next; // 先把temp(要插入的节点)的next连接到head_c的next，否则等会会更新head_c->next
        head_c->next = temp; // 头插到c链表(更新头节点)
    }
    if (p != NULL) { // 把剩余节点都头插到c(此为p，也就是a链表还有剩余的情况)
        while (p != NULL) { // 遍历，直到a链表也为空
            temp = p;
            p = p->next;
            temp->next = head_c->next; // 头插到c
            head_c->next = temp; // 更新头节点
        }
    } else { // q(也就是b链表)有剩余的情况
        while (q != NULL) {
            temp = q;
            q = q->next;
            temp->next = head_c->next;
            head_c->next = temp;
        }
    }
    return head_c;
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
    listNode(L);
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

    Node *a = initList();
    Node *b = initList();
    insertTail(a, 1);
    insertTail(a, 3);
    insertTail(a, 5);
    listNode(a);
    insertTail(b, 2);
    insertTail(b, 4);
    insertTail(b, 6);
    listNode(b);
    listNode(merge(a, b));
}