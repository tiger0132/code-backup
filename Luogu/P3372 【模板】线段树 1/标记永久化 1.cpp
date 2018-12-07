#include <cstdio>

const int N = 1e5+15;

struct node *newNode();

struct node {
	long long val, add;
	int l, r, mid;
	node *lc, *rc;
	void pushup() { val = lc->val + rc->val; }
	void build(int L, int R) {
		val = 0; add = 0; l = L; r = R; mid = (l+r) >> 1;
		if (l == r) { scanf("%lld", &val); return; }
		(lc = newNode())->build(l, mid);
		(rc = newNode())->build(mid+1, r);
		pushup();
	} 
	void update(int L, int R, long long x) {
		val += x * (R-L+1);
		if (L == l && r == R) { add += x; return; }
		if (R <= mid) lc->update(L, R, x);
		else if (mid < L) rc->update(L, R, x);
		else lc->update(L, mid, x), rc->update(mid+1, R, x);
	}
	long long query(int L, int R, long long tag = 0) {
		if (L == l && r == R) return val + tag * (r-l+1);
		tag += add;
		if (R <= mid) return lc->query(L, R, tag);
		else if (mid < L) return rc->query(L, R, tag);
		else return lc->query(L, mid, tag) + rc->query(mid+1, R, tag);
	}
} pool[N<<2], *root, *null = pool;

node *newNode() {
	static node *ptr = pool+1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int n, m, op, x, y, z;

int main() {
	scanf("%d%d", &n, &m);
	(root = newNode())->build(1, n);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) {
			scanf("%d", &z);
			root->update(x, y, z);
		} else {
			printf("%lld\n", root->query(x, y));
		}
	}
}