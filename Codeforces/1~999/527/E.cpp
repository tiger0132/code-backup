#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 4e5 + 54;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt = 1;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int vis[N], f;
void dfs(int x) {
	for (int &i = x[head], t; i; i = e[i].next)
		if (!(i / 2)[vis]) {
			(i / 2)[vis] = 1, dfs(e[t = i].to);
			if (f)
				printf("%d %d\n", e[t].to, x);
			else
				printf("%d %d\n", x, e[t].to);
			f ^= 1;
		}
}

int n, m, x, y, d[N];
int main() {
	for (scanf("%d%d", &n, &m); ~scanf("%d%d", &x, &y);) x[d]++, y[d]++, addedge(x, y);
	for (int i = 1, l = 0; i <= n; i++)
		if (i[d] & 1) l = l ? addedge(l, i), m++, 0 : i;
	printf("%d\n", m + (m & 1));
	dfs(x);
	if (m & 1) printf("%d %d\n", x, x);
}