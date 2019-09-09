#include <algorithm>
#include <cstdio>
#include <cstring>

// clang-format off
#define L ch][0
#define R ch][1
const int N = 4e5 + 54;
int ch[N][2], l[N], r[N], mid[N], mn[N], c;
void up(int x) { x[mn] = std::min(x[L][mn], x[R][mn]); }
void build(int x, int ql, int qr) {
	x[l] = ql, x[r] = qr, x[mid] = (ql + qr) / 2;
	if (ql == qr) return void(x[mn] = 0);
	build(x[L] = ++c, ql, x[mid]), build(x[R] = ++c, x[mid] + 1, qr), up(x);
}
void upd(int x, int qi, int v) {
	if (x[l] == x[r]) return void(x[mn] = v);
	upd(qi <= x[mid] ? x[L] : x[R], qi, v), up(x);
}
int qry(int x, int ql, int qr) {
	if (ql <= x[l] && x[r] <= qr) return x[mn];
	int ret = 1e9;
	if (ql <= x[mid]) ret = std::min(ret, qry(x[L], ql, qr));
	if (x[mid] < qr) ret = std::min(ret, qry(x[R], ql, qr));
	return ret;
}
// clang-format on

struct point {
	int pos[2];
} a[N];
struct rect {
	int pos[2][2], *ans;
} b[N];

int n, m, k, q, ans[N];
void calc(int x, int y) {
	std::sort(a + 1, a + k + 1,
			  [x, y](const point& u, const point& v) { return u.pos[x] < v.pos[x]; });
	std::sort(b + 1, b + q + 1,
			  [x, y](const rect& u, const rect& v) { return u.pos[x][1] < v.pos[x][1]; });
	int p1 = 1, p2 = 1;
	for (; p1 <= q; p1++) {
		for (; a[p2].pos[x] <= b[p1].pos[x][1] && p2 <= k; p2++)
			upd(1, a[p2].pos[y], a[p2].pos[x]);
		int tt = qry(1, b[p1].pos[y][0], b[p1].pos[y][1]);
		if (tt >= b[p1].pos[x][0]) *b[p1].ans = 1;
	}
}
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &q);
	for (int i = 1; i <= k; i++) scanf("%d%d", &a[i].pos[0], &a[i].pos[1]);
	for (int i = 1; i <= q; i++)
		scanf("%d%d%d%d", &b[i].pos[0][0], &b[i].pos[1][0], &b[i].pos[0][1],
			  &b[i].pos[1][1]),
			b[i].ans = ans + i;
	build(c = 1, 1, m);
	calc(0, 1);
	build(c = 1, 1, n);
	calc(1, 0);
	for (int i = 1; i <= q; i++) puts(ans[i] ? "YES" : "NO");
}