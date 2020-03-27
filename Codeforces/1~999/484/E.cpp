#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

typedef std::pair<int, int> pii;
const int N = 4e6 + 64;
struct rec {
	int sz, la, ra, ans;
	rec operator+(const rec& rhs) const {
		return {sz + rhs.sz,				  //
				la == sz ? la + rhs.la : la,  //
				rhs.ra == rhs.sz ? ra + rhs.ra : rhs.ra,
				std::max({ans, rhs.ans, ra + rhs.la})};
	}
} tag[N];
int ch[N][2], nc = 1;
int cl(int x) { return (++nc)[L] = x[L], nc[R] = x[R], nc[tag] = x[tag], nc; }
void up(int x) { x[tag] = x[L][tag] + x[R][tag]; }
void build(int x, int l, int r) {
	if (l == r) return x[tag] = {1, 1, 1, 1}, void();
	build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r), up(x);
}
void ins(int x, int l, int r, int y) {
	if (l == r) return x[tag] = {1, 0, 0, 0}, void();
	if (y <= mid) return ins(x[L] = cl(x[L]), l, mid, y), up(x);
	ins(x[R] = cl(x[R]), mid + 1, r, y), up(x);
}
rec qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[tag];
	if (qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return qry(x[L], l, mid, ql, qr) + qry(x[R], mid + 1, r, ql, qr);
}

int n, m, l, r, x, y, z, rt[N];
std::vector<int> v[N];
pii a[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &x), a[i] = pii(x, i);
	std::sort(a + 1, a + n + 1);
	build(rt[0] = 1, 1, n);
	for (int i = 1; i <= n; i++) ins(rt[i] = cl(rt[i - 1]), 1, n, a[i].second);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		for (l = 1, r = n; l <= r;) {
			if (qry(rt[mid], 1, n, x, y).ans < z)
				r = mid - 1;
			else
				l = mid + 1;
		}
		printf("%d\n", a[l].first);
	}
}