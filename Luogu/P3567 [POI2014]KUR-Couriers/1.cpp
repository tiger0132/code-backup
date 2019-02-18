// 在此问候 sb 出题人的全家。
// 卡你 mb 的空间啊
// 存个 l, r，用个指针你卡我个毛线啊
// 不陪智障出题人卡常数了，再见。

#include <algorithm>
#include <cstdio>

const int N = 5e5 + 55;

extern struct node pool[N * 22];
int newNode();
struct node {
	int v, lc, rc;
	void pushup() { v = pool[lc].v + pool[rc].v; }
	void build(int l, int r) {
		if (l == r) return;
		int mid = (l + r) >> 1;
		pool[lc = newNode()].build(l, mid);
		pool[rc = newNode()].build(mid + 1, r);
		pushup();
	}
	int insert(int x, int l, int r) {
		int ret = newNode(), mid = (l + r) >> 1;
		pool[ret] = *this;
		if (l == r) return (pool[ret].v = v + 1), ret;
		if (x <= mid)
			pool[ret].lc = pool[lc].insert(x, l, mid);
		else
			pool[ret].rc = pool[rc].insert(x, mid + 1, r);
		return pool[ret].pushup(), ret;
	}
} pool[N * 22];
int newNode() {
	static int ptr = 0;
	return ptr++;
}

int n, root[N];
int query(int L, int R, int x, int l = 1, int r = n) {
	if (l == r) return l;
	int ls = pool[pool[R].lc].v - pool[pool[L].lc].v, rs = pool[pool[R].rc].v - pool[pool[L].rc].v,
		mid = (l + r) >> 1;
	if (ls > x)
		return query(pool[L].lc, pool[R].lc, x, l, mid);
	else if (rs > x)
		return query(pool[L].rc, pool[R].rc, x, mid + 1, r);
	else
		return 0;
}

int n$, m, x, y, a[N], b[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
	std::sort(b + 1, b + n + 1);
	n$ = std::unique(b + 1, b + n + 1) - b - 1;
	pool[root[0] = newNode()].build(1, n);
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
		root[i] = pool[root[i - 1]].insert(a[i], 1, n);
	}
	while (m--) {
		scanf("%d%d", &x, &y);
		printf("%d\n", b[query(root[x - 1], root[y], (y - x + 1) / 2)]);
	}
}