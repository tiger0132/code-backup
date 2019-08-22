#include <bits/stdc++.h>

const int N = 100005;

struct edge {
	int to, next;
} e[N << 1];

int head[N], cnt;

void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]};
	head[x] = cnt;
}

int par[N], top[N], dep[N], t[N], anc[N][21];
long long s, w[N];
int n, l;

void prework() {
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j <= n; j++) {
			anc[j][i] = anc[anc[j][i - 1]][i - 1];
		}
	}
}

void dfs1(int x, int p) {
	dep[x] = dep[p] + 1;
	w[x] += w[p];
	top[x] = x;
	int len = l - 1;
	for (int i = 19; i >= 0; i--) {
		if (!anc[top[x]][i] || (1 << i) > len) continue;
		if (w[x] - w[par[anc[top[x]][i]]] <= s) {
			len -= 1 << i;
			top[x] = anc[top[x]][i];
		}
	}
	for (int i = head[x]; i; i = e[i].next) {
		dfs1(e[i].to, x);
	}
}

int dfs2(int x) {
	int ret = 0, mx = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		ret += dfs2(nx);
		if (t[nx] == nx) continue;
		if (!mx || dep[mx] > dep[t[nx]]) mx = t[nx];
	}
	if (mx)
		t[x] = mx;
	else
		t[x] = top[x], ret++;
	return ret;
}

int main() {
	scanf("%d%d%I64d", &n, &l, &s);
	for (int i = 1; i <= n; i++) {
		scanf("%I64d", w + i);
		if (w[i] > s) {
			puts("-1");
			return 0;
		}
	}
	for (int i = 2; i <= n; i++) {
		scanf("%d", par + i);
		anc[i][0] = par[i];
		addedge(par[i], i);
	}
	prework();
	dfs1(1, 0);
	dep[0] = 0x3f3f3f3f;
	printf("%d", dfs2(1));
}