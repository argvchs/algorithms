#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
int n, m, p, rt, a[N], b1[N], b2[N], ifn[N], ofn[N], fa[N], ch[N], dep[N], siz[N], top[N],
    idx, cnt, head[N];
struct edge {
    int to, next;
} e[N << 1];
vector<pair<int, int>> tmp;
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void addedge(int u, int v) { add(u, v), add(v, u); }
void dfs1(int u, int fa) {
    ::fa[u] = fa, dep[u] = dep[fa] + 1, siz[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs1(v, u), siz[u] += siz[v];
        if (siz[v] > siz[ch[u]]) ch[u] = v;
    }
}
void dfs2(int u, int fa, int top) {
    ::top[u] = top, ifn[u] = ++idx;
    if (ch[u]) {
        dfs2(ch[u], u, top);
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to;
            if (v != fa && v != ch[u]) dfs2(v, u, v);
        }
    }
    ofn[u] = idx;
}
void solve(int u, int v) {
    tmp.clear();
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        tmp.emplace_back(top[u], u);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    tmp.emplace_back(v, u);
}
void update(int x, int k) {
    for (int i = x; i <= n; i += i & -i)
        b1[i] = (b1[i] + k) % p, b2[i] = (b2[i] + (i64)k * x) % p;
}
void update(int l, int r, int k) { update(l, k), update(r + 1, p - k % p); }
int query(int x) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i)
        ret = (ret + (i64)(x + 1) * b1[i] - b2[i] + p) % p;
    return ret;
}
int query(int l, int r) { return (query(r) - query(l - 1) + p) % p; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> rt >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addedge(u, v);
    }
    dfs1(rt, 0);
    dfs2(rt, 0, rt);
    for (int i = 1; i <= n; i++) update(ifn[i], ifn[i], a[i]);
    for (int i = 1, op, x, y, z; i <= m; i++) {
        cin >> op >> x;
        if (op == 1) {
            cin >> y >> z;
            solve(x, y);
            for (auto [u, v] : tmp) update(ifn[u], ifn[v], z);
        } else if (op == 2) {
            cin >> y;
            solve(x, y);
            int ans = 0;
            for (auto [u, v] : tmp) ans = (ans + query(ifn[u], ifn[v])) % p;
            cout << ans << '\n';
        } else if (op == 3) {
            cin >> y;
            update(ifn[x], ofn[x], y);
        } else cout << query(ifn[x], ofn[x]) << '\n';
    }
    return 0;
}