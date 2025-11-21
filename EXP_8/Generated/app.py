from flask import Flask, jsonify
import heapq

app = Flask(__name__)

# C代码中的地点数据
places = [
    {"name": "主门", "intro": "0"},
    {"name": "主楼", "intro": "1"},
    {"name": "体育场", "intro": "2"},
    {"name": "联通广场", "intro": "3"},
    {"name": "汇文楼", "intro": "4"},
    {"name": "新图书馆", "intro": "5"},
    {"name": "A区食堂", "intro": "6"},
    {"name": "B区食堂", "intro": "7"},
    {"name": "C区食堂", "intro": "8"},
    {"name": "艺术楼", "intro": "9"},
]

# 使用一个很大的数表示无穷大
INF = float('inf')

# 初始化邻接矩阵
matrix = [[INF] * 10 for _ in range(10)]

def set_matrix():
    """设置邻接矩阵的权值"""
    for i in range(10):
        matrix[i][i] = 0

    # C代码中的路径数据
    edges = [
        (0, 1, 70), (0, 2, 170),
        (1, 2, 114), (1, 5, 404), (1, 3, 200),
        (3, 4, 450),
        (4, 7, 260), (4, 9, 650),
        (5, 6, 130),
        (6, 7, 190),
        (7, 9, 550),
        (8, 9, 200),
    ]
    for u, v, weight in edges:
        matrix[u][v] = weight
        matrix[v][u] = weight

# --- 算法实现 ---
dist_floyd = []
path_floyd = []

def floyd_warshall():
    """Floyd-Warshall 算法，计算所有节点对的最短路径"""
    global dist_floyd, path_floyd
    dist_floyd = [row[:] for row in matrix]
    path_floyd = [[-1] * 10 for _ in range(10)]

    for i in range(10):
        for j in range(10):
            if i != j and matrix[i][j] != INF:
                path_floyd[i][j] = i

    for k in range(10):
        for i in range(10):
            for j in range(10):
                if dist_floyd[i][k] + dist_floyd[k][j] < dist_floyd[i][j]:
                    dist_floyd[i][j] = dist_floyd[i][k] + dist_floyd[k][j]
                    path_floyd[i][j] = path_floyd[k][j]

def get_floyd_path(start, end):
    """从Floyd算法的结果中回溯路径"""
    if path_floyd[start][end] == -1:
        return []
    path = [places[end]['name']]
    curr = end
    while curr != start:
        prev = path_floyd[start][curr]
        if prev == -1: return [] # 路径中断
        path.insert(0, places[prev]['name'])
        if prev == curr: break # 防止死循环
        curr = prev
    return path


# 在应用启动时，预先计算好所有数据
set_matrix()
floyd_warshall()


# --- API 路由 ---

@app.route('/')
def index():
    return "欢迎使用校园导览API！"

@app.route('/places')
def get_places():
    """获取所有地点列表"""
    return jsonify(places)

@app.route('/path/from_gate/to/<int:dest_id>')
def get_path_from_gate(dest_id):
    """
    Dijkstra算法：计算从主门(0)到指定地点的最短路径
    """
    if not (0 <= dest_id < 10):
        return jsonify({"error": "无效的目标地点ID"}), 400

    # Dijkstra 算法实现
    dist = [INF] * 10
    prev = [-1] * 10
    dist[0] = 0
    pq = [(0, 0)]  # (距离, 节点ID)

    while pq:
        d, u = heapq.heappop(pq)

        if d > dist[u]:
            continue

        for v in range(10):
            if dist[u] + matrix[u][v] < dist[v]:
                dist[v] = dist[u] + matrix[u][v]
                prev[v] = u
                heapq.heappush(pq, (dist[v], v))
    
    # 回溯路径
    path = []
    curr = dest_id
    while curr != -1:
        path.insert(0, places[curr]['name'])
        curr = prev[curr]

    if dist[dest_id] == INF:
        return jsonify({
            "start": places[0]['name'],
            "end": places[dest_id]['name'],
            "error": "没有可达路径"
        })
    else:
        return jsonify({
            "start": places[0]['name'],
            "end": places[dest_id]['name'],
            "distance": dist[dest_id],
            "path": path
        })


@app.route('/path/from/<int:start_id>/to/<int:end_id>')
def get_path_between_places(start_id, end_id):
    """
    Floyd-Warshall算法：计算任意两个地点间的最短路径
    """
    if not (0 <= start_id < 10 and 0 <= end_id < 10):
        return jsonify({"error": "无效的地点ID"}), 400

    distance = dist_floyd[start_id][end_id]

    if distance == INF:
        return jsonify({
            "start": places[start_id]['name'],
            "end": places[end_id]['name'],
            "error": "没有可达路径"
        })
    else:
        path = get_floyd_path(start_id, end_id)
        return jsonify({
            "start": places[start_id]['name'],
            "end": places[end_id]['name'],
            "distance": distance,
            "path": path
        })

if __name__ == '__main__':
    app.run(debug=True, port=5000)
