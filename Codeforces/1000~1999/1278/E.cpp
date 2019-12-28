#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e6 + 61;
struct edge {
	int to, next;
} e[N << 1];
int head[N], d[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt, x[d]++;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt, y[d]++;
}

int pre[N], nxt[N], nc;
void ins_after(int x, int v) { v[nxt] = x[nxt], v[nxt][pre] = v, x[nxt] = v, v[pre] = x; }
void ins_before(int x, int v) {
	v[nxt] = x, v[pre] = x[pre], x[pre] = v, v[pre][nxt] = v;
}

int flag[N];
void dfs(int x, int p, int r) {
	for (int i = x[head], nx, nl, nr; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			ins_before(r, nl = ++nc), nl[flag] = nx * 2 - 1;
			ins_after(r, nr = ++nc), nr[flag] = nx * 2;
			dfs(nx, x, nr);
		}
}

int n, x, y, ans[N];
int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	nc = 2, 1 [nxt] = 2, 2 [pre] = 1, 1 [flag] = 1, 2 [flag] = 2;
	dfs(1, 0, 2);
	for (int i = 1, j = 1; i; i = i[nxt]) i[flag][ans] = j++;
	for (int i = 1; i <= 2 * n; i++) printf("%d%c", ans[i], " \n"[i % 2 == 0]);
}