#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 5e5 + 52, M = 19;

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = {y, x[head]}, x[head] = cnt;
	e[++cnt] = {x, y[head]}, y[head] = cnt;
}

struct node {
	int x, y;
	bool operator<(const node& r) const { return x < r.x; }
};
struct query {
	int x, y1, y2, *ans, op;
	bool operator<(const query& r) const { return x < r.x; }
};

int lb[N], rb[N], dep[N], f[N][M], idx;
void dfs(int x, int p) {
	for (int i = x[head], nx = x[lb] = ++idx; i; i = e[i].next)
		if ((nx = e[i].to) != p) nx[dep] = x[dep] + 1, nx[f][0] = x, dfs(nx, x);
	x[rb] = idx;
}

int n, m, q, x, y, bit[N], s[N], ans[N];
std::vector<query> qry;
std::vector<node> p;

void add(int x, int v) {
	for (; x <= 2 * n; x += x & -x) bit[x] += v;
}
int sum(int x) {
	int r = 0;
	for (; x; x -= x & -x) r += bit[x];
	return r;
}
int get(int x, int y) {
	int sub = y[dep] - x[dep] - 1;
	for (int i = M - 1; i >= 0; i--)
		if ((sub >> i) & 1) y = y[f][i];
	return y;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs(1, 0);
	for (int j = 1; j < M; j++)
		for (int i = 1; i <= n; i++) i[f][j] = i[f][j - 1][f][j - 1];
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &x, &y), p.push_back({x[lb], y[lb]}), p.push_back({y[lb], x[lb]});
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d", &x, &y);
		if (x[lb] > y[lb]) std::swap(x, y);
		if (x[lb] < y[lb] && y[rb] <= x[rb]) {
			int z = get(x, y);
			qry.push_back({y[lb] - 1, 1, n, ans + i, -1});
			qry.push_back({y[rb], 1, n, ans + i, 1});
			qry.push_back({y[lb] - 1, z[lb], z[rb], ans + i, 1});
			qry.push_back({y[rb], z[lb], z[rb], ans + i, -1});
		} else {
			qry.push_back({x[lb] - 1, y[lb], y[rb], ans + i, -1});
			qry.push_back({x[rb], y[lb], y[rb], ans + i, 1});
		}
	}
	std::sort(p.begin(), p.end());
	std::sort(qry.begin(), qry.end());
	auto it1 = qry.begin();
	auto it2 = p.begin();
	for (; it1 != qry.end(); it1++) {
		for (; it2 != p.end() && it2->x <= it1->x; it2++) add(it2->y, 1);
		*it1->ans += it1->op * (sum(it1->y2) - sum(it1->y1 - 1));
	}
	for (int i = 1; i <= q; i++) printf("%d\n", i[ans] + 1);
}