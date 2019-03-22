#include <cstdio>
#include <utility>
#include <vector>

using ll = long long;
using pii = std::pair<int, int>;

const int N = 1e5 + 51, M = 1e8 + 81;

int rt[N], newNode(int, int, int, ll);
extern struct node _[];
struct node {
	int lc, rc, c;
	ll s;
	int insert(int x, int o, int l = 1, int r = M) {
		if (l == r) return newNode(0, 0, c + o, s + x * o);
		int mid = (l + r) >> 1;
		if (x <= mid) return newNode(_[lc].insert(x, o, l, mid), rc, c + o, s + x * o);
		return newNode(lc, _[rc].insert(x, o, mid + 1, r), c + o, s + x * o);
	}
	ll query(int k, int l = 1, int r = M) {
		if (l == r) return k * l;
		int mid = (l + r) >> 1;
		if (k > c) return s;
		if (k <= _[lc].c) return _[lc].query(k, l, mid);
		return _[lc].s + _[rc].query(k - _[lc].c, mid + 1, r);
	}
} _[N * 200];
int newNode(int lc, int rc, int c, ll s) {
	static int ptr = 1;
	_[ptr] = (node){lc, rc, c, s};
	return ptr++;
}

std::vector<pii> v[N];
int n, m, w, x, y, z;
ll lans = 1;

int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		v[x].push_back(pii(z, 1));
		v[y + 1].push_back(pii(z, -1));
	}
	for (int i = 1; i <= n; i++) {
		rt[i] = rt[i - 1];
		for (pii j : v[i]) rt[i] = _[rt[i]].insert(j.first, j.second);
	}
	while (n--) {
		scanf("%d%d%d%d", &w, &x, &y, &z);
		x = (x * lans + y) % z + 1;
		printf("%lld\n", lans = _[rt[w]].query(x));
	}
}