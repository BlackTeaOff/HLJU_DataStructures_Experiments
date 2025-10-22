#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

void createTree(treeNode** T) {
    int n;
    scanf("%d", &n);
    if (n == 0) { // n=0时, 代表当前结点为NULL
        *T = NULL; // *T代表T指向(存储)的指针指向的地址
        return; // T代表T指向的指针的地址
    }
    treeNode* node = malloc(sizeof(treeNode));
    node->data = n; // 前序, 中左右
    *T = node; // 在函数内修改了指针指向的地址, 需用二级指针
    createTree(&((*T)->left)); // 传入左指针的地址
    createTree(&((*T)->right)); // 二级指针, 传入指针的地址
}

void preOrder(treeNode* T) {
    if (T == NULL) { // basecase
        return;
    }
    printf("%d ", T->data);
    preOrder(T->left);
    preOrder(T->right); 
}

int getHeight(treeNode* T) { // 每次返回该结点下的最大深度
    if (T == NULL) {
        return 0; // 顺序左右中
    }
    int leftHeight = getHeight(T->left); // 该结点下左子树的深度
    int rightHeight = getHeight(T->right); // 该结点下右子树的深度
    int height = leftHeight>rightHeight?leftHeight:rightHeight; // 谁大返回谁
    return height + 1; // 返回左右子树最大的深度加上自己, 返回给上一个节点, 上一个结点继续找
}

int main() {
    treeNode* tree = NULL;
    createTree(&tree);
    preOrder(tree);
    printf("\n");
    printf("%d\n", getHeight(tree));
    return 0;
}