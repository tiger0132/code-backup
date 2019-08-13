#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 5e5 + 55;

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = {y, x[head]}, x[head] = cnt;
	e[++cnt] = {x, y[head]}, y[head] = cnt;
}

struct qr {
	int x;
	bool *ans;
};
int sz[N], dep[N], son[N], par[N], c[N];
std::vector<qr> q[N];
char s[N];
void dfs1(int x, int p, int d) {
	x[sz] = 1, x[dep] = d, x[par] = p;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs1(nx, x, d + 1), x[sz] += nx[sz];
			if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
		}
}

bool vis[N];
void dfs3(int x) {  // 暴力统计
	x[dep][c] ^= 1 << (s[x] - 'a');
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && !nx[vis]) dfs3(nx);
}
void dfs2(int x, bool f) {  // f 代表重儿子
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) dfs2(nx, false);
	if (x[son]) dfs2(x[son], true), x[son][vis] = true;  // 直接继承重儿子的答案
	dfs3(x);											 // 暴力统计轻儿子的答案
	x[son][vis] = false;								 // 清除重儿子的 vis 标记
	for (auto i : q[x]) *(i.ans) = !(i.x[c] & (i.x[c] - 1));
	if (!f) dfs3(x);  // 如果自己是轻儿子，消除自己的影响
}

int n, m, x, y;
bool ans[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; i++) scanf("%d", &x), addedge(i, x);
	scanf("%s", s + 1);
	for (int i = 1; i <= m; i++) scanf("%d%d", &x, &y), x[q].push_back({y, ans + i});
	dfs1(1, 0, 1), dfs2(1, true);
	for (int i = 1; i <= m; i++) puts(ans[i] ? "Yes" : "No");
}