#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <queue>
#include <utility>
#include <vector>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

typedef std::pair<int, int> pii;
const int N = 6e5 + 56;

std::vector<int> g[N];
int deg[N];
void addedge(int x, int y) { x[g].push_back(y), y[deg]++; }

int ch[N][2], nc;
void build(int x, int l, int r) {
	if (l == r) return addedge(l, x);
	build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r);
	addedge(x[L], x), addedge(x[R], x);
}
void link(int x, int l, int r, int ql, int qr, int y) {
	if (ql <= l && r <= qr) return addedge(x, y);
	if (ql <= mid) link(x[L], l, mid, ql, qr, y);
	if (mid < qr) link(x[R], mid + 1, r, ql, qr, y);
}
int rt;

std::vector<pii> initial;
int ans[N], orig[N];

int n, s, m, x, y, l, r, k, cnt;
std::queue<int> q;
int main() {
	scanf("%d%d%d", &n, &s, &m), nc = n;
	for (int i = 1; i <= s; i++) {
		scanf("%d%d", &x, &y);
		initial.push_back({y, x});
		x[ans] = y, x[orig] = y;
	}
	// std::sort(initial.begin(), initial.end());
	build(rt = ++nc, 1, n);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &l, &r, &k);
		int exchange = ++nc;
		for (int j = 0, la = l; j < k; j++) {
			scanf("%d", &x);
			if (la < x) link(rt, 1, n, la, x - 1, exchange);
			addedge(exchange, x);
			la = x + 1;
		}
		if (x < r) link(rt, 1, n, x + 1, r, exchange);
	}
	for (int i = 1; i <= nc; i++)
		if (!i[deg]) i[ans] = std::max(i[ans], 1), q.push(i);
	for (; !q.empty(); q.pop()) {
		int x = q.front();
		cnt += (x <= n);
		for (int nx : x[g]) {
			nx[ans] = std::max(nx[ans], x[ans] + (nx <= n));
			if (!--nx[deg]) q.push(nx);
		}
	}
	if (cnt != n) return puts("NIE"), 0;
	for (int i = 1; i <= n; i++)
		if ((i[orig] && i[ans] != i[orig]) || i[ans] > 1e9) return puts("NIE"), 0;
	puts("TAK");
	for (int i = 1; i <= n; i++) printf("%d%c", i[ans], " \n"[i == n]);
}