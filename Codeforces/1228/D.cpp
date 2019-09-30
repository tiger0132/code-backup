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

int n, m, x[M], y[M], a[N][4], col[N], c[4], c2[4][4];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", x + i, y + i), addedge(x[i], y[i]);
	col[x[1]] = 1, col[y[1]] = 2;
	for (int i = x[1][head]; i; i = e[i].next) e[i].to[a][1] = 1;
	for (int i = y[1][head]; i; i = e[i].next) {
		e[i].to[a][2] = 1;
		if (e[i].to[a][1]) e[i].to[col] = 3;
	}
	for (int i = 1; i <= m; i++) {
		if (x[i][col] == 3) y[i][a][3] = 1;
		if (y[i][col] == 3) x[i][a][3] = 1;
	}
	for (int i = 1; i <= n; i++) {
		if ((i[a][1] + i[a][2] + i[a][3]) != 2) return puts("-1"), 0;
		if (i[col] == 1 && i[a][1]) return puts("-1"), 0;
		if (i[col] == 2 && i[a][2]) return puts("-1"), 0;
		if (i[col] == 3 && i[a][3]) return puts("-1"), 0;
		if (!i[a][1]) i[col] = 1;
		if (!i[a][2]) i[col] = 2;
		if (!i[a][3]) i[col] = 3;
	}
	for (int i = 1; i <= n; i++) i[col][c]++;
	for (int i = 1; i <= m; i++) {
		c2[x[i][col]][y[i][col]]++;
		c2[y[i][col]][x[i][col]]++;
	}
	if (c2[1][1] || c2[2][2] || c2[3][3]) return puts("-1"), 0;
	if (c2[1][2] != c[1] * c[2]) return puts("-1"), 0;
	if (c2[1][3] != c[1] * c[3]) return puts("-1"), 0;
	if (c2[2][3] != c[2] * c[3]) return puts("-1"), 0;
	for (int i = 1; i <= n; i++) printf("%d ", i[col]);
}