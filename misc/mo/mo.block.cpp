#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int n, m, l = 1, r, a[N], b[N], belong[N], val[N], sum[N], siz, cnt;
struct node {
    int l, r, k, id, ans;
} q[N];
bool comp1(node a, node b) {
    if (belong[a.l] != belong[b.l]) return a.l < b.l;
    return a.r < b.r;
}
bool comp2(node a, node b) { return a.id < b.id; }
void build() {
    siz = sqrt(n);
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / siz + 1;
}
void insert(int x) { ++val[x], ++sum[belong[x]]; }
void remove(int x) { --val[x], --sum[belong[x]]; }
int query(int x) {
    int i = 1, j = 1, cur = 0;
    while (cur + sum[i] < x) cur += sum[i++], j += siz;
    while (cur + val[j] < x) cur += val[j++];
    return j;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i];
    for (int i = 1; i <= m; i++) cin >> q[i].l >> q[i].r >> q[i].k, q[i].id = i;
    sort(b + 1, b + n + 1);
    cnt = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
    build();
    sort(q + 1, q + m + 1, comp1);
    for (int i = 1; i <= m; i++) {
        while (l > q[i].l) insert(a[--l]);
        while (r < q[i].r) insert(a[++r]);
        while (l < q[i].l) remove(a[l++]);
        while (r > q[i].r) remove(a[r--]);
        q[i].ans = query(q[i].k);
    }
    sort(q + 1, q + m + 1, comp2);
    for (int i = 1; i <= m; i++) cout << b[q[i].ans] << '\n';
    return 0;
}