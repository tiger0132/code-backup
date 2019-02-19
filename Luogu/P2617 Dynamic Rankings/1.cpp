#include <algorithm>
#include <cstdio>

const int N = 1e5 + 51;
extern struct node* null;
struct node {
	node *lc, *rc;
	int v;
	void pushup() { v = lc->v + rc->v; }
	node(node* lc_, node* rc_, int v_) : lc(lc_), rc(rc_), v(v_) {}
	node* insert(int l, int r, int x, int o) {
		int mid = (l + r) >> 1;
		if ((v += o) && l == r) return new node(null, null, v + 1);
		if (x <= mid) return new node(lc->insert(l, mid, x, o), rc, v + 1);
		return new node(lc, rc->insert(mid + 1, r, x, o), v + 1);
	}
}* null = new node(0, 0, 0), *rt[N];

node *L[N], *R[N];
int n, m, cl, cr;
inline int lowbit(int x) { return x & -x; }
int query(int x, int l = 1, int r = n + m) {
	if (l == r) return l;
	int sum = 0, mid = (l + r) >> 1;
	for (int i = 1; i <= cr; i++) sum += R[i]->lc->v;
	// printf("(%d)", sum);
	for (int i = 1; i <= cl; i++) sum -= L[i]->lc->v;
	// printf("[%d, %d]: %d\n", l, mid, sum);
	if (x <= sum) {
		for (int i = 1; i <= cl; i++) L[i] = L[i]->lc;
		for (int i = 1; i <= cr; i++) R[i] = R[i]->lc;
		return query(x, l, mid);
	} else {
		for (int i = 1; i <= cl; i++) L[i] = L[i]->rc;
		for (int i = 1; i <= cr; i++) R[i] = R[i]->rc;
		return query(x - sum, mid + 1, r);
	}
}
void add(int x, int o = 1) {
	for (int i = x; i <= n; i += lowbit(i)) rt[i]->insert(1, n + m, x, o);
}

int src[N], a[N], b[N], c[N], t[N], n$;
char op[2];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", src + i), t[++n$] = src[i];
	for (int i = 1; i <= m; i++) {
		scanf("%s%d%d", op, a + i, b + i);
		if (*op == 'Q')
			scanf("%d", c + i);
		else
			t[++n$] = b[i];
	}
	std::sort(t + 1, t + n$ + 1);
	n$ = std::unique(t + 1, t + n$ + 1) - t - 1;
	for (int i = 1; i <= n; i++) add(src[i] = std::lower_bound(t + 1, t + n$ + 1, src[i]) - t);

	for (int i = 1; i <= m; i++) {
		if (c[i]) {
			cl = cr = 0;
			for (int j = a[i] - 1; j; j -= lowbit(j)) L[++cl] = rt[j];
			for (int j = b[i]; j; j -= lowbit(j)) R[++cr] = rt[j];
			printf("%d\n", t[query(c[i])]);
		} else {
			b[i] = std::lower_bound(t + 1, t + n$ + 1, b[i]) - t;
			add(src[a[i]], -1);
			// printf("del %d\n", src[a[i]]);
			add(src[a[i]] = b[i]);
			// printf("add %d\n", src[a[i]]);
		}
	}
}