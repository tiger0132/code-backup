#include <utility>
#include <cstdio>
#include <queue>
#include <cmath>
#include <set>

#define L first
#define R second

typedef long long ll;

const int N = 6e5+56;

inline int f(int x) {
	if (~x & 1) return x & 3;
	return 2 * (x - 1) + (x & 3);
}

extern struct node *newNode(int l, int r), *null;
struct node {
	int l, r, mid, l$, r$, vis; ll ans;
	node *lc, *rc;
	void pushup() {
		l$ = lc != null ? lc->l$ : rc->l$;
		r$ = rc != null ? rc->r$ : lc->r$;
		ans = lc->ans ^ rc->ans;
		if (lc != null && rc != null) {
			ans ^= ((ll)rc->l$ * rc->l$ - (ll)lc->r$ * lc->r$);
		}
		vis = lc->vis && rc->vis;
	}
	void update(int L, int R) {
		if (vis) return;
		if (L <= l && r <= R) {
			l$ = l; r$ = r; vis = 1;
			ans = f(r$) ^ f(l$);
			return;
		}
		if (L <= mid) {
			if (lc == null) lc = newNode(l, mid);
			lc->update(L, R);
		}
		if (mid < R) {
			if (rc == null) rc = newNode(mid+1, r);
			rc->update(L, R);
		}
		pushup();
	}
} pool[N<<4], *root, *null = pool;
node *newNode(int l = 1, int r = 1e9) {
	static node *ptr = pool+1;
	ptr->lc = ptr->rc = null;
	ptr->l = l; ptr->r = r; ptr->mid = (l+r)>>1;
	return ptr++;
}

int n, op, l, r;

int main() {
	root = newNode();
	for (scanf("%d", &n); n--; ) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d", &l, &r);
			root->update(l, r);
		} else {
			printf("%lld\n", root->ans);
		}
	}
}