// Greek Question Mark: ';'

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 5e5 + 55, INF = 0x3f3f3f3f;
struct tup {
	int l, r, v;
	friend tup operator+(const tup &L, const tup &R) { return {L.l, R.r, L.v + R.v}; }
	friend bool operator<(const tup &L, const tup &R) { return L.v < R.v; }
};
struct tag {
	tup lmax, rmax, gmax, lmin, rmin, gmin, sum;
	bool rev;
	tag(int l = 0, int x = 0) : rev() { lmax = rmax = gmax = lmin = rmin = gmin = sum = {l, l, x}; }
	friend tag operator+(const tag &L, const tag &R) {
		tag ret;
		ret.lmax = std::max(L.lmax, L.sum + R.lmax);
		ret.lmin = std::min(L.lmin, L.sum + R.lmin);
		ret.rmax = std::max(R.rmax, L.rmax + R.sum);
		ret.rmin = std::min(R.rmin, L.rmin + R.sum);
		ret.gmax = std::max({L.gmax, R.gmax, L.rmax + R.lmax});
		ret.gmin = std::min({L.gmin, R.gmin, L.rmin + R.lmin});
		ret.sum = L.sum + R.sum;
		return ret;
	}
};
struct node *newNode();
struct node {
	int l, r, mid;
	node *lc, *rc;
	tag t;
	void pushup() { t = lc->t + rc->t; }
	void rev() {
		std::swap(t.lmax, t.lmin), std::swap(t.rmax, t.rmin), std::swap(t.gmax, t.gmin), t.rev ^= 1;
		t.lmax.v *= -1, t.lmin.v *= -1, t.rmax.v *= -1, t.rmin.v *= -1, t.gmax.v *= -1, t.gmin.v *= -1, t.sum.v *= -1;
	}
	void pushdown() {
		if (t.rev) lc->rev(), rc->rev(), t.rev ^= 1;
	}
	void build(int L, int R, int *a) {
		l = L, r = R, mid = (l + r) / 2;
		if (l == r) return void(t = tag(l, a[l]));
		(lc = newNode())->build(l, mid, a);
		(rc = newNode())->build(mid + 1, r, a);
		pushup();
	}
	void update(int x, int y) {
		if (l == r) return void(t = tag(x, y));
		pushdown();
		x <= mid ? lc->update(x, y) : rc->update(x, y);
		pushup();
	}
	void update2(int L, int R) {
		if (L <= l && r <= R) return rev();
		pushdown();
		if (L <= mid) lc->update2(L, R);
		if (mid < R) rc->update2(L, R);
		pushup();
	}
	tag query(int L, int R) {
		if (L <= l && r <= R) return t;
		pushdown();
		if (R <= mid) return lc->query(L, R);
		if (mid < L) return rc->query(L, R);
		return lc->query(L, R) + rc->query(L, R);
	}
} pool[N << 2], *null = pool, *root;
node *newNode() {
	static node *ptr = pool + 1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int n, m, op, lans, x, y, z, a[N];
std::queue<tag> q;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	(root = newNode())->build(1, n, a);
	for (scanf("%d", &m); m--;) {
		scanf("%d%d%d", &op, &x, &y);
		if (op) {
			for (lans = !scanf("%d", &z); z--;) {
				tag t = root->query(x, y);
				if (t.gmax.v < 0) break;
				lans += t.gmax.v;
				root->update2(t.gmax.l, t.gmax.r);
				q.push(t);
			}
			for (tag i; !q.empty(); q.pop()) i = q.front(), root->update2(i.gmax.l, i.gmax.r);
			printf("%d\n", lans);
		} else {
			root->update(x, y);
		}
	}
}