#include <bits/stdc++.h>
using namespace std;

const int LOG = 20; // log2(N) where N <= 1e5

int main() {
    int n;
    cin >> n;

    // Node values (1-indexed)
    vector<int> nodeValue(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> nodeValue[i];
    }

    // Adjacency list of the tree
    vector<vector<int>> tree(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Binary lifting tables
    vector<vector<int>> parent(n + 1, vector<int>(LOG)); // parent[node][j] = 2^j-th ancestor
    vector<vector<int>> maxOnPath(n + 1, vector<int>(LOG)); // max value from node to its 2^j-th ancestor
    vector<int> level(n + 1); // depth level of each node

    // DFS to fill parent[node][0] and maxOnPath[node][0]
    function<void(int, int)> dfs = [&](int current, int par) {
        level[current] = level[par] + 1;
        parent[current][0] = par;
        maxOnPath[current][0] = nodeValue[current];

        for (int neighbor : tree[current]) {
            if (neighbor != par) {
                dfs(neighbor, current);
            }
        }
    };

    dfs(1, 0); // Assuming node 1 is the root

    // Precompute binary lifting tables
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            int midAncestor = parent[i][j - 1];
            parent[i][j] = parent[midAncestor][j - 1];
            maxOnPath[i][j] = max(maxOnPath[i][j - 1], maxOnPath[midAncestor][j - 1]);
        }
    }

    // Lifts node u up by k levels
    auto liftNode = [&](int u, int k) {
        for (int j = 0; j < LOG; j++) {
            if ((k >> j) & 1) {
                u = parent[u][j];
            }
        }
        return u;
    };

    // Gets the maximum value on the path from node u up by k levels
    auto getMaxAlongPath = [&](int u, int k) {
        int maxVal = 0;
        for (int j = 0; j < LOG; j++) {
            if ((k >> j) & 1) {
                maxVal = max(maxVal, maxOnPath[u][j]);
                u = parent[u][j];
            }
        }
        return maxVal;
    };

    // Computes the Lowest Common Ancestor (LCA) of u and v
    auto getLCA = [&](int u, int v) {
        if (level[u] < level[v]) swap(u, v);
        u = liftNode(u, level[u] - level[v]);

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (parent[u][j] != parent[v][j]) {
                u = parent[u][j];
                v = parent[v][j];
            }
        }
        return parent[u][0];
    };

    // Distance between two nodes u and v
    auto getDistance = [&](int u, int v) {
        int lca = getLCA(u, v);
        return level[u] + level[v] - 2 * level[lca];
    };

    // Maximum value on the path from u to v
    auto getMaxBetweenNodes = [&](int u, int v) {
        int lca = getLCA(u, v);
        int maxU = getMaxAlongPath(u, level[u] - level[lca]);
        int maxV = getMaxAlongPath(v, level[v] - level[lca]);
        return max({maxU, maxV, nodeValue[lca]});
    };

    // Process queries
    int q;
    cin >> q;

    while (q--) {
        int u, v;
        cin >> u >> v;

        // Example usage:
        // cout << "Distance: " << getDistance(u, v) << '\n';
        // cout << "Max value on path: " << getMaxBetweenNodes(u, v) << '\n';
    }

    return 0;
}
