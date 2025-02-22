#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
const int N = 5e3 + 5, M = 5e4 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, h[N], dis[N], cur[N], head[N], cnt = 1, flow, cost;
bool vis[N];
struct edge {
    int to, nxt, w, c;
} e[M << 1];
queue<int> Q;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> PQ;
void add(int u, int v, int w, int c) { e[++cnt] = {v, head[u], w, c}, head[u] = cnt; }
void addflow(int u, int v, int w, int c) { add(u, v, w, c), add(v, u, 0, -c); }
void spfa() {
    memset(h, 0x3f, sizeof(h));
    h[s] = 0, vis[s] = true, Q.push(s);
    while (Q.size()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w, c = e[i].c;
            if (h[v] > h[u] + c && w) {
                h[v] = h[u] + c;
                if (!vis[v]) vis[v] = true, Q.push(v);
            }
        }
    }
}
bool dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    PQ.emplace(dis[s] = 0, s);
    while (PQ.size()) {
        int u = PQ.top().second;
        PQ.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w, c = e[i].c;
            if (dis[v] > dis[u] + c + h[u] - h[v] && w)
                PQ.emplace(dis[v] = dis[u] + c + h[u] - h[v], v);
        }
    }
    return dis[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    vis[u] = true;
    for (int &i = cur[u]; i; i = e[i].nxt) {
        int v = e[i].to, w = e[i].w, c = e[i].c;
        if (!vis[v] && h[v] == h[u] + c && w) {
            int ret = dfs(v, min(flow - used, w));
            used += ret, e[i].w -= ret, e[i ^ 1].w += ret;
            if (used == flow) break;
        }
    }
    vis[u] = false;
    return used;
}
void dinic() {
    spfa();
    while (dijkstra()) {
        memcpy(cur, head, sizeof(cur));
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= n; i++) h[i] += dis[i];
        while (int ret = dfs(s, INF)) flow += ret, cost += ret * h[t];
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t;
    for (int i = 1, u, v, w, c; i <= m; i++) cin >> u >> v >> w >> c, addflow(u, v, w, c);
    dinic();
    cout << flow << ' ' << cost;
}