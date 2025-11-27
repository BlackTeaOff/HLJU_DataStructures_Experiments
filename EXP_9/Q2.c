#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct node {
    int data;
    struct node* lchild;
    struct node* rchild;
} TreeNode;

int compare;

TreeNode* BSTSearch(TreeNode* T, int data) { // 传入根结点地址与要查找的值
    if (T == NULL) { // 等于NULL代表没找到
        return NULL;
    }
    if (data == T->data) { // 相等就返回这个结点的地址
        compare++;
        return T;
    } else if (data < T->data) { // data小于结点的值
        compare++;
        return BSTSearch(T->lchild, data); // 就去这个结点的左子树找
    } else { // data大于结点的值
        compare++;
        return BSTSearch(T->rchild, data); // 就去这个结点的右子树找
    }
}

// 因为要修改指针指向的值, 所以要使用二级指针
void createBST(TreeNode** T, int data) { // 二级指针存的是指针的地址, 通过解二级指针可以得到一级指针指向的结点
    if (*T == NULL) { // 一级指针指向NULL, 就可以把这个指针指向新创建的结点
        *T = malloc(sizeof(TreeNode));
        (*T)->data = data;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
    } else if (data < (*T)->data) { // 如果data小于当前结点的data
        createBST(&(*T)->lchild, data); // 去左子树创建新节点
    } else { // data大于当前结点data
        createBST(&(*T)->rchild, data); // 去右子树创建新结点
    }
}

TreeNode* deleteNode(TreeNode* T, int data) {
    if (T == NULL) {
        return NULL;
    }
    if (data < T->data) { // 要找的结点小于当前结点, 递归删除左子树上的节点
        T->lchild = deleteNode(T->lchild, data); // 因为该结点的左子树会被改变, 所以让这个结点的左子树等于删除结点后的子树(返回值)
        return T;
    } else if (data > T->data) { // 要找的结点大于当前结点, 递归删除右子树上的结点
        T->rchild = deleteNode(T->rchild, data);
        return T;
    } else if (data == T->data) { // 删除分四种情况
        // 1. 要删除的结点没有左右子树
        if (T->lchild == NULL && T->rchild == NULL) {
            free(T); // 直接删除该节点
            return NULL; // 给上面的结点左右孩子指针返回NULL
        } else if (T->lchild != NULL && T->rchild == NULL) {
            // 2. 要删除的结点有左孩子但是没有右孩子, 让该结点的左孩子替代要删除的结点
            TreeNode* temp = T->lchild; // 保存该结点的左孩子
            free(T);
            return temp; // 直接返回这个左孩子给上面结点的左右孩子指针
        } else if (T->lchild == NULL && T->rchild != NULL) {
            // 3. 要删除结点没有左孩子但是有右孩子, 让该结点的右孩子代替要删除的节点
            TreeNode* temp = T->rchild;
            free(T);
            return temp; // 把这个右孩子返回给上面结点的左右指针
        } else if (T->lchild != NULL && T->rchild != NULL) {
            // 4. 要删除的结点左右子树都有
            // 4.1 让要删除结点的左子树都放在右子树最小节点的左子树上(因为左子树一定比所有右子树的值小, 只能放在右子树最小结点的左面(最小的地方))
                // 让修改后的右子树代替要删除的结点

            TreeNode* cur = T->rchild; // 去找右子树的最小结点
            while (cur->lchild != NULL) { // 在右子树一直向左找
                cur = cur->lchild;
            }
            cur->lchild = T->lchild; // 把要删除结点的左子树放在右子树最小结点的左面
            TreeNode* temp = T->rchild; // 把该右子树存起来
            free(T);
            return temp; // 返回该右子树到上面结点的左右指针
        }
    }
    return T; // 没找到就返回自己(没变化)
}

void inOrder(TreeNode* T) { // 中序遍历二叉排序树输出为从小到大(顺序左中右)
    if (T == NULL) {
        return;
    }
    inOrder(T->lchild);
    printf("%d ", T->data);
    inOrder(T->rchild);
}

int main() {
    srand((unsigned)time(NULL));

    TreeNode* T = NULL;

    int choice;
    while (1) {
        printf("----------\n");
        printf("1-建立\n");
        printf("2-输出\n");
        printf("3-插入\n");
        printf("4-查找\n");
        printf("5-删除\n");
        printf("0-退出\n");
        printf("----------\n");

        scanf("%d", &choice);
        switch (choice) {
            case 1 : {
                int length;
                int range_start;
                int range_end;
                int range;

                printf("请输入正整数的个数: ");
                scanf("%d", &length);
                printf("请输入正整数的取值范围: ");
                scanf("%d %d", &range_start, &range_end);
                range = range_end - range_start;

                printf("该组数据: ");
                int arr[length];
                for (int i = 0; i < length; i++) {
                    arr[i] = rand() % range + range_start;
                    createBST(&T, arr[i]);
                    printf("%d ", arr[i]);
                }
                printf("\n");

                break;
            }
            case 2 :
                inOrder(T);
                printf("\n");
                break;
            case 3 : {
                int data;
                printf("请输入要插入的值: ");
                scanf("%d", &data);
                createBST(&T, data);
                printf("插入完成\n");
                break;
            }
            case 4 : {
                compare = 0;
                int data;
                printf("请输入要查找的值: ");
                scanf("%d", &data);
                
                TreeNode *result = BSTSearch(T, data);
                if (result != NULL) {
                    printf("在树中查找到该值%d, 比较次数为%d\n", result->data, compare);
                } else {
                    printf("未找到该值\n");
                }
                break;
            }
            case 5 : {
                int data;
                printf("请输入要删除结点的值: ");
                scanf("%d", &data);
                T = deleteNode(T, data);
                break;
            }
            case 0 :
                return 0;
        }
    }
    /*
    int arr[] = {5, 8, 2, 3, 1, 0, 10};
    for (int i = 0; i < 6; i++) {
        createBST(&T, arr[i]);
    }
    inOrder(T);
    */
}