#include <bit>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
using u32 = unsigned;
using p32 = pair<int, int>;
const int N = 5e3 + 5, M = 5e4 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, h[N], dis[N], pos[N], siz[35], cur[N], head[N],
    cnt = 1, beg, top, ansflow, anscost;
bool vis[N];
struct edge {
    int to, nex, w, c;
} e[M << 1];
queue<int> Q;
vector<int> buc[35], tmp;
void add(int u, int v, int w, int c) { e[++cnt] = {v, head[u], w, c}, head[u] = cnt; }
void addflow(int u, int v, int w, int c) { add(u, v, w, c), add(v, u, 0, -c); }
void spfa() {
    memset(h, 0x3f, sizeof(h));
    h[s] = 0, vis[s] = true, Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (int i = head[u]; i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w, c = e[i].c;
            if (h[v] > h[u] + c && w) {
                h[v] = h[u] + c;
                if (!vis[v]) vis[v] = true, Q.push(v);
            }
        }
    }
}
void insert(int x) {
    int k = bit_width<u32>(dis[x] ^ dis[top]);
    ++siz[k], pos[x] = buc[k].size(), buc[k].push_back(x);
}
void update(int x, int y) {
    int k = bit_width<u32>(dis[x] ^ dis[top]);
    --siz[k], dis[x] = y, insert(x);
}
void removemin() {
    pos[top] = -1, --siz[0];
    if (siz[0]) {
        while (pos[top = buc[0][beg]] == -1) ++beg;
        return;
    }
    int now = 0, las = top;
    for (int i = 30; i >= 1; i--)
        if (siz[i]) now = i;
    siz[now] = beg = top = 0, tmp = move(buc[now]);
    for (int i = 0; i <= now; i++) buc[i].clear();
    for (int i = 0; i < (int)tmp.size(); i++) {
        int k = bit_width<u32>(dis[tmp[i]] ^ dis[las]);
        if (k == now && pos[tmp[i]] == i && dis[tmp[i]] <= dis[top]) top = tmp[i];
    }
    for (int i = 0; i < (int)tmp.size(); i++) {
        int k = bit_width<u32>(dis[tmp[i]] ^ dis[las]);
        if (k == now && pos[tmp[i]] == i) insert(tmp[i]);
    }
}
bool dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    dis[top = s] = beg = 0;
    for (int i = 0; i <= 30; i++) buc[i].clear();
    for (int i = 1; i <= n; i++) insert(i);
    for (int i = 1; i <= n; i++, removemin())
        for (int j = head[top]; j; j = e[j].nex) {
            int v = e[j].to, w = e[j].w, c = e[j].c;
            if (dis[v] > dis[top] + c + h[top] - h[v] && w)
                update(v, dis[top] + c + h[top] - h[v]);
        }
    return dis[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    vis[u] = true;
    for (int &i = cur[u]; i; i = e[i].nex) {
        int v = e[i].to, w = e[i].w, c = e[i].c;
        if (!vis[v] && dis[v] == dis[u] + c + h[u] - h[v] && w) {
            int ret = dfs(v, min(flow - used, w));
            used += ret, e[i].w -= ret, e[i ^ 1].w += ret;
            if (used == flow) break;
        }
    }
    vis[u] = false;
    return used;
}
void dinic() {
    int ret;
    spfa();
    while (dijkstra()) {
        memcpy(cur, head, sizeof(cur));
        memset(vis, 0, sizeof(vis));
        while ((ret = dfs(s, INF))) ansflow += ret, anscost += ret * (dis[t] + h[t]);
        for (int i = 1; i <= n; i++) h[i] += dis[i];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t;
    for (int i = 1, u, v, w, c; i <= m; i++) {
        cin >> u >> v >> w >> c;
        addflow(u, v, w, c);
    }
    dinic();
    cout << ansflow << ' ' << anscost;
    return 0;
}