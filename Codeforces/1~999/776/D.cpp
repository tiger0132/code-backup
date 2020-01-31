#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e5 + 52;

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void l(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}

int n, m, x, y, r[N][2], c[N], op[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", i + op);
	for (int i = 1; i <= m; i++)
		for (scanf("%d", &x); x--; r[y][c[y]++] = i) scanf("%d", &y);
	for (int i = 1; i <= n; i++) {
		int u = r[i][0], v = r[i][1];
		l(u, v + m * !i[op]);
		l(u + m, v + m * i[op]);
	}
	for (int i = 1; i <= m; i++)
		if (f(i) == f(i + m)) return puts("NO"), 0;
	puts("YES");
}