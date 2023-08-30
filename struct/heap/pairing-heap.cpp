#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], rt[N], fa[N], siz[N], cnt;
bool vis[N];
struct node {
    int l, r;
    pair<int, int> val;
} tree[N];
int merge(int lt, int rt) {
    if (!lt || !rt) return lt ^ rt;
    if (tree[lt].val > tree[rt].val) swap(lt, rt);
    tree[rt].r = tree[lt].l, tree[lt].l = rt;
    return lt;
}
int pairing(int rt) {
    if (!rt || !tree[rt].r) return rt;
    int r1 = tree[rt].r, r2 = tree[r1].r;
    tree[rt].r = tree[r1].r = 0;
    return merge(merge(rt, r1), pairing(r2));
}
void insert(int &rt, pair<int, int> a) {
    tree[++cnt] = {0, 0, a};
    rt = merge(rt, cnt);
}
void remove(int &rt) { rt = pairing(tree[rt].l); }
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        fa[i] = i, siz[i] = 1;
        insert(rt[i], {a[i], i});
    }
    for (int i = 1, op, u, v; i <= m; i++) {
        cin >> op >> u;
        if (op == 1) {
            cin >> v;
            if (vis[u] || vis[v]) continue;
            u = find(u), v = find(v);
            if (u == v) continue;
            if (siz[u] < siz[v]) swap(u, v);
            fa[v] = u, siz[u] += siz[v];
            rt[u] = merge(rt[u], rt[v]);
        } else {
            if (vis[u]) {
                cout << "-1\n";
                continue;
            }
            auto [val, id] = tree[rt[u = find(u)]].val;
            remove(rt[u]);
            vis[id] = true;
            cout << val << '\n';
        }
    }
    return 0;
}