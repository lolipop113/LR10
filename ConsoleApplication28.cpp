#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>

    using namespace std;

vector<vector<int>> generateRandomGraph(int n) {
    vector<vector<int>> graph(n, vector<int>(n, 0));
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (i != j) {
                int weight = rand() % 10 + 1;
                graph[i][j] = weight;
                graph[j][i] = weight;
            }
        }
    }
    return graph;
}



//убрать обратный ход в ориентир. матр.
vector<int> bfs(vector<vector<int>>& graph, int start) {
    vector<int> distances(graph.size(), INT_MAX);
    queue<int> q;
    q.push(start);
    distances[start] = 0;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int i = 0; i < graph.size(); i++) {
            if (graph[current][i] > 0 && distances[i] > distances[current] + graph[current][i]) {
                distances[i] = distances[current] + graph[current][i];
                q.push(i);
            }
        }
    }
    return distances;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите количество вершин в графе: ";
    cin >> n;
    vector<vector<int>> graph = generateRandomGraph(n);
    cout << "Матрица смежности для неориентированного графа:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    vector<vector<int>> allDistances;
    for (int i = 0; i < n; i++) {
        allDistances.push_back(bfs(graph, i));
    }
    // Определение радиуса и диаметра
    int radius = INT_MAX;
    int diameter = 0;
    for (const auto& distances : allDistances) {
        int maxDist = *max_element(distances.begin(), distances.end());
        if (maxDist < INT_MAX) {
            radius = min(radius, maxDist);
            diameter = max(diameter, maxDist);
        }
    }
    cout << "Радиус графа: " << radius << endl;
    cout << "Диаметр графа: " << diameter << endl;

    // Определение центральных и периферийных вершин
    vector<int> centralVertices;
    vector<int> peripheralVertices;
    for (int i = 0; i < n; i++) {
        int maxDist = *max_element(allDistances[i].begin(), allDistances[i].end());
        if (maxDist == diameter) {
            peripheralVertices.push_back(i);
        }
        if (maxDist == radius) {
            centralVertices.push_back(i);
        }
    }
    cout << "Центральные вершины: ";
    for (int v : centralVertices) {
        cout << v << " ";
    }
    cout << endl;
    cout << "Периферийные вершины: ";
    for (int v : peripheralVertices) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
