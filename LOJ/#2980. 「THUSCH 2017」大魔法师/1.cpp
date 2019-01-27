#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int P = 998244353, N = 2.5e5 + 5e3;

struct $ {
	int a[4][4];
	inline $() { memset(a, 0, sizeof a); }
	inline $(const $& rhs) { memcpy(a, rhs.a, sizeof a); }
	inline void clear() { memset(a, 0, sizeof a); }
	inline void one() {
		memset(a, 0, sizeof a);
		a[0][0] = a[1][1] = a[2][2] = a[3][3] = 1;
	}
	inline void operator*=(const $& rhs) {
		int ret[4][4];
		// clang-format off
		ret[0][0] = ((ll)rhs.a[0][0] * a[0][0] + (ll)rhs.a[0][1] * a[1][0] + (ll)rhs.a[0][2] * a[2][0] + (ll)rhs.a[0][3] * a[3][0]) % P;
		ret[0][1] = ((ll)rhs.a[0][0] * a[0][1] + (ll)rhs.a[0][1] * a[1][1] + (ll)rhs.a[0][2] * a[2][1] + (ll)rhs.a[0][3] * a[3][1]) % P;
		ret[0][2] = ((ll)rhs.a[0][0] * a[0][2] + (ll)rhs.a[0][1] * a[1][2] + (ll)rhs.a[0][2] * a[2][2] + (ll)rhs.a[0][3] * a[3][2]) % P;
		ret[0][3] = ((ll)rhs.a[0][0] * a[0][3] + (ll)rhs.a[0][1] * a[1][3] + (ll)rhs.a[0][2] * a[2][3] + (ll)rhs.a[0][3] * a[3][3]) % P;
		ret[1][0] = ((ll)rhs.a[1][0] * a[0][0] + (ll)rhs.a[1][1] * a[1][0] + (ll)rhs.a[1][2] * a[2][0] + (ll)rhs.a[1][3] * a[3][0]) % P;
		ret[1][1] = ((ll)rhs.a[1][0] * a[0][1] + (ll)rhs.a[1][1] * a[1][1] + (ll)rhs.a[1][2] * a[2][1] + (ll)rhs.a[1][3] * a[3][1]) % P;
		ret[1][2] = ((ll)rhs.a[1][0] * a[0][2] + (ll)rhs.a[1][1] * a[1][2] + (ll)rhs.a[1][2] * a[2][2] + (ll)rhs.a[1][3] * a[3][2]) % P;
		ret[1][3] = ((ll)rhs.a[1][0] * a[0][3] + (ll)rhs.a[1][1] * a[1][3] + (ll)rhs.a[1][2] * a[2][3] + (ll)rhs.a[1][3] * a[3][3]) % P;
		ret[2][0] = ((ll)rhs.a[2][0] * a[0][0] + (ll)rhs.a[2][1] * a[1][0] + (ll)rhs.a[2][2] * a[2][0] + (ll)rhs.a[2][3] * a[3][0]) % P;
		ret[2][1] = ((ll)rhs.a[2][0] * a[0][1] + (ll)rhs.a[2][1] * a[1][1] + (ll)rhs.a[2][2] * a[2][1] + (ll)rhs.a[2][3] * a[3][1]) % P;
		ret[2][2] = ((ll)rhs.a[2][0] * a[0][2] + (ll)rhs.a[2][1] * a[1][2] + (ll)rhs.a[2][2] * a[2][2] + (ll)rhs.a[2][3] * a[3][2]) % P;
		ret[2][3] = ((ll)rhs.a[2][0] * a[0][3] + (ll)rhs.a[2][1] * a[1][3] + (ll)rhs.a[2][2] * a[2][3] + (ll)rhs.a[2][3] * a[3][3]) % P;
		ret[3][0] = ((ll)rhs.a[3][0] * a[0][0] + (ll)rhs.a[3][1] * a[1][0] + (ll)rhs.a[3][2] * a[2][0] + (ll)rhs.a[3][3] * a[3][0]) % P;
		ret[3][1] = ((ll)rhs.a[3][0] * a[0][1] + (ll)rhs.a[3][1] * a[1][1] + (ll)rhs.a[3][2] * a[2][1] + (ll)rhs.a[3][3] * a[3][1]) % P;
		ret[3][2] = ((ll)rhs.a[3][0] * a[0][2] + (ll)rhs.a[3][1] * a[1][2] + (ll)rhs.a[3][2] * a[2][2] + (ll)rhs.a[3][3] * a[3][2]) % P;
		ret[3][3] = ((ll)rhs.a[3][0] * a[0][3] + (ll)rhs.a[3][1] * a[1][3] + (ll)rhs.a[3][2] * a[2][3] + (ll)rhs.a[3][3] * a[3][3]) % P;
		// clang-format on
		memcpy(a, ret, sizeof a);
	}
	inline $ operator+(const $& rhs) const {
		$ ret;
		for (int i = 0; i < 4; i++) {
			ret.a[i][0] = (a[i][0] + rhs.a[i][0]) % P;
		}
		return ret;
	}
};

struct node* newNode();
struct node {
	$ m, tag;
	int l, r, mid;
	node *lc, *rc;
	inline void pushup() { m = lc->m + rc->m; }
	inline void pushdown() {
		lc->m *= tag;
		rc->m *= tag;
		lc->tag *= tag;
		rc->tag *= tag;
		tag.one();
	}
	void build(int L, int R) {
		l = L, r = R, mid = (l + r) >> 1;
		tag.one();
		if (l == r) {
			m.a[3][0] = 1;
			return (void)scanf("%d%d%d", m.a[0], m.a[1], m.a[2]);
		}
		(lc = newNode())->build(l, mid);
		(rc = newNode())->build(mid + 1, r);
		pushup();
	}
	void update(int L, int R, const $& x) {
		if (L <= l && r <= R) {
			m *= x;
			tag *= x;
			return;
		}
		pushdown();
		if (L <= mid) lc->update(L, R, x);
		if (mid < R) rc->update(L, R, x);
		pushup();
	}
	void query(int L, int R, $& ret) {
		if (L <= l && r <= R) return void(ret = ret + m);
		pushdown();
		if (L <= mid) lc->query(L, R, ret);
		if (mid < R) rc->query(L, R, ret);
	}
} pool[N << 2], *null = pool, *root;
node* newNode() {
	static node* ptr = pool + 1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int n, m, op, l, r, x;
$ t;
int main() {
	scanf("%d", &n);
	(root = newNode())->build(1, n);
	for (scanf("%d", &m); m--;) {
		scanf("%d%d%d", &op, &l, &r);
		if (op == 7) {
			t.clear();
			root->query(l, r, t);
			printf("%d %d %d\n", t.a[0][0], t.a[1][0], t.a[2][0]);
			continue;
		}
		t.one();
		if (op > 3) scanf("%d", &x);
		// clang-format off
		switch (op) {
			case 1: t.a[0][1] = 1; break;
			case 2: t.a[1][2] = 1; break;
			case 3: t.a[2][0] = 1; break;
			case 4: t.a[0][3] = x; break;
			case 5: t.a[1][1] = x; break;
			case 6: t.a[2][2] = 0; t.a[2][3] = x; break;
		}
		root->update(l, r, t);
		// clang-format on
	}
}