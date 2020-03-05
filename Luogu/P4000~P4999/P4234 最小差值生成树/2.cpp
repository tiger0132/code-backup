#include <algorithm>
#include <cstdio>
#include <cstring>
#define L ch][0
#define R ch][1

const int N = 3e5 + 53;
struct edge {
	int x, y, z;
	bool operator<(const edge& rhs) const { return z < rhs.z; }
} e[N];

// clang-format off
int n, ch[N][2], p[N], v[N], r[N], mn[N];
void up(int x) {
	x[mn] = x;
	if (x[L][mn] > n && (x[mn] <= n || x[L][mn] < x[mn])) x[mn] = x[L][mn];
	if (x[R][mn] > n && (x[mn] <= n || x[R][mn] < x[mn])) x[mn] = x[R][mn];
}
bool c(int x) { return x[p][R] == x; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rv(int x) { std::swap(x[L], x[R]), x[r] ^= 1; }
void pd(int x) { x[r] && (rv(x[L]), rv(x[R]), x[r] = 0); }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = ch[x][!k];
	(nr(y) && (ch[z][c(y)] = x)), p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void pa(int x) { if (nr(x)) pa(x[p]); pd(x); }
void sp(int x) { pa(x); for (int y = x[p]; nr(x); rt(x), y = x[p]) if (nr(y)) rt(c(x) == c(y) ? y : x); }
void ac(int x) { for (int y = 0; x; x = (y = x)[p]) sp(x), x[R] = y, up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void lnk(int x, int y) { mr(x), x[p] = y; }
void cut(int x, int y) { spl(x, y), x[p] = y[L] = 0, up(y); }

int _p[N];
int f(int x) { return x[_p] ? x[_p] = f(x[_p]) : x; }
void mg(int x, int y) { if ((x = f(x)) != (y = f(y))) x[_p] = y; }
// clang-format on

int m, ans = 1e9, cnt, vis[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].z);
	std::sort(e + 1, e + m + 1);
	for (int i = 1, j = 1, k; i <= m; i++) {
		int x = e[i].x, y = e[i].y, z = e[i].y;
		if (x == y) continue;
		if (f(x) != f(y))
			cnt++, (n + i)[v] = z, mg(x, y);
		else {
			spl(x, y), k = y[mn];
			cut(e[k - n].x, k), cut(e[k - n].y, k);
			for (vis[k - n] = 0; !vis[j];) j++;
		}
		i[vis] = 1, lnk(x, n + i), lnk(y, n + i);
		if (cnt == n - 1) ans = std::min(ans, e[i].z - e[j].z);
	}
	printf("%d", ans);
}