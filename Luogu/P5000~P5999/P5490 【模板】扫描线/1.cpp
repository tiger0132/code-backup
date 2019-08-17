// 不好了！我们指针军团有个叫 tiger0132 的菜鸡倒戈了！

#include <algorithm>
#include <cstdio>
#include <cstring>

typedef double d;
const int N = (1e5 + 51) * 4;

#define Lc ch][0
#define Rc ch][1
// a: 永久化的加法标记
// s: 区间线段长总和
int ch[N][2], a[N], l[N], r[N], mid[N], s[N], inv[N], ncnt;
void up(int x) { x[s] = (x[a] ? (x[r] + 1)[inv] - x[l][inv] : x[Lc][s] + x[Rc][s]); }
void build(int x, d L, d R) {
	x[l] = L, x[r] = R, x[mid] = (L + R) / 2;
	if (L < R) build(x[Lc] = ++ncnt, L, x[mid]), build(x[Rc] = ++ncnt, x[mid] + 1, R);
}
void add(int x, d L, d R, int v) {
	if (L <= x[l] && x[r] <= R) return (a[x] += v), up(x);
	if (L <= x[mid]) add(x[Lc], L, R, v);
	if (x[mid] < R) add(x[Rc], L, R, v);
	up(x);
}

struct line {
	int y, x1, x2, v;
	bool operator<(const line& r) const { return y < r.y; }
} rec[N];

int n, x1[N], y1[N], x2[N], y2[N], m, last;
long long ans;
signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d%d", x1 + i, y1 + i, x2 + i, y2 + i);
		inv[2 * i - 1] = x1[i], inv[2 * i] = x2[i];
	}
	std::sort(inv + 1, inv + 2 * n + 1);
	m = std::unique(inv + 1, inv + 2 * n + 1) - inv - 1;
	for (int i = 1; i <= n; i++) {
		x1[i] = std::lower_bound(inv + 1, inv + m + 1, x1[i]) - inv;
		x2[i] = std::lower_bound(inv + 1, inv + m + 1, x2[i]) - inv;
		if (y1[i] > y2[i]) std::swap(y1[i], y2[i]);
		rec[2 * i - 1] = (line){y1[i], x1[i], x2[i], 1};
		rec[2 * i] = (line){y2[i], x1[i], x2[i], -1};
	}
	std::sort(rec + 1, rec + 2 * n + 1);
	build(++ncnt, 1, m);
	last = rec[1].y;
	for (int i = 1; i <= 2 * n; i++) {
		ans += 1ll * (rec[i].y - last) * 1 [s];
		add(1, rec[i].x1, rec[i].x2 - 1, rec[i].v);
		last = rec[i].y;
		// prt(1);
	}
	printf("%lld", ans);
}