//No. of good path(hard).
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); 
        }
        return parent[x];
    }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};
int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
    int n = vals.size();
    unordered_map<int, vector<int>> valueToNodes;
    for (int i = 0; i < n; ++i) {
        valueToNodes[vals[i]].push_back(i);
    }
    vector<vector<int>> graph(n);
    for (auto& edge : edges) {
        int a = edge[0], b = edge[1];
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    UnionFind uf(n);
    vector<bool> visited(n, false);
    int goodPaths = 0;
    for (auto& [value, nodes] : valueToNodes) {
        for (int node : nodes) {
            visited[node] = true;
            for (int neighbor : graph[node]) {
                if (visited[neighbor] && vals[neighbor] <= value) {
                    uf.unite(node, neighbor);
                }
            }
        }
        unordered_map<int, int> componentCount;
        for (int node : nodes) {
            int root = uf.find(node);
            componentCount[root]++;
        }
        for (auto& [root, count] : componentCount) {
            goodPaths += (count * (count + 1)) / 2;
        }
    }

    return goodPaths;
}
int main() {
    vector<int> vals1 = {1, 3, 2, 1, 3};
    vector<vector<int>> edges1 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    cout << "Example 1 Output: " << numberOfGoodPaths(vals1, edges1) << endl;
    vector<int> vals2 = {1, 1, 2, 2, 3};
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {2, 3}, {2, 4}};
    cout << "Example 2 Output: " << numberOfGoodPaths(vals2, edges2) << endl;
    vector<int> vals3 = {1};
    vector<vector<int>> edges3 = {};
    cout << "Example 3 Output: " << numberOfGoodPaths(vals3, edges3) << endl;

    return 0;
}
