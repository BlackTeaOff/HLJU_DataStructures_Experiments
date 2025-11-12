#define MAXSIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} Queue;

Queue* initQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->front = 0;
    q->rear = 0;
    return q;
}

void enqueue(Queue *q, int e) {
    if ((q->rear + 1) % MAXSIZE == q->front) {
        printf("队列已满\n");
        return;
    }
    q->data[q->rear] = e;
    q->rear = (q->rear + 1) % MAXSIZE; // 防止数组越界, 例如当下标等于MAXSIZE-1的时候, 其值为0
}

int dequeue(Queue* q) {
    if (q->front == q->rear) {
        printf("队列为空\n");
        return -1;
    }
    int e = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return e;
}

int isQueueEmpty(Queue *q) {
    return q->front == q->rear; // 1为空
}

typedef struct node {
    int adjvex; // 所连接的点的下标
    struct node *next;
} edgeNode; // 边表结点, 对应着一条边, 连接在顶点表结点后, 存储该顶点连接的顶点的下标

typedef struct {
    char data;
    edgeNode *firstedge;
} vertexNode; // 顶点表结点, 存储了每个结点的值以及其连接的第一个边表结点

typedef struct {
    vertexNode *vertices; // 顶点表(数组)
    int verNum; // 点的数量
    int edgeNum; // 边的数量
} Graph;

Graph* initGraph() {
    Graph *g = malloc(sizeof(Graph));
    g->vertices = NULL;
    g->verNum = 0;
    g->edgeNum = 0;
    return g;
}

void createGraph(Graph *g) {
    if (g == NULL) {
        printf("图还未初始化\n");
        return;
    }

    printf("请输入顶点数: ");
    scanf(" %d", &g->verNum);
    printf("请输入边数: ");
    scanf(" %d", &g->edgeNum);
    g->vertices = malloc(sizeof(vertexNode) * g->verNum); // 顶点表数组

    printf("请输入各点的数据: ");
    for (int i = 0; i < g->verNum; i++) {
        scanf(" %c", &g->vertices[i].data);
        g->vertices[i].firstedge = NULL; // 初始化其连接的第一个边表结点为空
    }

    char a;
    char b;
    int index_a;
    int index_b;
    for (int i = 0; i < g->edgeNum; i++) { // 输入每一条边的端点
        index_a = -1;
        index_b = -1;
        printf("请输入与第%d条边连接的两个顶点: ", i + 1);
        scanf(" %c", &a);
        scanf(" %c", &b);
        for (int j = 0; j < g->verNum; j++) { // 寻找两个顶点的下标, 该值需存到边表结点中
            if (a == g->vertices[j].data) {
                index_a = j;
            }
            if (b == g->vertices[j].data) {
                index_b = j;
            }
        }
        if (index_a == -1 || index_b == -1) {
            printf("至少有一个点不在顶点表中\n");
            return;
        }

        edgeNode *e = malloc(sizeof(edgeNode)); // 创建一个边表结点
        e->adjvex = index_b; // 该边表结点存储与a相连结点下标
        e->next = g->vertices[index_a].firstedge; // 头插法
        g->vertices[index_a].firstedge = e;

        edgeNode *e1 = malloc(sizeof(edgeNode));
        e1->adjvex = index_a;
        e1->next = g->vertices[index_b].firstedge;
        g->vertices[index_b].firstedge = e1;
    }
    printf("图创建完成(邻接表)\n");
}

void findshortestPath(Graph *g) {
    if (g == NULL) {
        printf("图未初始化\n");
        return;
    }

    char startChar;
    char endChar;
    printf("请输入路径的起始顶点: ");
    scanf(" %c", &startChar);
    printf("请输入路径的结束顶点: ");
    scanf(" %c", &endChar);

    int startIndex = -1;
    int endIndex = -1;
    for (int i = 0; i < g->verNum; i++) {
        if (g->vertices[i].data == startChar) {
            startIndex = i;
        }
        if (g->vertices[i].data == endChar) {
            endIndex = i;
        }
    }
    if (startIndex == -1 || endIndex == -1) {
        printf("至少有一个顶点不在图中\n");
        return;
    }

    int visited[g->verNum];
    for (int i = 0; i < g->verNum; i++) {
        visited[i] = 0;
    }
    int parent[g->verNum]; // 用来存储各个点的上一个结点(用来找路径)
    for (int i = 0; i < g->verNum; i++) {
        parent[i] = -1;
    }

    Queue *q = initQueue();

    enqueue(q, startIndex); // 把开始结点入队
    visited[startIndex] = 1;

    int found = 0;
    while(!isQueueEmpty(q)) {
        int u = dequeue(q); // 出队

        if (u == endIndex) { // 找到了目标结点
            found = 1;
            break;
        }

        edgeNode *p = g->vertices[u].firstedge; // 不是的话就把它邻接的结点入队
        while (p != NULL) {
            if (!visited[p->adjvex]) {
                visited[p->adjvex] = 1;
                parent[p->adjvex] = u; // 把这个结点的上一个结点存起来, 用来存路径
                enqueue(q, p->adjvex);
            }
            p = p->next;
        }
    }

    if (found) {
            int path[g->verNum];
            int path_len = 0;
            int curr = endIndex;
            while (curr != -1) {
                path[path_len] = curr;
                curr = parent[curr];
                path_len++;
            }

            for (int i = path_len - 1; i >=0; i--) {
                printf("%c ", g->vertices[path[i]].data);
            }
            printf("\n");
        } else {
            printf("不存在路径\n");
        }

        free(q);
}

void printGraph(Graph *g) {
    edgeNode *p;
    for (int i = 0; i < g->verNum; i++) {
        p = g->vertices[i].firstedge;
        printf("%c所连接的点: ", g->vertices[i].data);
        while (p != NULL) {
            printf("%c ", g->vertices[p->adjvex].data);
            p = p->next;
        }
        printf("\n");
    }
}

int main() {
    Graph *g = initGraph();
    createGraph(g);
    // printGraph(g);
    findshortestPath(g);
}