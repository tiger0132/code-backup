#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#define x first
#define y second

typedef std::pair<int, int> pii;
const int N = 1e5 + 51, M = 17;
const double eps = 1e-6;

int n, m, h[N], m1[N], m2[N], a[N][M], b[N][M], f[N][M];
std::set<pii> s;
bool cmp(int i, int x, int y) {
	return abs(i[h] - x[h]) < abs(i[h] - y[h]) ||
		   (abs(i[h] - x[h]) == abs(i[h] - y[h]) && x[h] < y[h]);
}
void chk(int i, int x) {
	if (!i[m1])
		i[m1] = x;
	else if (cmp(i, x, i[m1]))
		i[m2] = i[m1], i[m1] = x;
	else if (!i[m2] || cmp(i, x, i[m2]))
		i[m2] = x;
}
void calc(int i, int x, int &d1, int &d2) {
	d1 = d2 = 0;
	for (int j = M - 1; j >= 0; j--)
		if (i[f][j] && d1 + d2 + i[a][j] + i[b][j] <= x)
			d1 += i[a][j], d2 += i[b][j], i = i[f][j];
	if (i[m2] && d1 + d2 + i[a][0] <= x) d1 += i[a][0];
}

int x, y, ans, d1, d2;
double mx, t;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", h + i), s.insert(pii(i[h], i));
	for (int i = 1; i <= n; i++) {
		std::set<pii>::iterator it = s.find(pii(i[h], i)),
								tmp;  // 傻逼 C++ 标准，不准我写 auto
		if ((tmp = it) != s.begin() && (chk(i, (--tmp)->y), tmp != s.begin()))
			chk(i, (--tmp)->y);
		if ((tmp = ++it) != s.end() && (chk(i, tmp->y), ++tmp != s.end())) chk(i, tmp->y);
		s.erase(pii(i[h], i));
	}
	for (int i = 1; i <= n; i++)
		i[f][0] = i[m2][m1], i[a][0] = abs(i[h] - i[m2][h]),
		i[b][0] = abs(i[m2][h] - i[m2][m1][h]);
	for (int j = 1; j < M; j++)
		for (int i = 1; i <= n; i++)
			i[f][j] = i[f][j - 1][f][j - 1],
			i[a][j] = i[a][j - 1] + i[f][j - 1][a][j - 1],
			i[b][j] = i[b][j - 1] + i[f][j - 1][b][j - 1];
	scanf("%d%d", &x, &m), *h = -2e9, mx = 1e9;
	for (int i = 1; i <= n; i++) {
		calc(i, x, d1, d2);
		t = d2 ? 1. * d1 / d2 : 2e9;
		if (t < mx - eps || (fabs(t - mx) < eps && i[h] > ans[h])) mx = t, ans = i;
	}
	for (printf("%d\n", ans); m--;)
		scanf("%d%d", &x, &y), calc(x, y, d1, d2), printf("%d %d\n", d1, d2);
}