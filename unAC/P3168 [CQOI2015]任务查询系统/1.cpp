#include <cstdio>
#include <vector>

typedef long long ll;
const int N = 1e5 + 51, L = 1e7;

extern struct node *newNode(), *null;
struct node {
	int l, r, mid, c;
	node *lc, *rc;
	ll v;
	void pushup() { v = lc->v + rc->v, c = lc->c + rc->c; }
	void build(int L, int R) {
		l = L, r = R, mid = (l + r) >> 1;
		if (l == r) return;
		(lc = newNode())->build(l, mid);
		(lc = newNode())->build(mid + 1, r);
		pushup();
	}
	node *insert(int x) {
		node *ret = newNode();
		*ret = *this;
		if (l == r) return (ret->v += x, ret->c += (x < 0 ? -1 : 1)), ret;
		if (x <= mid) ret->lc = lc->insert(x);
		if (mid < x) ret->rc = rc->insert(x);
		return ret->pushup(), ret;
	}
	ll query(int x) {
		if (x > c) return v;
		if (l == r) return 1ll * x * l;
		if (x < lc->c) return lc->query(x);
		if (x > lc->c) return lc->v + rc->query(x - lc->c);
		return lc->v;
	}
} pool[N << 6], *null = pool, *rt[N];
node *newNode() {
	static node *ptr = pool + 1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int n, m, x, y, z, w;
std::vector<int> v[N];
ll lans = 1;
int main() {
	null->lc = null->rc = null;
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		v[x].push_back(z);
		v[y + 1].push_back(-z);
	}
	rt[0] = newNode();
	rt[0]->l = 1, rt[0]->r = L;
	for (int i = 1; i <= n; i++) {
		rt[i] = rt[i - 1];
		for (int j : v[i]) rt[i] = rt[i]->insert(j);
	}
	while (n--) {
		scanf("%d%d%d%d", &x, &y, &z, &w);
		int k = 1 + (y * lans + z) % w;
		printf("[%d, %d]: ", x, k);
		printf("%lld\n", lans = rt[x]->query(k));
	}
}