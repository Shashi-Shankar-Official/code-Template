#include <bits/stdc++.h>
using namespace std;

const int N= 2e5+1, M=20;

vector<int> adj[N];
int depth[N], parent[N][M];

void dfs(int curr, int par) {
    depth[curr] = depth[par] + 1;
    parent[curr][0] = par;
    for(int j=1;j<M;j++) {
        parent[curr][j] = parent[parent[curr][j-1]][j-1];
    }

    for(auto x:adj[curr]) {
        if(x != par) {
            dfs(x, curr);
        }
    }
}

int kthParent(int u, int k) {
    for(int i=M-1; i>=0; i--) {
        if((1 << i) & k) {
            u=parent[u][i];
        }
    }

    return u;
}



//LCA- Lowest common ancestor
int LCA(int u, int v) {
    if(u==v) return u;
    if(depth[u] < depth[v]) {
        swap(u,v);
    }
    int diff = depth[u] - depth[v];
    for(int j= M-1; j>=0; j--) {
        if((diff >> j) & 1) {
            u = parent[u][j];
        }
    }

    for(int j= M-1; j>=0; j--) {
        if(parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
        }
    }

    if(u == v) {
        return u;
    } else {
        return parent[u][0];
    }
}

int main() {
    int n,q;
    cin>>n>>q;

    for(int i=2;i<=n;i++) {
        int x;
        cin>>x;
        adj[x].push_back(i);
    }
    dfs(1,0);

    for(int i =0; i<q;i++) {
        int u,k;
        cin>>u>>k;
        int parent = kthParent(u,k);
        if(parent == 0) {
            cout<<"-1\n";
        } else {
            cout<<parent<<"\n";
        }
    }
    return 0;
}
