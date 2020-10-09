#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 1e6 + 61;

std::vector<int> g[N];
int dep[N], son[N];
void dfs1(int x, int p) {
	for (int nx : x[g])
		if (nx != p) {
			dfs1(nx, x);
			if (nx[dep] > x[son][dep]) x[son] = nx;
		}
	x[dep] = x[son][dep] + 1;
}

int buf[N], *pt = buf;
int *f[N], ans[N];
void dfs2(int x, int p) {
	f[x][0] = 1;
	if (x[son]) {
		f[x[son]] = f[x] + 1;
		dfs2(x[son], x);
		x[ans] = x[son][ans] + 1;
	}
	for (int nx : x[g])
		if (nx != p && nx != x[son]) {
			f[nx] = pt, pt += nx[dep];
			dfs2(nx, x);
			for (int i = 1; i <= nx[dep]; i++) {
				f[x][i] += f[nx][i - 1];
				if (f[x][i] > f[x][x[ans]] || (f[x][i] == f[x][x[ans]] && i < x[ans]))
					x[ans] = i;
			}
		}
	if (f[x][x[ans]] == 1) x[ans] = 0;
}

int n;
int main() {
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		x[g].push_back(y);
		y[g].push_back(x);
	}
	dfs1(1, 1);
	f[1] = pt, pt += 1 [dep];
	dfs2(1, 1);
	for (int i = 1; i <= n; i++) printf("%d\n", i[ans]);
}