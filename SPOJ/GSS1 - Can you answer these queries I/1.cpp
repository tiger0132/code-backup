#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
const int N = 2e5 + 52, INF = 0x3f3f3f3f;
struct node {
	int s, ls, rs, gss;
	void operator=(int x) { s = ls = rs = gss = x; }
	node operator+(const node& r) const {
		return {s + r.s, std::max(ls, s + r.ls), std::max(rs + r.s, r.rs),
				std::max({gss, r.gss, rs + r.ls})};
	}
	void operator+=(const node& r) { *this = *this + r; };
} tag[N];
int ch[N][2], l[N], r[N], mid[N], c;
void up(int x) { x[tag] = x[L][tag] + x[R][tag]; }
void build(int x, int ql, int qr, int* a) {
	x[l] = ql, x[r] = qr, x[mid] = (ql + qr) / 2;
	if (ql == qr) return void(x[tag] = a[ql]);
	build(x[L] = ++c, ql, x[mid], a), build(x[R] = ++c, x[mid] + 1, qr, a), up(x);
}
node qry(int x, int ql, int qr) {
	if (ql <= x[l] && x[r] <= qr) return x[tag];
	node ret{0, -INF, -INF, -INF};
	if (ql <= x[mid]) ret += qry(x[L], ql, qr);
	if (x[mid] < qr) ret += qry(x[R], ql, qr);
	return ret;
}

int n, a[N], m, x, y;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	build(c = 1, 1, n, a);
	for (scanf("%d", &m); m--;) {
		scanf("%d%d", &x, &y);
		printf("%d\n", qry(1, x, y).gss);
	}
}