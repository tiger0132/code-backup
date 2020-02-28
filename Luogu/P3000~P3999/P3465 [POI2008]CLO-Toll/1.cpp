#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e5 + 51, M = 2e5 + 52;
struct edge {
	int to, next;
} e[M << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int p[N], flg[N], pt[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }

int vis[N], par[N], last;
bool dfs(int x, int p) {
	x[par] = p, x[vis] = 1;
	int fl = 0;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			if (!nx[vis])
				fl |= dfs(nx, x);
			else {
				fl = 1;
				if (!last) last = x;
			}
		}
	return fl;
}

int n, m, x, y, u, v;
int main() {
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d", &x, &y);
		if ((u = f(x)) != (v = f(y))) {
			u[p] = v;
			v[pt] |= u[pt];
			v[flg] |= u[flg];
		} else if (!u[flg]) {
			u[flg] = 1;
			u[pt] = x;
		} else
			continue;
		addedge(x, y);
	}
	for (int i = 1; i <= n; i++)
		if (!f(i)[flg]) return puts("NIE"), 0;
	for (int i = 1; i <= n; i++)
		if (!f(i)[pt][vis]) {
			last = 0, dfs(f(i)[pt], 0);
			f(i)[pt][par] = last;
		}
	puts("TAK");
	for (int i = 1; i <= n; i++) printf("%d\n", i[par]);
}