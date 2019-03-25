#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 2e4 + 42;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}, head[y] = cnt;
}

int dep[N], dis[N], val[N], par[N][30];
void dfs(int x, int p) {
	for (int i = 1; i < 30; i++) {
		par[x][i] = par[par[x][i - 1]][i - 1];
	}
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dis[nx] = dis[x] + e[i].w;
		dep[nx] = dep[x] + 1;
		val[nx] = e[i].w;
		par[nx][0] = x;
		dfs(nx, x);
	}
}
int kth(int x, int k) {
	for (int i = 29; i >= 0; i--)
		if ((1 << i) & k) x = par[x][i];
	return x;
}
int lca(int x, int y) {
	int dx = dep[x], dy = dep[y];
	if (dx > dy) std::swap(x, y), std::swap(dx, dy);
	y = kth(y, dy - dx);
	if (x == y) return x;
	for (int i = 29; i >= 0; i--) {
		if (par[x][i] != par[y][i]) {
			x = par[x][i];
			y = par[y][i];
		}
	}
	return par[x][0];
}

int _, n, x, y, z;
char op[N];
#define memset0(x) memset(x, 0, sizeof x)
int main() {
	for (scanf("%d", &_); _--;) {
		memset0(dep), memset0(dis), memset0(val), memset0(par), memset0(head), cnt = 0;
		scanf("%d", &n);
		for (int i = 1; i < n; i++) {
			scanf("%d%d%d", &x, &y, &z);
			addedge(x, y, z);
		}
		dfs(1, 0);
		while (scanf("%s", op), op[1] != 'O') {
			scanf("%d%d", &x, &y);
			int l = lca(x, y);
			if (op[1] == 'I') {
				printf("%d\n", dis[x] + dis[y] - 2 * dis[l]);
			} else {
				scanf("%d", &z);
				if (z <= dep[x] - dep[l] + 1) 
					printf("%d\n", kth(x, z - 1));
				else {
					z -= dep[x] - dep[l] + 1;
					printf("%d\n", kth(y, dep[y] - dep[l] - z));
				}
			}
		}
	}
}