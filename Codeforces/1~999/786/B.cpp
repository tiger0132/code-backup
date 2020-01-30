#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2
#define int long long

const int N = 8e5 + 58;
struct edge {
	int to, next, w;
} e[N * 5];
int head[N], cnt;
void addedge(int x, int y, int z, int op = 0) {
	if (op) std::swap(x, y);
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
}

int ch[N][2], nc;
void build(int x, int l, int r, int op) {
	if (l == r) return addedge(l, x, 0, op);
	build(x[L] = ++nc, l, mid, op), build(x[R] = ++nc, mid + 1, r, op);
	addedge(x[L], x, 0, op), addedge(x[R], x, 0, op);
}
void upd(int x, int l, int r, int ql, int qr, int y, int z, int op) {
	if (ql <= l && r <= qr) return addedge(x, y, z, op);
	if (ql <= mid) upd(x[L], l, mid, ql, qr, y, z, op);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, y, z, op);
}

int dis[N];
struct node {
	int x, d;
	bool operator<(const node& rhs) const { return d > rhs.d; }
};
std::priority_queue<node> pq;
void spfa(int s) {
	memset(dis, 0x3f, sizeof dis), dis[s] = 0;
	for (pq.push((node){s, 0}); !pq.empty();) {
		node t = pq.top();
		pq.pop();
		int x = t.x, d = t.d;
		if (d != x[dis]) continue;
		for (int i = head[x], nx; i; i = e[i].next)
			if ((nx = e[i].to)[dis] > x[dis] + e[i].w)
				nx[dis] = x[dis] + e[i].w, pq.push((node){nx, nx[dis]});
	}
}

int n, m, s, rt[2], op, x, y, z, w;
signed main() {
	scanf("%lld%lld%lld", &n, &m, &s), nc = n;
	build(rt[0] = ++nc, 1, n, 0);  // out,	[] -> ()
	build(rt[1] = ++nc, 1, n, 1);  // in,	() -> []
	while (m--) {
		scanf("%lld%lld%lld%lld", &op, &x, &y, &z);
		if (op == 1)
			addedge(x, y, z);
		else {
			scanf("%lld", &w), op = 3 - op;
			upd(rt[op], 1, n, y, z, x, w, op);
		}
	}
	spfa(s);
	for (int i = 1; i <= n; i++)
		printf("%lld ", dis[i] == 0x3f3f3f3f3f3f3f3f ? -1 : dis[i]);
}