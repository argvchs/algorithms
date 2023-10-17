#include <iostream>
using namespace std;
constexpr int N = 3005;
int n, m, q, bit[N][N];
void update(int x, int y, int k) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= m; j += j & -j) bit[i][j] += k;
}
int query(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i)
        for (int j = y; j >= 1; j -= j & -j) ret += bit[i][j];
    return ret;
}
int query(int x, int y, int z, int t) {
    return query(z, t) - query(x - 1, t) - query(z, y - 1) + query(x - 1, y - 1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1, op, x, y, z, t; i <= q; i++) {
        cin >> op >> x >> y >> z;
        if (op == 1) update(x, y, z);
        else cin >> t, cout << query(x, y, z, t) << '\n';
    }
    return 0;
}