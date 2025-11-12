#define MAXSIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int **Matrix; // 邻接矩阵
    char *vertices; // 点集合
    int verNum; // 点的数量
    int edgeNum; // 边的数量
} Graph;

Graph* initGraph() {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->Matrix = NULL;
    g->vertices = NULL;
    g->verNum = 0;
    g->edgeNum = 0;
    return g;
}

void printMartix(int** Matrix, int len) {
    if (Matrix == NULL) {
        printf("未创建二维数组\n");
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            printf("%d ", Matrix[i][j]);
        }
        printf("\n");
    }
}

void createGraph(Graph *g) {
    printf("请输入点的数量: ");
    scanf("%d", &(g->verNum));
    printf("请输入边的数量: ");
    scanf("%d", &(g->edgeNum));
    printf("请输入各点的数据: ");
    g->vertices = (char *)malloc(sizeof(char) * g->verNum + 1); // 加上末尾'\0'
    for (int i = 0; i < g->verNum; i++) { // 输入点集
        scanf(" %c", &(g->vertices[i]));
    }
    g->vertices[g->verNum] = '\0';

    g->Matrix = malloc(sizeof(int *) * g->verNum); // 分配点数量的数组, 每一个指针指向一个数组
    for (int i = 0; i < g->verNum; i++) {
        g->Matrix[i] = malloc(sizeof(int) * g->verNum); // 给每一行数组分配内存
        for (int j = 0; j < g->verNum; j++) {
            g->Matrix[i][j] = 0; // 初始化这一行数组为0
        }
    }

    char a;
    char b;
    int index_a;
    int index_b;
    for (int i = 0; i < g->edgeNum; i++) { // 开始操作邻接矩阵
        index_a = -1;
        index_b = -1;
        printf("请输入与第%d条边相连的两个顶点: ", i + 1);
        scanf(" %c", &a); // 一个空格是为了去掉前面scanf在缓冲区产生的换行符
        scanf(" %c", &b);
        for (int j = 0; j < g->verNum; j++) {
            if (g->vertices[j] == a) { // 找字符a在点集中的位置
                index_a = j;
            }
            if (g->vertices[j] == b) { // 找字符b在点集中的位置
                index_b = j;
            } // 这两个位置对应邻接矩阵中的位置
        }
        if (index_a == -1 || index_b == -1) { // a和b至少有一个在点集里面不存在
                printf("至少有一个点不存在于点集中\n");
                return;
            }
        // printf("%d\n", index_a);
        // printf("%d\n", index_b);
        g->Matrix[index_a][index_b] = 1; // 无向图对称
        g->Matrix[index_b][index_a] = 1;
    }

    printf("图创建完成(邻接矩阵)\n");
    // printMartix(g->Matrix, g->verNum);
}

int DFS(Graph *g, int startIndex, int endIndex, int* visited, char* path, int pathIndex) {
    visited[startIndex] = 1; // 将当前访问结点标为已访问
    path[pathIndex] = g->vertices[startIndex]; // 将当前结点存入路径
    pathIndex++;

    if (startIndex == endIndex) { // 当前结点与目标结点相同时, 就找到了一条路径
        for (int i = 0; i < pathIndex; i++) {
            printf("%c ", path[i]);
        }
        printf("\n");
        return 1;
    }

    for (int i = 0; i < g->verNum; i++) { // 遍历当前结点邻接点
        if (g->Matrix[startIndex][i] == 1 && !visited[i]) { // 与下标为i的点邻接, 且该点没有被遍历过
            if (DFS(g, i, endIndex, visited, path, pathIndex) == 1) { // 返回1, 代表找到了路径
                return 1; // 找到了路径就一直把1返回到findSimplePath
            }
        }
    }

    return 0; // 没有找到没有访问过的邻接点, 返回0
}

void findSimplePath(Graph *g) {
    if (g == NULL) {
        printf("图未初始化");
    }

    char startChar; // 起点字符
    char endChar; // 终点字符
    printf("请输入路径的起始顶点: ");
    scanf(" %c", &startChar);
    printf("请输入路径的结束顶点: ");
    scanf(" %c", &endChar);

    int startIndex = -1; // 找两个字符在数组中的位置
    int endIndex = -1;
    for (int i = 0; i < g->verNum; i++) {
        if (g->vertices[i] == startChar) {
            startIndex = i;
        }
        if (g->vertices[i] == endChar) {
            endIndex = i;
        }
    }
    if (startIndex == -1 || endIndex == -1) {
        printf("输入的顶点至少有一个不存在于图中\n");
        return;
    }

    int *visited = malloc(sizeof(int) * g->verNum); // 保存访问过的下标
    for (int i = 0; i < g->verNum; i++) {
        visited[i] = 0;
    }

    char *path = malloc(sizeof(char) * g->verNum); // 保存走过的路径

    if (DFS(g, startIndex, endIndex, visited, path, 0) == 0) {
        printf("未找到路径");
    }

    free(visited);
    free(path);
}

int main() {
    Graph *g = initGraph();
    createGraph(g);
    findSimplePath(g);
}