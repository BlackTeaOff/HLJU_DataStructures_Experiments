#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset

typedef struct {
    char name[100];
    char intro[100];
} Places;

//char places[10][10] = {"主门", "主楼", "体育场", "联通广场", "汇文楼", "新图书馆", "A区食堂", "B区食堂", "C区食堂", "艺术楼"};
Places places[10] = {
    {"主门", "0"},
    {"主楼", "1"},
    {"体育场", "2"},
    {"联通广场", "3"},
    {"汇文楼", "4"},
    {"新图书馆", "5"},
    {"A区食堂", "6"},
    {"B区食堂", "7"},
    {"C区食堂", "8"},
    {"艺术楼", "9"},
};

// 0-主门, 1-主楼, 2-体育场, 3-联通广场, 4-汇文楼, 5-新图书馆, 6-A区食堂, 7-B区食堂, 8-C区食堂, 9-艺术楼

int Matrix[10][10]; // 邻接矩阵

/*
Martix = {
          0   1   2    3    4    5    6    7     8      9
       0  0, 70, 170, 260, 720, 500, 600, 825, 1500, 1300
*/


void setMartix(int Matrix[10][10]) {
    for (int i = 0; i < 10; i++) {
        Matrix[i][i] = 0; // 初始化对角线为0(自身到自身)
    }
    // 只需要将图中连线的写入权值(路程), 没连线的还是无穷大(0x3f)
    Matrix[0][1] = 70; Matrix[1][0] = 70;    // 主门-主楼
    Matrix[0][2] = 170; Matrix[2][0] = 170;  // 主门-体育场
    // Matrix[0][3] = 260; Matrix[3][0] = 260;  // 主门-联通广场
    // Matrix[0][4] = 720; Matrix[4][0] = 720;  // 主门-汇文楼
    // Matrix[0][5] = 500; Matrix[5][0] = 500;  // 主门-新图书馆
    // Matrix[0][6] = 600; Matrix[6][0] = 600;  // 主门-A区食堂
    // Matrix[0][7] = 825; Matrix[7][0] = 825;  // 主门-B区食堂
    // Matrix[0][8] = 1500; Matrix[8][0] = 1500;// 主门-C区食堂
    // Matrix[0][9] = 1300; Matrix[9][0] = 1300;// 主门-艺术楼
    
    Matrix[1][2] = 114; Matrix[2][1] = 114;  // 主楼-体育场
    Matrix[1][5] = 404; Matrix[5][1] = 404;  // 主楼-新图书馆
    Matrix[1][3] = 200; Matrix[3][1] = 200;  // 主楼-联通广场

    Matrix[3][4] = 450; Matrix[4][3] = 450;  // 联通广场-汇文楼
    
    Matrix[4][7] = 260; Matrix[7][4] = 260;  // 汇文楼-B食堂
    Matrix[4][9] = 650; Matrix[9][4] = 650;  // 汇文楼-艺术楼


    Matrix[5][6] = 130; Matrix[6][5] = 130;  // 新图书馆-A食堂

    Matrix[6][7] = 190; Matrix[7][6] = 190;  // A食堂-B食堂

    Matrix[7][9] = 550; Matrix[9][7] = 550;  // B食堂-艺术楼

    Matrix[8][9] = 200; Matrix[9][8] = 200; // C食堂-艺术楼
}


void printPath(int path[], int j) {
    if (path[j] == -1) { // Base case: If j is the source
        printf("%s", places[j].name);
        return;
    }
    printPath(path, path[j]);
    printf(" -> %s", places[j].name);
}

// Dijkstra's algorithm implementation
void dijkstra(int graph[10][10], int src, int dest) {
    int dist[10];     // The output array. dist[i] will hold the shortest distance from src to i
    int visited[10];  // visited[i] will be true if vertex i is included in shortest path tree
    int path[10];     // To store the path

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < 10; i++) {
        dist[i] = 0x3f3f3f3f;
        visited[i] = 0;
        path[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < 10 - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = -1;
        for (int i = 0; i < 10; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        
        if (u == -1) break; // All remaining vertices are inaccessible

        // Mark the picked vertex as visited
        visited[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < 10; v++) {
            if (!visited[v] && graph[u][v] != 0x3f3f3f3f && dist[u] != 0x3f3f3f3f && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                path[v] = u;
            }
        }
    }

    // print the constructed distance array and path
    if (dist[dest] == 0x3f3f3f3f) {
        printf("从 %s 到 %s 没有可达路径。\n", places[src].name, places[dest].name);
    } else {
        printf("从 %s 到 %s 的最短路径是: \n", places[src].name, places[dest].name);
        printPath(path, dest);
        printf("\n总路程: %d 米\n", dist[dest]);
    }
}


void fromGatePath(int dest) { // 从大门到dest最短路径(Dijkstra)
    printf("--- 查询从主门到 %s 的最短路径 ---\n", places[dest].name);
    dijkstra(Matrix, 0, dest); // 主门的索引是 0
}

// --- Floyd-Warshall 算法实现 ---
int dist_floyd[10][10];
int path_floyd[10][10];

// 递归打印Floyd算法的路径
void printFloydPath(int i, int j) {
    if (path_floyd[i][j] == i) { // 如果i是j的前驱，说明是直达
        printf("%s", places[i].name);
        return;
    }
    if (path_floyd[i][j] == -1) { // 没有路径
        return;
    }
    printFloydPath(i, path_floyd[i][j]);
    printf(" -> %s", places[path_floyd[i][j]].name);
}


// Floyd-Warshall algorithm to find all-pairs shortest paths
void floydWarshall() {
    // Initialize dist and path matrices
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            dist_floyd[i][j] = Matrix[i][j];
            if (Matrix[i][j] != 0x3f3f3f3f && i != j) {
                path_floyd[i][j] = i; // The predecessor of j is i
            } else {
                path_floyd[i][j] = -1; // No path or self-loop
            }
        }
    }

    // Core of the Floyd-Warshall algorithm
    for (int k = 0; k < 10; k++) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (dist_floyd[i][k] != 0x3f3f3f3f && dist_floyd[k][j] != 0x3f3f3f3f &&
                    dist_floyd[i][k] + dist_floyd[k][j] < dist_floyd[i][j]) {
                    dist_floyd[i][j] = dist_floyd[i][k] + dist_floyd[k][j];
                    path_floyd[i][j] = path_floyd[k][j]; // Update predecessor
                }
            }
        }
    }
}


void fromPlacePath(int start, int dest) { // 从start到dest最短路径(Floyd)
    printf("\n--- 查询从 %s 到 %s 的最短路径 ---\n", places[start].name, places[dest].name);
    if (dist_floyd[start][dest] == 0x3f3f3f3f) {
        printf("从 %s 到 %s 没有可达路径。\n", places[start].name, places[dest].name);
    } else {
        printf("从 %s 到 %s 的最短路径是: \n", places[start].name, places[dest].name);
        printFloydPath(start, dest);
        printf(" -> %s", places[dest].name);
        printf("\n总路程: %d 米\n", dist_floyd[start][dest]);
    }
}

void printMatrix(int Matrix[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (Matrix[i][j] == 0x3f3f3f3f) { // 无穷大的情况
                printf("INF ");
            } else {
                printf("%3d ", Matrix[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    // for (int i = 0; i < 10; i++) {
    //     printf("%s %s\n", places[i].name, places[i].intro);
    // }
    memset(Matrix, 0x3f, sizeof(Matrix)); // 都设为无穷大(每个字节被设置为0x3f, 一个int4字节, 4个3f)
    setMartix(Matrix);
    
    // 首先运行Floyd-Warshall算法来计算所有点对的最短路径
    floydWarshall();

    // 示例1：查找从主门到联通广场(索引3)的最短路径
    fromGatePath(3); 

    // 示例2：查找从体育场(索引2)到C区食堂(索引8)的最短路径
    fromPlacePath(7, 1);
}