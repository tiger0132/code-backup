#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 51, M = 3e5 + 53;
struct edge {
	int to, next;
} e[M << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int p[N], cc;
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void u(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y, cc--;
}

int n, m, x[M], y[M], col[N], a[N], b[N], c[N], v[N], c1[4], c2[4][4];
std::queue<int> qq;
int main() {
	scanf("%d%d", &n, &m), cc = n;
	for (int i = 1; i <= m; i++)
		scanf("%d%d", x + i, y + i), addedge(x[i], y[i]), u(x[i], y[i]);
	if (cc > 1) return puts("-1"), 0;
	col[x[1]] = 1, col[y[1]] = 2, x[1][v] = y[1][v] = 1;
	for (int i = x[1][head]; i; i = e[i].next) e[i].to[a] = 1;
	for (int i = y[1][head]; i; i = e[i].next) {
		int nx = e[i].to;
		nx[b] = 1;
		if (nx[a]) /* printf("[%d]\n", nx),*/
			qq.push(nx), nx[v] = 1;
	}
	for (int x; !qq.empty(); qq.pop()) {
		x = qq.front();
		// printf("%d\n", x);
		int *p, *q, *w;
		if (!x[a]) w = a, p = b, q = c, x[col] = 1;
		if (!x[b]) p = a, w = b, q = c, x[col] = 2;
		if (!x[c]) p = a, q = b, w = c, x[col] = 3;
		for (int i = x[head], nx; i; i = e[i].next) {
			(nx = e[i].to)[w] = 1;
			if (nx[v]) continue;
			// printf("%d -> %d\n", x, nx);
			nx[v] = 1;
			if (nx[p] && nx[q]) return puts("-1"), 0;
			qq.push(nx);
		}
	}
	for (int i = 1; i <= n; i++) i[col][c1]++;
	for (int i = 1; i <= m; i++) {
		c2[x[i][col]][y[i][col]]++;
		c2[y[i][col]][x[i][col]]++;
	}
	if (c2[1][1] || c2[2][2] || c2[3][3]) return puts("-1"), 0;
	if (c2[1][2] != c1[1] * c1[2]) return puts("-1"), 0;
	if (c2[1][3] != c1[1] * c1[3]) return puts("-1"), 0;
	if (c2[2][3] != c1[2] * c1[3]) return puts("-1"), 0;
	for (int i = 1; i <= n; i++)
		if (!i[col]) return puts("-1"), 0;
	for (int i = 1; i <= n; i++) printf("%d ", i[col]);
}