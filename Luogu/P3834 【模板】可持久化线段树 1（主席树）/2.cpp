#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52, M = 1e9;
extern struct node* null;
struct node {
	node *lc, *rc;
	int v;
	void pushup() { v = lc->v + rc->v; }
	node(node* lc_, node* rc_, int v_) : lc(lc_), rc(rc_), v(v_) {}
	node* insert(int l, int r, int x) {
		int mid = (l + r) >> 1;
		if (l == r) return new node(null, null, v + 1);
		if (x <= mid) return new node(lc->insert(l, mid, x), rc, v + 1);
		return new node(lc, rc->insert(mid + 1, r, x), v + 1);
	}
}* null = new node(0, 0, 0), *root[N];

int n;
int query(node* L, node* R, int x, int l = 0, int r = M) {
	if (l == r) return l;
	int sum = R->lc->v - L->lc->v, mid = (l + r) >> 1;
	if (x <= sum)
		return query(L->lc, R->lc, x, l, mid);
	else
		return query(L->rc, R->rc, x - sum, mid + 1, r);
}

int x, y, z, n$, m, a[N];
int main() {
	null->lc = null->rc = null;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	root[0] = null;
	for (int i = 1; i <= n; i++) root[i] = root[i - 1]->insert(0, M, a[i]);
	while (m--) {
		scanf("%d%d%d", &x, &y, &z);
		printf("%d\n", query(root[x - 1], root[y], z));
	}
}