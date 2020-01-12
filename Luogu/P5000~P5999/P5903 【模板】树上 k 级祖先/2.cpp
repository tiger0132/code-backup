#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long ll;
typedef unsigned u;
const int N = 1e6 + 61, L = 19;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

u s;
inline u get(u x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x;
}

int p[N], dep[N], ord[N], occ[N], ordc;
void dfs(int x, int d) {
	x[dep] = d;
	ord[ordc++] = x;
	for (int i = x[head], nx; i; i = e[i].next) {
		dfs(nx = e[i].to, d + 1);
		ord[ordc++] = x;
	}
	x[occ] = ordc - 1;
}
int lca(int x, int y) {
	if (std::min(x, y) <= 0) return 0;
	int l = 31 - __builtin_clz((x ^ y) | 1);
	return (x | (1 << l)) & ~((1 << l) - 1);
}

std::vector<int> B[N];
int a[N];
int qry(int i, int x) {
	if (x >= a[i]) return i;
	int d = a[i] - x;
	if (d <= 3 * (i & -i)) return B[i][d];
	int k = lca(i - d + 1, i);
	return B[k][a[k] - x];
}

int n, q, rt, x, k, la, last[N];
ll ans;
int main() {
	scanf("%d%d%u", &n, &q, &s);
	for (int i = 1; i <= n; i++) {
		scanf("%d", p + i);
		p[i] ? addedge(p[i], i), 0 : (rt = i);
	}
	dfs(rt, 1);
	for (int i = 0; i < ordc; i++) a[i] = ord[i][dep];
	for (int i = ordc - 1; i >= 0; i--) {
		int f = 3 * (i & -i);  // 事实上 f(0) 应该是 = n 的，但是因为 a[0]
							   // 是最小的，所以直接写 f(x) = 3lowbit(x) 也没问题
		a[i][last] = i;
		for (int j = 0; j <= f && j < a[i]; j++) B[i].push_back((a[i] - j)[last]);
		for (int j = B[i].size() - 2; j >= 0; j--) B[i] = std::min(B[i], B[i + 1]);
	}
	for (int i = 1; i <= q; i++) {
		x = (get(s) ^ la) % n + 1, k = (get(s) ^ la) % x[dep];
		la = ord[qry(x[occ], x[dep] - k)];
		ans ^= 1ll * i * la;
	}
	printf("%lld", ans);
}