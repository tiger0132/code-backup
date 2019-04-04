// WARNING: THIS CODE IS HACKABLE!

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <set>
#include <unordered_map>
#define int long long

const int N = 3e5 + 53, INF = 0x3f3f3f3f;

extern struct node _[];
int newNode();
struct node {
	int lc, rc, max, min, gcd;
	void build(int l, int r, int *a) {
		int mid = (l + r) / 2;
		if (l == r) return (void)(max = min = a[l], gcd = llabs(a[l] - a[l - 1]));
		_[lc = newNode()].build(l, mid, a), _[rc = newNode()].build(mid + 1, r, a);
		max = std::max(_[lc].max, _[rc].max), min = std::min(_[lc].min, _[rc].min);
		gcd = std::__gcd(_[lc].gcd, _[rc].gcd);
	}
	void set1(int x, int y, int l, int r) {
		int mid = (l + r) / 2;
		if (l == r) return void(max = min = y);
		(x <= mid ? _[lc].set1(x, y, l, mid) : _[rc].set1(x, y, mid + 1, r));
		max = std::max(_[lc].max, _[rc].max), min = std::min(_[lc].min, _[rc].min);
	}
	void set2(int x, int y, int l, int r) {
		int mid = (l + r) / 2;
		if (l == r) return void(gcd = y);
		(x <= mid ? _[lc].set2(x, y, l, mid) : _[rc].set2(x, y, mid + 1, r));
		gcd = std::__gcd(_[lc].gcd, _[rc].gcd);
	}
#define F_QUERY(x, y, v)                                                  \
	int query##x(int L, int R, int l, int r) {                            \
		if (L <= l && r <= R) return x;                                   \
		int mid = (l + r) / 2, ret = v;                                   \
		if (L <= mid) ret = std::y(ret, _[lc].query##x(L, R, l, mid));    \
		if (mid < R) ret = std::y(ret, _[rc].query##x(L, R, mid + 1, r)); \
		return ret;                                                       \
	}
	F_QUERY(max, max, -INF)
	F_QUERY(min, min, INF)
	F_QUERY(gcd, __gcd, 0)
} _[N << 4];
int newNode() {
	static int ptr = 1;
	return ptr++;
}
int rt, rt2, n, m, op, x, y, z, lans, a[N], pre[N];
std::unordered_map<int, std::set<int>> mp;
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a + i);
		if (!mp.count(a[i])) mp[a[i]].insert(0);
		pre[i] = *--mp[a[i]].end(), mp[a[i]].insert(i);
	}
	for (auto i : mp) i.second.insert(n + 1);
	_[rt = newNode()].build(0, n + 1, a);
	_[rt2 = newNode()].build(0, n + 1, pre);
	while (m--) {
		scanf("%lld%lld%lld", &op, &x, &y), x ^= lans, y ^= lans;
		if (op == 1) {
			// TODO: Check if there're some duplicate.

			// auto l = mp[a[x]].lower_bound(x), r = l;
			// l--, r++, _[rt3].set(*r, pre[*r] = *l, n + 1);
			// mp[a[x]].erase(x), mp[y].insert(x);
			_[rt].set1(x, a[x] = y, 0, n + 1);
			_[rt].set2(x, llabs(y - a[x - 1]), 0, n + 1);
			_[rt].set2(x + 1, llabs(a[x + 1] - y), 0, n + 1);
		} else {
			scanf("%lld", &z), z ^= lans;
			int u = _[rt].querymax(x, y, 0, n + 1) - _[rt].querymin(x, y, 0, n + 1);
			int v = _[rt].querygcd(x + 1, y, 0, n + 1);
			if (x == y || (u == z * (y - x) && v == z))
				lans++, puts("Yes");
			else
				puts("No");
		}
	}
}