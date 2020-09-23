#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define mid (l + r) / 2

const int N = 2e5 + 52, LN = 19;

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }

int n, v[N], fa[N][LN], dfn[N], rb[N], sz[N], idx;
std::vector<int> g[N];
void dfs(int x) {
	x[dfn] = ++idx, x[sz] = (x <= n);
	for (int nx : x[g]) dfs(nx), x[sz] += nx[sz];
	x[rb] = idx;
}
int get(int x, int k) {
	for (int i = LN - 1; i >= 0; i--)
		if (x[fa][i][v] <= k) x = x[fa][i];
	return x;
}
bool chk(int x, int y) { return x[dfn] <= y[dfn] && y[rb] <= x[rb]; }

int m, q, x, y, z, cnt;
int main() {
	scanf("%d%d", &n, &m), cnt = n, v[0] = 1e9;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		int fx = f(x), fy = f(y);
		if (fx != fy) {
			fx[p] = fy[p] = ++cnt;
			fx[fa][0] = fy[fa][0] = cnt;
			cnt[g].push_back(fx);
			cnt[g].push_back(fy);
			cnt[v] = i;
		}
	}
	for (int i = 1; i < LN; i++)
		for (int j = 1; j <= cnt; j++) j[fa][i] = j[fa][i - 1][fa][i - 1];
	dfs(cnt);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d%d", &x, &y, &z);
		int l = 1, r = m;
		while (l <= r) {
			int fx = get(x, mid), fy = get(y, mid);
			bool f = false;
			if (chk(fx, fy))
				f = (fx[sz] >= z);
			else if (chk(fy, fx))
				f = (fy[sz] >= z);
			else
				f = (fx[sz] + fy[sz] >= z);
			if (f)
				r = mid - 1;
			else
				l = mid + 1;
		}
		printf("%d\n", l);
	}
}