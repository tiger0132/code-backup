#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <cstdio>
#define L(x) ch[x][0]
#define R(x) ch[x][1]
#define __ __gnu_pbds

typedef long long ll;
typedef __::tree<ll, __::null_type, std::less<ll>,
					 __::rb_tree_tag,
					 __::tree_order_statistics_node_update> $;
const int N = int(5e4+45);

void join($& x, const $& y) {
	for (const auto& i : y) {
		x.insert(i);
	}
}

struct node *newNode();
struct node {
	int l, r, mid; $ _;
	node *lc, *rc;
	void pushup() { _ = lc->_; join(_, rc->_); }
	void build(int L, int R, ll *a) {
		l = L; r = R; mid = (l+r) >> 1;
		if (l == r) return (void)_.insert(a[L]);
		(lc = newNode())->build(l, mid, a);
		(rc = newNode())->build(mid+1, r, a);
		pushup();
	}
	void update(int x, ll y, ll z) {
		_.erase(y); _.insert(z);
		if (l == r) return;
		if (x <= mid) lc->update(x, y, z);
		else rc->update(x, y, z);
	}
	void query(int L, int R, $& ans) {
		if (L <= l && r <= R) return (void)join(ans, _);
		if (L <= mid) lc->query(L, R, ans);
		if (mid < R) rc->query(L, R, ans);
	}
} pool[N<<2], *root, *null = pool;
node *newNode() {
	static node *ptr = pool+1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int n, m, op, x, y;
ll a[N], z;
$ tmp;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a+i);
		(a[i] *= N) += i;
	}
	(root = newNode())->build(1, n, a);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op ^ 3) scanf("%lld", &z);
		if (op != 3) {
			tmp.clear();
			tmp.insert(-2147483647ll * N);
			tmp.insert(2147483647ll * N);
			root->query(x, y, tmp);
			// for (const auto& i : tmp) {
			// 	printf("%lld ", i / N);
			// } puts("");
		}
		switch (op) {
			case 1: printf("%lu\n", tmp.order_of_key(z * N)); break;
			case 2: printf("%lld\n", *tmp.find_by_order(z) / N); break;
			case 3: root->update(x, a[x] * N + x, y); a[x] = y; break;
			case 4: printf("%lld\n", *--tmp.lower_bound(z * N) / N); break;
			case 5: printf("%lld\n", *tmp.lower_bound((z+1) * N) / N); break;
		}
	}
}