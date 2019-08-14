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
int ch[N][2], a[N], l[N], r[N], mid[N], s[N], inv[N];
void up(int x) { x[s] = x[a] ? (x[r] + 1)[inv] - x[l][inv] : x[Lc][a] + x[Rc][a]; }
void build(int x, d L, d R) {
	x[l] = L, x[r] = R, x[mid] = (L + R) / 2;
	if (L == R) build(x[Lc], L, x[mid]), build(x[Rc], x[mid], R);
}
void add(int x, d L, d R, int v) {
	if (L <= x[l] && x[r] <= R) return (a[x] += v), up(x);
	if (L <= x[mid]) add(x[Lc], L, R, v);
	if (x[mid] < R) add(x[Rc], L, R, v);
	up(x);
}

struct line {
	int y, x1, x2, v;
} rec[N];

int n, x1, y1, x2, y2, m;
long long ans;
signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		rec[2 * i - 1] = (line){y1, x1, x2, 1};
		rec[2 * i] = (line){y2, x1, x2, 1};
		inv[2 * i - 1] = x1, inv[2 * i] = x2;
	}
	std::sort(inv + 1, inv + 2 * n + 1);
	m = std::unique(inv + 1, inv + 2 * n) - inv - 1;
}