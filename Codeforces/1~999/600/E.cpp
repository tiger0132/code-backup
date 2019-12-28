#include <algorithm>
#include <cstdio>

const int N = 1e5+15;

extern struct node *newNode(int l, int r), *null;

struct node {
	int max, sum, l, r, mid;
	long long ans;
	node *lc, *rc;
	void pushup() {
		sum = std::max(lc->sum, rc->sum);
		if (lc->sum >= rc->sum) {
			max = lc->max;
			ans = lc->ans;
			if (lc->sum == rc->sum) ans += rc->ans;
		} else {
			max = rc->max;
			ans = rc->ans;
		}
	}
	void update(int x) {
		if (l == r) { max = ans = x; sum++; return; }
		if (x <= mid) {
			if (lc == null) lc = newNode(l, mid);
			lc->update(x);
		} else {
			if (rc == null) rc = newNode(mid+1, r);
			rc->update(x);
		}
		pushup();
	}
	node *merge(node *rhs) {
		if (this == null) return rhs;
		if (rhs == null) return this;
		if (l == r) { max = ans = l; sum += rhs->sum; return this; }
		lc = lc->merge(rhs->lc);
		rc = rc->merge(rhs->rc);
		pushup();
		return this;
	}
} pool[int(3e6+36)], *null = pool;
void init() { null->max = 0xcfcfcfcf; }
node *newNode(int l = 1, int r = 1e5) {
	static node *ptr = pool+1;
	ptr->lc = ptr->rc = null;
	ptr->l = l; ptr->r = r; ptr->mid = (l+r)>>1;
	return ptr++;
}

struct edge { int to, next; } e[N<<1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}; head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}; head[y] = cnt;
}

long long ans[N];
node *root[N];
int c[N];

void dfs(int x, int par) {
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par) continue;
		dfs(nx, x);
		root[x]->merge(root[nx]);
	}
	root[x]->update(c[x]);
	ans[x] = root[x]->ans;
}

int n, x, y;

int main() {
	init();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", c+i);
		root[i] = newNode();
	}
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	dfs(1, -1);
	for (int i = 1; i <= n; i++) {
		printf("%I64d ", ans[i]);
	}
}