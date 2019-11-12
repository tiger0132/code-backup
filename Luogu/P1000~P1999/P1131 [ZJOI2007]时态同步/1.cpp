#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 5e5 + 55;

struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z}, y[head] = cnt;
}

int mx[N];
ll ans;
void dfs(int x, int p) {
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x), x[mx] = std::max(x[mx], nx[mx] + e[i].w);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) ans += x[mx] - nx[mx] - e[i].w;
}

int n, s, x, y, z;
int main() {
	scanf("%d%d", &n, &s);
	for (int i = 1; i < n; i++) scanf("%d%d%d", &x, &y, &z), addedge(x, y, z);
	dfs(s, 0);
	printf("%lld", ans);
}