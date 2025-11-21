#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset

#define DLLEXPORT __declspec(dllexport) // __declspec(dllexport)声明该函数可以通过编译为dll为外部调用

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

char result_json[2048]; // 用来存储结果/路径的json格式, 传入python, 渲染到网页
/*
Martix = {
          0   1   2    3    4    5    6    7     8      9
       0  0, 70, 170, 260, 720, 500, 600, 825, 1500, 1300
*/


void setMartix() {
    memset(Matrix, 0x3f, sizeof(Matrix)); // 都设为无穷大(每个字节被设置为0x3f, 一个int4字节, 4个3f)

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

void buildGatePathString(int path[], int j, char* path_str, char* path_id, int id_index) { // 传入path, 从哪开始, 还有需要传出的路径字符串
    if (path[j] == -1) { // 到大门的情况(大门path为-1)
        sprintf(path_str + strlen(path_str), "\"%s\"", places[j].name); // 写入名字, +strlen是为了移动指针, 移动到字符串末尾继续添加
        path_id[id_index] = j + '0';
        id_index++;
        path_id = '\0';
        return;
    }
    path_id[id_index] = j + '0';
    id_index++;
    path_id[id_index] = ',';
    id_index++;
    buildGatePathString(path, path[j], path_str, path_id, id_index); // 递归向前回溯, 传入该结点的前一个结点
    sprintf(path_str + strlen(path_str), ", \"%s\"", places[j].name);
}

DLLEXPORT char* fromGatePath(int dest) { // 从大门到dest最短路径(Dijkstra), 给python返回json字符串
    int src = 0; // 从大门开始

    int dist[10];    // 记录某点到src最短长度
    int visited[10]; // 记录某点是否已找到最短路径
    int path[10];    // 记录某点的前驱(每次遍历会以别的点为中间点, 看看从src(大门)通过中间点到达该点会不会比直接从src)
    // (到达该点更近, 如果更近则更新该点的前驱为中间点)

    for (int i = 0; i < 10; i++) {
        dist[i] = 0x3f3f3f3f; // 所有最短长度为无穷大
        visited[i] = 0;       // 所有都还没找到最短路径
        path[i] = -1;         // 所有都还没有前驱
    }

    dist[src] = 0; // 设置src(大门), 到达src的最短长度为0

    for (int i = 0; i < 9; i++) { // 到最后一个点之前就处理完了, 因为到最后一个点的时候, 其他的visited都为1了, 都为最短路径
        int u = -1; // 用来存储所有点中, 离src最近的点的下标(最近的情况就是找到src到该点的最短路径了), -1代表没有
        for (int j = 0; j < 10; j++) { // 遍历所有点(0-9)
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) { // 找没有找到最短路径的, 并且该点的路径最短(如果u大则更新为j)
                u = j; // u == -1确保循环开始时, 第一个结点能被设置(因为第一次的时候u=-1, dist[u]不存在)
            }
        }

        if (u == -1) { // u = -1代表所有点都找到了最短路径
            break;
        }

        visited[u] = 1; // 设置该点为已有最短路径

        for (int v = 0; v < 10; v++) { // 遍历其他点, 看看通过u点到达该点会不会比从src到该点更近    ↓(而且从src通过u到v, 比直接从src到v更近)
            if (!visited[v] && Matrix[u][v] != 0x3f3f3f3f && dist[u] + Matrix[u][v] < dist[v]) { // 该点需要没访问过, 而且和u点有连接
                dist[v] = dist[u] + Matrix[u][v]; // 更新v的最短路径为经过u点到达v点
                path[v] = u; // 设置该点的前驱为u
            }
        }
    }

    memset(result_json, 0, sizeof(result_json)); // 设置返回json字符串都为0
    if (dist[dest] == 0x3f3f3f3f) { // 如果dest到src(0-原点)无可达路径, 无穷大                                "\"为转义字符"
        sprintf(result_json, "{\"error\": \"从%s到%s没有最短路径\"}", places[0].name, places[dest].name); // 将字符串格式化存到字符数组
    } else {
        char path_str[1024] = "";
        char path_id[1024] = "";

        buildGatePathString(path, dest, path_str, path_id, 0);
        //sprintf(result_json, "{\"distance\": %d, \"path_ids\": [1, 0]}", dist[dest]);

        sprintf(result_json, "{\"start\": \"%s\", \"destination\": \"%s\", \"distance\": %d, \"path_ids\": [%s],\"path\": [%s]}", places[0].name, places[dest].name, dist[dest], path_id, path_str);
        return result_json;
    }

    /*
    if (dist[dest] == 0x3f3f3f3f) {
        printf("从 %s 到 %s 没有可达路径。\n", places[src].name, places[dest].name);
    } else {
        printf("从 %s 到 %s 的最短路径是: \n", places[src].name, places[dest].name);
        printPath(path, dest);
        printf("\n总路程: %d 米\n", dist[dest]);
    }
    */
}

int d[10][10]; // d数组, 记录点到点的最短距离
int p[10][10]; // p数组, 记录某点到某点最短路径的前驱

void flyod() { // 设置dp数组
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            d[i][j] = Matrix[i][j]; // 初始化d数组, 第一次就是邻接矩阵里面的权值
            if (Matrix[i][j] > 0 && Matrix[i][j] != 0x3f3f3f3f) { // i到j有边而且不为无穷大
                p[i][j] = i; // 初始化p数组, i到j的前驱为i
            } else {
                p[i][j] = -1; // 没边(对角线为0)或者无穷大, 前驱设为-1代表没有路径
            }
        }
    }

    for (int i = 0; i < 10; i++) { // 选第i的点作为中间点, 看j通过i到k比j直接到k是不是更近, 更近则更新
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                if (d[j][i] + d[i][k] < d[j][k]) {
                    d[j][k] = d[j][i] + d[i][k]; // 更新j到k的距离为j-i-k的距离(因为更短)
                    p[j][k] = p[i][k]; // j到k的前驱设为i到k的前驱
                }
            }
        }
    }
}

void buildPlacePathString(int i, int j, char* path_str, char* path_id, int id_index) { // 递归构造floyd路径字符串和path_ids
    if (p[i][j] == -1) {
        sprintf(path_str + strlen(path_str), "\"%s\"", places[i].name); // 向path数组最后写入, 写入的值为"name"
        path_id[id_index] = i + '0'; // 把起点i加入路径id数组(存的是ASCII所以加上0的ASCII值)
        id_index++;
        path_id[id_index] = '\0';
        return;
    }

    path_id[id_index] = j + '0';
    id_index++;
    path_id[id_index] = ','; // 每个值用逗号分隔
    id_index++;
    buildPlacePathString(i, p[i][j], path_str, path_id, id_index); // 把i到j的前驱作为下一个终点, 继续往前找
    sprintf(path_str + strlen(path_str), ", \"%s\"", places[j].name);
}

DLLEXPORT char* fromPlacePath(int src, int dest) {
    memset(result_json, 0, sizeof(result_json)); // result字符串清空
    if (d[src][dest] == 0x3f3f3f3f) { // src到dest路径为无穷大, 则没有最短路径
        sprintf(result_json, "{\"error\": \"从%d到%d没有最短路径\"}");
    } else {
        char path_str[1024] = "";
        char path_id[1024] = "";

        buildPlacePathString(src, dest, path_str, path_id, 0);

        sprintf(result_json,
                "{\"start\": \"%s\", \"dest\": \"%s\", \"distance\": %d, \"path_ids\": [%s], \"path\": [%s]}",
                places[src].name, places[dest].name, d[src][dest], path_id, path_str);

        return result_json;
    }
}

DLLEXPORT Places* getPlaces() {
    return places;
}

DLLEXPORT void init() {
    setMartix(); //  外部使用先初始化
    flyod(); // dp数组设置
}


// void main() {
//     setMartix();
//     printf("%s", fromGatePath(4));
// }
