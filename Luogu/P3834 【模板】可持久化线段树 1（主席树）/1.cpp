#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;
struct node* newNode();
struct node {
	int l, r, mid, v;
	node *lc, *rc;
	void pushup() { v = lc->v + rc->v; }
	void build(int L, int R) {
		l = L, r = R, mid = (l + r) >> 1;
		if (l == r) return;
		(lc = newNode())->build(l, mid);
		(rc = newNode())->build(mid + 1, r);
		pushup();
	}
	node* insert(int x) {
		node* ret = newNode();
		*ret = *this;
		if (l == r) return (ret->v = v + 1), ret;
		if (x <= mid)
			ret->lc = lc->insert(x);
		else
			ret->rc = rc->insert(x);
		return ret->pushup(), ret;
	}
} pool[N << 5], *root[N];
node* newNode() {
	static node* ptr = pool;
	return ptr++;
}

int n;
int query(node* L, node* R, int x) {
	if (L->l == L->r) return L->l;
	int sum = R->lc->v - L->lc->v;
	if (x <= sum)
		return query(L->lc, R->lc, x);
	else
		return query(L->rc, R->rc, x - sum);
}

int x, y, z, n$, m, a[N], b[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
	std::sort(b + 1, b + n + 1);
	n$ = std::unique(b + 1, b + n + 1) - b - 1;
	(root[0] = newNode())->build(1, n);
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
		root[i] = root[i - 1]->insert(a[i]);
	}
	while (m--) {
		scanf("%d%d%d", &x, &y, &z);
		printf("%d\n", b[query(root[x - 1], root[y], z)]);
	}
}