#define MAXSIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode
{
    int data;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

typedef struct {
    treeNode* data[MAXSIZE];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, treeNode* e) {
    if (s->top >= MAXSIZE - 1) {
        printf("栈已满\n");
        return;
    }
    s->top++;
    s->data[s->top] = e;
}

treeNode* pop(Stack* s) {
    if (s->top <= -1) {
        printf("栈为空\n");
        return NULL;
    }
    treeNode* e = s->data[s->top];
    s->top--;
    return e;
}

int isEmpty(Stack* s) {
    if (s->top <= -1) {
        return 1;
    } else {
        return 0;
    }
}

treeNode* getTop(Stack *s) {
    if (s->top <= -1) {
        printf("栈为空\n");
        return NULL;
    }
    return s->data[s->top];
}

void createTree(treeNode** T) {
    int n;
    scanf("%d", &n);
    if (n == 0) {
        *T = NULL;
        return;
    }
    treeNode* node = malloc(sizeof(treeNode));
    node->data = n;
    *T = node;
    createTree(&(*T)->left);
    createTree(&(*T)->right);
}

void RpreOrder(treeNode* T) { // R - recursive
    if (T == NULL) {
        return;
    }
    printf("%d ", T->data);
    RpreOrder(T->left);
    RpreOrder(T->right);
}

void IpreOrder(treeNode* T) { // I - iterative 迭代
    Stack s;
    initStack(&s);
    while (T != NULL || !isEmpty(&s)) { // 满足一个即可
        if (T != NULL) {
            printf("%d ", T->data);
            push(&s, T);
            T = T->left;
        } else {
            T = pop(&s);
            T = T->right;
        }
    }
}

void IinOrder(treeNode* T) { // 左中右
    Stack s;
    initStack(&s);
    while (T != NULL || !isEmpty(&s)) {
        if (T != NULL) {
            push(&s, T); 
            T = T->left; // 先左
        } else {
            T = pop(&s); // 左子树遍历完, 出栈来找到上一个节点
            printf("%d ", T->data); // 中
            T = T->right; // 右
        }
    }
}

void IpostOrder(treeNode* T) { // 左右中
    Stack s;
    initStack(&s);
    treeNode* r; // 保存上一次访问过的结点
    while (T != NULL || !isEmpty(&s))
    {
        while (T != NULL) { // 如果当前结点不为空, 就一直入栈, 并找左子结点
            push(&s, T);
            T = T->left;
        }
        T = getTop(&s); // T = NULL时, 通过栈获取栈顶元素(上一个结点, 已经遍历完左)
        if (T->right != NULL && r != T->right) { // 有右子结点而且上一次没访问过, 就指右
            T = T->right;
        } else { // 如果没有右子结点, 或者右子结点已经被访问, 就出栈执行-中-步骤
            pop(&s);
            printf("%d ", T->data);
            r = T; // 保存这次访问过的结点
            T = NULL; // 防止重复入栈
        }
    }
}

int main() {
    freopen("Q3_input.txt", "r", stdin); // 把文本文件里的内容作为输入
    treeNode* tree;
    createTree(&tree);
    RpreOrder(tree);
    printf("\n");
    IpreOrder(tree);
    printf("\n");
    IinOrder(tree);
    printf("\n");
    IpostOrder(tree);
    printf("\n");
}