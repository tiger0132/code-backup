#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 2e5 + 52;

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = {y, x[head]}, x[head] = cnt, e[++cnt] = {x, y[head]}, y[head] = cnt; }

int p[N], d[N], sz[N], son[N], top[N], in[N], out[N], idx;
void dfs1(int x) {
	x[sz] = 1;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != x[p]) {
			nx[p] = x, nx[d] = x[d] + 1, dfs1(nx), x[sz] += nx[sz];
			if (nx[sz] > mx) x[son] = nx, mx = nx[sz];
		}
}
void dfs2(int x, int t) {
	x[top] = t, x[in] = ++idx;
	if (!x[son]) goto end;
	dfs2(x[son], t);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[p] && nx != x[son]) dfs2(nx, nx);
end:
	x[out] = ++idx;
}
int lca(int x, int y) {
	for (; x[top] != y[top]; x = x[top][p])
		if (x[top][d] < y[top][d]) std::swap(x, y);
	return x[d] < y[d] ? x : y;
}
bool cmp(int x, int y) {
	int u = x > 0 ? x[in] : (-x)[out];
	int v = y > 0 ? y[in] : (-y)[out];
	return u < v;
}

int n, k, x, y, a[N], ans[N], c[N];
std::stack<int> st;
bool f[N], g[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs1(1), dfs2(1, 1);
	for (scanf("%*d"); ~scanf("%d", &k);) {
		bool fl = false;
		for (int i = 1; i <= k; i++) scanf("%d", a + i), a[i][f] = a[i][g] = true;
		for (int i = 1; i <= k; i++)
			if (a[i][g] && a[i][p][g]) fl = true;
		std::sort(a + 1, a + k + 1, cmp);
		for (int i = 1, l; i < k; i++)
			if (!(l = lca(a[i], a[i + 1]))[f]) (a[++k] = l)[f] = true;
		if (!(1 [f])) a[++k] = 1;
		for (int i = 1; i <= k; i++) a[i + k] = -a[i];
		k *= 2, std::sort(a + 1, a + k + 1, cmp);
		for (int i = 1; i <= k; i++)
			if (a[i] > 0)
				st.push(a[i]);
			else {
				x = st.top(), st.pop();
				if (x == 1) {
					if (x[g]) x[ans] += x[c];
					if (!x[g] && x[c] > 1) x[ans]++;
					printf("%d\n", fl ? -1 : 1 [ans]);
				} else {
					if (x[g]) x[ans] += x[c], x[c] = 1;
					if (!x[g] && x[c] > 1) x[ans]++, x[c] = 0;
					y = st.top();
					y[c] += x[c], y[ans] += x[ans];
				}
				x[ans] = x[c] = 0, x[f] = x[g] = false;
			}
	}
}