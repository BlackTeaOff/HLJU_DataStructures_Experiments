#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the export macro for Windows DLLs
#define DLLEXPORT __declspec(dllexport)

typedef struct {
    char name[100];
    char intro[100];
} Places;

Places places[10] = {
    {"主门", "0"}, {"主楼", "1"}, {"体育场", "2"}, {"联通广场", "3"}, {"汇文楼", "4"},
    {"新图书馆", "5"}, {"A区食堂", "6"}, {"B区食堂", "7"}, {"C区食堂", "8"}, {"艺术楼", "9"},
};

int Matrix[10][10];
int dist_floyd[10][10];
int path_floyd[10][10];

// A static buffer to hold the JSON string result.
// This is simple but not thread-safe. For this project, it's sufficient.
static char result_buffer[2048];

void setMartix() {
    memset(Matrix, 0x3f, sizeof(Matrix));
    for (int i = 0; i < 10; i++) {
        Matrix[i][i] = 0;
    }
    Matrix[0][1] = 70; Matrix[1][0] = 70;
    Matrix[0][2] = 170; Matrix[2][0] = 170;
    Matrix[1][2] = 114; Matrix[2][1] = 114;
    Matrix[1][5] = 404; Matrix[5][1] = 404;
    Matrix[1][3] = 200; Matrix[3][1] = 200;
    Matrix[3][4] = 450; Matrix[4][3] = 450;
    Matrix[4][7] = 260; Matrix[7][4] = 260;
    Matrix[4][9] = 650; Matrix[9][4] = 650;
    Matrix[5][6] = 130; Matrix[6][5] = 130;
    Matrix[6][7] = 190; Matrix[7][6] = 190;
    Matrix[7][9] = 550; Matrix[9][7] = 550;
    Matrix[8][9] = 200; Matrix[9][8] = 200;
}

void floydWarshall() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            dist_floyd[i][j] = Matrix[i][j];
            if (Matrix[i][j] != 0x3f3f3f3f && i != j) {
                path_floyd[i][j] = i;
            } else {
                path_floyd[i][j] = -1;
            }
        }
    }
    for (int k = 0; k < 10; k++) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (dist_floyd[i][k] != 0x3f3f3f3f && dist_floyd[k][j] != 0x3f3f3f3f &&
                    dist_floyd[i][k] + dist_floyd[k][j] < dist_floyd[i][j]) {
                    dist_floyd[i][j] = dist_floyd[i][k] + dist_floyd[k][j];
                    path_floyd[i][j] = path_floyd[k][j];
                }
            }
        }
    }
}

// This function must be called once after loading the DLL.
DLLEXPORT void initialize() {
    setMartix();
    floydWarshall();
}

// Helper to build a path string for Dijkstra
void build_dijkstra_path_string(int path[], int j, char* buffer) {
    if (path[j] == -1) {
        sprintf(buffer + strlen(buffer), "\"%s\"", places[j].name);
        return;
    }
    build_dijkstra_path_string(path, path[j], buffer);
    sprintf(buffer + strlen(buffer), ", \"%s\"", places[j].name);
}

DLLEXPORT const char* query_from_gate(int dest) {
    int dist[10];
    int visited[10];
    int path[10];

    for (int i = 0; i < 10; i++) {
        dist[i] = 0x3f3f3f3f;
        visited[i] = 0;
        path[i] = -1;
    }
    dist[0] = 0;

    for (int count = 0; count < 9; count++) {
        int u = -1;
        for (int i = 0; i < 10; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = 1;
        for (int v = 0; v < 10; v++) {
            if (!visited[v] && Matrix[u][v] != 0x3f3f3f3f && dist[u] + Matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + Matrix[u][v];
                path[v] = u;
            }
        }
    }

    memset(result_buffer, 0, sizeof(result_buffer));
    if (dist[dest] == 0x3f3f3f3f) {
        sprintf(result_buffer, "{\"error\": \"No path found from %s to %s\"}", places[0].name, places[dest].name);
    } else {
        char path_str[1024] = "";
        build_dijkstra_path_string(path, dest, path_str);
        sprintf(result_buffer, "{\"start\": \"%s\", \"end\": \"%s\", \"distance\": %d, \"path\": [%s]}",
                places[0].name, places[dest].name, dist[dest], path_str);
    }
    return result_buffer;
}

// Helper to build a path string for Floyd
void build_floyd_path_string(int i, int j, char* buffer) {
    if (path_floyd[i][j] == -1) return;
    if (path_floyd[i][j] == i) {
        sprintf(buffer + strlen(buffer), "\"%s\"", places[i].name);
        return;
    }
    build_floyd_path_string(i, path_floyd[i][j], buffer);
    sprintf(buffer + strlen(buffer), ", \"%s\"", places[path_floyd[i][j]].name);
}

DLLEXPORT const char* query_from_place(int start, int dest) {
    memset(result_buffer, 0, sizeof(result_buffer));
    if (dist_floyd[start][dest] == 0x3f3f3f3f) {
        sprintf(result_buffer, "{\"error\": \"No path found from %s to %s\"}", places[start].name, places[dest].name);
    } else {
        char path_str[1024] = "";
        build_floyd_path_string(start, dest, path_str);
        // Add the destination to the path string
        sprintf(path_str + strlen(path_str), ", \"%s\"", places[dest].name);
        sprintf(result_buffer, "{\"start\": \"%s\", \"end\": \"%s\", \"distance\": %d, \"path\": [%s]}",
                places[start].name, places[dest].name, dist_floyd[start][dest], path_str);
    }
    return result_buffer;
}
