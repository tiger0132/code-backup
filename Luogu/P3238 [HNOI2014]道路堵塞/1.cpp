#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <queue>
#include <utility>

using pii = std::pair<int, int>;
const int N = 1e5 + 51, M = 2e5 + 52, INF = 0x3f3f3f3f;

int id[M];
struct edge {
	int to, next, w;
};
struct graph {
	edge e[M << 1];
	int head[N], dis[N], pre[N], cnt;
	void addedge(int x, int y, int z) { e[++cnt] = (edge){y, head[x], z}, head[x] = cnt; }
	template <typename Func>
	void sssp(int s, int t, Func f) {
		memset(dis, 0x3f, sizeof dis);
		std::priority_queue<pii> pq;
		pq.push(pii(dis[s] = 0, s));
		while (!pq.empty()) {
			int x = pq.top().second, y = -pq.top().first;
			pq.pop();
			if (x == t) continue;
			if (dis[x] < y) continue;
			for (int i = head[x]; i; i = e[i].next) {
				int nx = e[i].to;
				if (dis[nx] > y + e[i].w) {
					dis[nx] = y + e[i].w;
					pre[nx] = id[i] ? id[i] : pre[x];
					pq.push(pii(-dis[nx], nx));
				} else if (dis[nx] == y + e[i].w)
					pre[nx] = f(pre[nx], id[i] ? id[i] : pre[x]);
			}
		}
	}
} src, rev;

#define L() (lc ? lc : lc = newNode(l, mid))
#define R() (rc ? rc : rc = newNode(mid + 1, r))
#define chk(x, y) ((x) = std::min((x), (y)))
extern struct node *newNode(int, int);
struct node {
	int l, r, mid, min, tag;
	node *lc, *rc;
	void pushdown() {
		chk(L()->min, tag), chk(lc->tag, tag);
		chk(R()->min, tag), chk(rc->tag, tag);
		tag = INF;
	}
	void update(int L, int R, int x) {
		min = std::min(min, x);
		if (L <= l && r <= R) return (void)(chk(min, x), chk(tag, x));
		if (L <= mid) L()->update(L, R, x);
		if (mid < R) R()->update(L, R, x);
	}
	int query(int x) {
		if (l == r) return min;
		pushdown();
		if (x <= mid) return lc ? lc->query(x) : INF;
		return rc ? rc->query(x) : INF;
	}
} pool[N << 2], *root;
node *newNode(int l, int r) {
	static node *ptr = pool;
	*ptr = (node){l, r, (l + r) / 2, INF, INF};
	return ptr++;
}

int n, m, l, x, y, z;
int main() {
	scanf("%d%d%d", &n, &m, &l);
	root = newNode(0, l + 1);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		src.addedge(x, y, z);
		rev.addedge(y, x, z);
	}
	for (int i = 1; i <= l; i++) {
		scanf("%d", &x);
		id[x] = i;
	}
	rev.pre[n] = l + 1;
	src.sssp(1, n, [](int p, int q) { return p < q ? p : q; });
	rev.sssp(n, 1, [](int p, int q) { return p > q ? p : q; });
	for (int i = 1; i <= m; i++) {
		x = rev.e[i].to, y = src.e[i].to, z = src.e[i].w;
		if (id[i] || src.dis[x] == INF || rev.dis[y] == INF) continue;
		int l = src.pre[x] + 1, r = rev.pre[y] - 1;
		if (l <= r) root->update(l, r, src.dis[x] + rev.dis[y] + z);
	}
	for (int i = 1; i <= l; i++) {
		x = root->query(i);
		printf("%d\n", x == INF ? -1 : x);
	}
}