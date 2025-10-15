// UTF-8编码, 上面的实验大概都是GBK
#define MAXSIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* initCLlist(Node **rear) { // Circled Linked List
    Node *head = malloc(sizeof(Node)); // 二重指针, 指向函数外rear的地址, 可直接修改
    head->data = 0;
    head->next = head;
    *rear = head; // 修改函数外rear的指向, 这个*rear不再是复制体
    return head;
}

void inQuene(Node **rear, int e) {
    if (*rear == NULL) {
        printf("该链表未初始化\n");
        return;
    }
    Node *newNode = malloc(sizeof(Node));
    newNode->data = e;
    newNode->next = (*rear)->next;
    (*rear)->next = newNode;
    *rear = newNode;
}

int outQuene(Node *head, Node **rear) {
    if (head == NULL) {
        printf("该链表未初始化\n");
        return 0;
    }
    Node *q = head->next;
    if (q == head) {
        printf("只有头节点\n");
        return 0;
    }
    if (q->next == head) { // 如果删除的是最后一个节点, rear指向的节点
        *rear = head; // 则需要将函数外rear的地址重新指向head
    }
    int e = q->data;
    head->next = q->next;
    free(q);
    return e;
}

void emptyQuene(Node *head, Node **rear) {
    while (head->next != head) { // 一直出队, 直到只剩下头节点
        outQuene(head, rear);
    }
}

void printList(Node *head) {
    if (head == NULL) {
        printf("该链表未初始化\n");
        return;
    }
    Node *q = head->next;
    while (q != head) {
        printf("%d ", q->data);
        q = q->next;
    }
    printf("\n");
    printf("\n");
    return;
}

int main() {
    Node *rear;
    Node *L = initCLlist(&rear); // 传入rear本身的地址, 让函数内的二重指针指向这个rear本身的地址
    int i = -1; // 这样就可以在函数内直接修改rear的地址
    do {
        printf("1.入队\n");
        printf("2.出队\n");
        printf("3.置队空\n");
        if (scanf("%d", &i) == EOF) {
            break;
        }
        switch (i) {
            case 1:
                printf("输入入队数据: ");
                int e;
                scanf("%d", &e);
                printf("\n");
                inQuene(&rear, e); // 入队, 尾插, 只需要尾指针
                printList(L);
                break;
            case 2:
                outQuene(L, &rear);
                printList(L);
                break;
            case 3:
                emptyQuene(L, &rear);
                printList(L);
                break;
            default: // 第一次进入时, 进入default(因为i = -1, case没有相匹配的)
                break;
            }
    } while (i != 0);
}