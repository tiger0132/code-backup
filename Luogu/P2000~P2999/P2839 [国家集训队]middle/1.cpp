#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using pii = std::pair<int, int>;
const int N = 2e4 + 42;
int n;

extern struct node *null, *newNode(node *, node *, int, int, int, bool);
node merge(node, node);
struct node {
	int la, ra, sum;
	node *lc, *rc;
	void pushup() {
		la = std::max(lc->la, lc->sum + rc->la);
		ra = std::max(rc->ra, lc->ra + rc->sum);
		sum = lc->sum + rc->sum;
	}
	void build(int l = 1, int r = n) {
		if (l == r) return void(la = ra = sum = 1);
		int mid = (l + r) / 2;
		(lc = newNode(null, null, 0, 0, 0, 0))->build(l, mid);
		(rc = newNode(null, null, 0, 0, 0, 0))->build(mid + 1, r);
		pushup();
	}
	node *update(int x, int l = 1, int r = n) {
		if (l == r) return newNode(lc, rc, -1, -1, -1, 0);
		int mid = (l + r) / 2;
		if (x <= mid) return newNode(lc->update(x, l, mid), rc, la, ra, sum, 1);
		return newNode(lc, rc->update(x, mid + 1, r), la, ra, sum, 1);
	}
	node query(int L, int R, int l = 1, int r = n) {
		if (L <= l && r <= R) return *this;
		int mid = (l + r) / 2;
		if (mid >= R) return lc->query(L, R, l, mid);
		if (mid < L) return rc->query(L, R, mid + 1, r);
		return merge(lc->query(L, R, l, mid), rc->query(L, R, mid + 1, r));
	}
} pool[N * 90], *null = pool, *root[N];
node *newNode(node *lc, node *rc, int la, int ra, int sum, bool up) {
	static node *ptr = pool + 1;
	*ptr = (node){la, ra, sum, lc, rc};
	if (up) ptr->pushup();
	return ptr++;
}
node merge(node x, node y) {
	node ret;
	ret.la = std::max(x.la, x.sum + y.la);
	ret.ra = std::max(y.ra, x.ra + y.sum);
	ret.sum = x.sum + y.sum;
	return ret;
}

int q[4], &l1 = q[0], &r1 = q[1], &l2 = q[2], &r2 = q[3];
pii a[N];
bool check(int x) {
	int u, v = 0, w;
	u = root[x]->query(l1, r1).ra;
	if (r1 + 1 <= l2 - 1) v = root[x]->query(r1 + 1, l2 - 1).sum;
	w = root[x]->query(l2, r2).la;
	// printf("%d: %d %d %d\n", x, u, v, w);
	return u + v + w >= 0;
}

int m, x, lans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		a[i] = pii(x, i);
	}
	std::sort(a + 1, a + n + 1);
	(root[1] = newNode(null, 0, 0, 0, 0, 0))->build();
	for (int i = 2; i <= n; i++) root[i] = root[i - 1]->update(a[i - 1].second);
	for (scanf("%d", &m); m--;) {
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		l1 = (l1 + lans) % n + 1, r1 = (r1 + lans) % n + 1;
		l2 = (l2 + lans) % n + 1, r2 = (r2 + lans) % n + 1;
		std::sort(q, q + 4);
		int l = 1, r = n;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (check(mid))
				lans = mid, l = mid + 1;
			else
				r = mid - 1;
		}
		printf("%d\n", lans = a[lans].first);
	}
}