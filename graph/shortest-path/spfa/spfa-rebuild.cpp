#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
const int N = 1e5 + 5, M = 5e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, dis[N], head[N], cnt, tot;
bool vis[N];
struct edge {
    int to, nex, w;
} e[M << 1];
vector<int> S;
bool cmp(int u, int v) { return dis[u] > dis[v]; }
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
void spfa() {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = true, S.push_back(s);
    while (!S.empty()) {
        if (++tot > 1e4) sort(S.begin(), S.end(), cmp), tot = 0;
        int u = S.back();
        vis[u] = false, S.pop_back();
        for (int i = head[u]; i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) vis[v] = true, S.push_back(v);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
    }
    spfa();
    for (int i = 1; i <= n; i++)
        if (dis[i] == INF) cout << numeric_limits<int>::max() << ' ';
        else cout << dis[i] << ' ';
    return 0;
}