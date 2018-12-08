#include <vector>
#include <cstdio>

const int N = 5e5+55;

struct edge { int to, next; } e[N<<1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}; head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}; head[y] = cnt;
}

struct node { int x, *ans; };
std::vector<node> q[N];

int sz[N], dep[N], son[N], par[N];
void dfs1(int x, int p, int d) {
	sz[x] = 1; dep[x] = d; par[x] = p;
	int mx = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs1(nx, x, d+1);
		sz[x] += sz[nx];
		if (sz[nx] > mx) {
			mx = sz[nx];
			son[x] = nx;
		}
	}
}
int cntx[N];
bool vis[N];
char rec[N];
void dfs3(int x) {
	cntx[dep[x]] ^= 1 << (rec[x] - 'a');
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x] || vis[nx]) continue;
		dfs3(nx);
	}
}
void dfs2(int x, int f) {
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x] || nx == son[x]) continue;
		dfs2(nx, 0);
	}
	if (son[x]) dfs2(son[x], 1), vis[son[x]] = 1;
	dfs3(x);
	vis[son[x]] = 0;
	for (int i = 0; i < q[x].size(); i++) {
		*q[x][i].ans = !(cntx[q[x][i].x] & (cntx[q[x][i].x]-1));
	}
	if (!f) dfs3(x);
}

int n, m, x, y;
int ans[N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; i++) {
		scanf("%d", &x);
		addedge(i, x);
	}
	scanf("%s", rec+1);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		q[x].push_back((node){y, ans+i});
	}
	dfs1(1, -1, 1);
	dfs2(1, 0);
	for (int i = 1; i <= m; i++) {
		puts(ans[i] ? "Yes" : "No");
	}
}