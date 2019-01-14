// WA, 80pts.

#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 3e5 + 53, M = 19;

extern struct $ *newNode(int l, int r), *null;
struct $ {
	int l, r, mid, ans;
	$ *lc, *rc;
	void pushup() { ans = lc->ans + rc->ans; }
	void update(int x, int y) {
		if (l == r) return (void)(ans += y);
		if (x <= mid) {
			if (lc == null) lc = newNode(l, mid);
			lc->update(x, y);
		} else {
			if (rc == null) rc = newNode(mid + 1, r);
			rc->update(x, y);
		}
		pushup();
	}
	int query(int x) {
		if (l == r) return ans;
		if (x <= mid)
			return lc->query(x);
		else
			return rc->query(x);
	}
	$ *merge($ *rhs) {
		if (this == null) return rhs;
		if (rhs == null) return this;
		if (l == r) return (ans += rhs->ans), this;
		lc = lc->merge(rhs->lc);
		rc = rc->merge(rhs->rc);
		pushup();
		return this;
	}
} pool[N << 4], *null = pool;
$ *newNode(int l, int r) {
	static $ *ptr = pool + 1;
	ptr->lc = ptr->rc = null;
	ptr->l = l;
	ptr->r = r;
	ptr->mid = (l + r) >> 1;
	return ptr++;
}

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]};
	head[x] = cnt;
	e[++cnt] = (edge){x, head[y]};
	head[y] = cnt;
}

int dep[N], par[N][M + 1];
void dfs1(int x, int p, int d) {
	dep[x] = d;
	par[x][0] = p;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs1(nx, x, d + 1);
	}
}

int n;
void init() {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= n; j++) {
			par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}
}
int tmp_;
int lca(int x, int y) {
	if (dep[x] > dep[y]) std::swap(x, y);
	int sub = dep[y] - dep[x];
	for (int i = 0; i <= M; i++) {
		if ((sub >> i) & 1) {
			y = par[y][i];
		}
	}
	if (x == y) return x;
	for (int i = M; ~i; i--) {
		if (par[x][i] != par[y][i]) {
			x = par[x][i];
			y = par[y][i];
		}
	}
	tmp_ = y;
	return par[x][0];
}

std::vector<int> addU[N], delU[N], addD[N], delD[N];
int ans[N], w[N];
$ *U[N], *D[N];
void dfs2(int x, int p) {
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs2(nx, x);
		U[x]->merge(U[nx]);
		D[x]->merge(D[nx]);
	}
	// printf("begin (%d):\n", x);
	for (int i : addU[x]) /*printf("\tadd up [%d]\n", i), */
		U[x]->update(i, 1);
	for (int i : addD[x]) /*printf("\tadd down [%d]\n", i), */
		D[x]->update(i, 1);
	ans[x] = U[x]->query(w[x] + dep[x]) + D[x]->query(w[x] - dep[x]);
	// printf("\tans: %d\n", ans[x]);
	for (int i : delU[x]) /*printf("\tdel up [%d]\n", i), */
		U[x]->update(i, -1);
	for (int i : delD[x]) /*printf("\tdel down [%d]\n", i), */
		D[x]->update(i, -1);
	// printf("end (%d).\n", x);
}

int m, x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	dfs1(1, 0, 1);
	init();
	for (int i = 1; i <= n; i++) {
		scanf("%d", w + i);
		U[i] = newNode(-n, 2 * n);
		D[i] = newNode(-n, 2 * n);
	}
	while (m--) {
		scanf("%d%d", &x, &y);
		int l = lca(x, y);
		// printf("%d -- %d -- %d\n", x, l, y);
		if (l == x) {
			addD[y].push_back(-dep[x]);
			delD[x].push_back(-dep[x]);
		} else if (l == y) {
			addU[x].push_back(dep[x]);
			delU[y].push_back(dep[x]);
		} else {
			int tmp = dep[x] - 2 * dep[l];
			addU[x].push_back(dep[x]);
			delU[l].push_back(dep[x]);
			addD[y].push_back(tmp);
			delD[tmp_].push_back(tmp);
		}
	}
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) {
		printf("%d\n", ans[i]);
	}
}