#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
const int N = 2e5 + 52, M = 1.5e7 + 751;
struct edge {
	int to, next;
} e[M];
int head[N], cnt, v[62][N];
long long a[N];
int n, p[N], ans = 1e9;
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void ad(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}
int dfs(int s, int t, int f, int d) {
	std::queue<> q;

	if (s == t) return 1;
	for (int i = s[head], x; i; i = e[i].next)
		if (e[i].to != f && (x = dfs(e[i].to, t, s, d + 1))) return x + 1;
	return 0;
}
int i, j, x;
std::multiset<int> s;
int main() {
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%lld", a + i);
	}
	for (j = 0; j < 62; j++)
		for (i = 0; i < n; i++)
			if ((a[i] >> j) & 1) {
				v[j][i] = 1;
				if (f(j + n + 1) != f(i + 1))
					ad(i + 1, j + n + 1);
				else {
					x = dfs(i + 1, j + n + 1, 0, 0) / 2;
					if (x == 2) continue;
					ans = ans < x ? ans : x;
				}
			}
	printf("%d\n", ans == 1e9 ? -1 : ans);
}