#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long ll;
typedef unsigned u;
const int N = 5e5 + 55, L = 19;
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

int p[N], dep[N], _dep[N], son[N], top[N], col[N];
void dfs1(int x, int d) {
	x[dep] = x[_dep] = d;
	for (int i = x[head], nx, mx = d; i; i = e[i].next) {
		dfs1(nx = e[i].to, d + 1), x[dep] = std::max(x[dep], nx[dep]);
		if (nx[dep] > mx) mx = nx[dep], x[son] = nx;
	}
}
void dfs2(int x, int t) {
	x[top] = t;
	if (!x[son]) return;
	dfs2(x[son], t);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[son]) dfs2(nx, nx);
}

int n, q, rt, x, k, la, fa[N][L], c;
std::vector<int> up[N], down[N];
ll ans;
int main() {
	scanf("%d%d%u", &n, &q, &s);
	for (int i = 1; i <= n; i++) {
		scanf("%d", p + i);
		(i[fa][0] = p[i]) ? addedge(p[i], i), 0 : (rt = i);
	}
	dfs1(rt, 1), dfs2(rt, rt);
	for (int j = 1; j < L; j++)
		for (int i = 1; i <= n; i++) i[fa][j] = i[fa][j - 1][fa][j - 1];
	for (int i = 1; i <= n; i++)
		if (i == i[top]) {
			c++, i[col] = c;
			for (int j = i; j[son]; j = j[son]) down[c].push_back(j);
			for (int j = i[p], l = down[c].size(); j && l--; j = j[p]) up[c].push_back(j);
		}
	for (int i = 1; i <= q; i++) {
		x = (get(s) ^ la) % n + 1, k = (get(s) ^ la) % x[_dep];
		if (!k)
			la = x;
		else {
			int high = (int)log2(k);
			k -= 1 << high;
			x = x[fa][high];
			if (k <= x[_dep] - x[top][_dep])
				la = x[top][col][down][x[_dep] - x[top][_dep] - k];
			else
				la = x[top][col][up][k - x[_dep] + x[top][_dep] - 1];
		}
		ans ^= 1ll * i * la;
	}
	printf("%lld", ans);
}