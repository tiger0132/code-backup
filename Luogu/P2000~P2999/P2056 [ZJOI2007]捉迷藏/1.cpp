#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 4e5 + 54, INF = 1e9;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

int ord[N], col[N];
struct node *newNode();
struct node {
	int l, r, a, b, ans, x, y, z, w, mid;
	node *lc, *rc;
	void pushup() {
		ans = std::max({lc->z + rc->y, lc->w + rc->x, lc->ans, rc->ans});
		if (lc->b < rc->a)
			a = lc->a + rc->a - lc->b, b = rc->b;
		else
			a = lc->a, b = lc->b + rc->b - rc->a;  // fuck 三目运算
		x = std::max({lc->x, rc->x + lc->a - lc->b, rc->y + lc->a + lc->b});
		y = std::max({lc->y, rc->y - lc->a + lc->b});
		z = std::max({rc->z, lc->z - rc->a + rc->b, lc->w + rc->a + rc->b});
		w = std::max({rc->w, lc->w + rc->a - rc->b});
	}
	void set() {
		a = ord[l] == -2, b = ord[l] == -1, ans = -INF, x = y = z = w = !((ord[l] > 0) * (!col[ord[l]])) * -INF;
	}
	void build(int L, int R) {
		l = L, r = R, mid = (l + r) / 2;
		if (l == r) return set();
		(lc = newNode())->build(l, mid);
		(rc = newNode())->build(mid + 1, r);
		pushup();
	}
	void update(int x) {
		if (l == r) return set();
		x <= mid ? lc->update(x) : rc->update(x);
		pushup();
	}
} pool[N << 2], *null = pool, *rt;
node *newNode() {
	static node *ptr = pool + 1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int idx, l[N];
void dfs(int x, int p) {
	ord[++idx] = -1, ord[++idx] = x, l[x] = idx;
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x);
	ord[++idx] = -2;
}

int n, m, x, y, c;
char op[9];
int main() {
	scanf("%d", &n), c = n;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	dfs(1, 0);
	(rt = newNode())->build(1, idx);
	for (scanf("%d", &m); m--;) {
		scanf("%s", op);
		if (*op == 'G')
			printf("%d\n", c < 2 ? c - 1 : rt->ans);
		else {
			scanf("%d", &x);
			c += col[x] ? -1 : 1;
			col[x] ^= 1;
			rt->update(l[x]);
		}
	}
}