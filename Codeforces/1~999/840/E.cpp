#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e5 + 51, K = 256;

struct Trie {
	int ch[N][2], nc;
	int _() { return ++nc, ch[nc][0] = ch[nc][1] = 0, nc; }
	void clear() { nc = ch[0][0] = ch[0][1] = 0; }
	void ins(int x) {
		int p = 0;
		for (int i = 15; i >= 0; i--) {
			int& nx = ch[p][(x >> i) & 1];
			if (!nx) nx = _();
			p = nx;
		}
	}
	int qry(int x) {
		int p = 0, ans = 0;
		for (int i = 15; i >= 0; i--) {
			int nx = !((x >> i) & i);
			if (ch[p][nx])
				ans |= 1 << i, p = ch[p][nx];
			else
				p = ch[p][!nx];
		}
		return ans;
	}
} trie;

int par[N], dep[N], top[N], a[N], f[N][K];
std::vector<int> g[N];
void dfs(int x, int p, int d) {
	x[par] = p, x[dep] = d;
	// trie.clear();
	int& y = x[top] = x;
	for (int i = 0; i < K; i++, y = y[par]) {
		// trie.ins(a[y] ^ i);
		for (int j = 0; j < K; j++) f[x][j] = std::max(f[x][j], a[y] ^ i ^ (j << 8));
	}
	// for (int i = 0; i < K; i++) f[x][i] = trie.qry(i << 8);
	for (int nx : x[g])
		if (nx != p) dfs(nx, x, d + 1);
}

int n, q, x, y;
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		x[g].push_back(y);
		y[g].push_back(x);
	}
	dfs(1, 0, 0);
	while (q--) {
		int ans = 0, tmp = 0;
		scanf("%d%d", &x, &y);
		for (; y[dep] - x[dep] >= K; y = y[top], tmp++) ans = std::max(ans, f[y][tmp]);
		for (tmp <<= 8; y != x[par]; y = y[par], tmp++) ans = std::max(ans, y[a] ^ tmp);
		printf("%d\n", ans);
	}
}