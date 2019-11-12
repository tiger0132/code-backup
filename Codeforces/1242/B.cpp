#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 1e5 + 51;
std::vector<int> g[N];
void addedge(int x, int y) { g[x].push_back(y), g[y].push_back(x); }

int v[N], pre[N], nxt[N];
void del(int x) {
	x[pre][nxt] = x[nxt];
	x[nxt][pre] = x[pre];
}

std::queue<int> q;
void bfs(int x) {
	for (q.push(x), del(x); !q.empty(); q.pop()) {
		int x = q.front();
		for (int nx : g[x]) nx[v] = 1;
		for (int i = 0 [nxt]; i; i = i[nxt])
			if (!i[v]) del(i), q.push(i);
		for (int nx : g[x]) nx[v] = 0;
	}
}

int n, m, x, y, ans;
int main() {
	for (scanf("%d%d", &n, &m); m--;) scanf("%d%d", &x, &y), addedge(x, y);
	for (int i = 0; i <= n; i++) i[pre] = i - 1, i[nxt] = i + 1;
	n[nxt] = 0;
	while (0 [nxt]) bfs(0 [nxt]), ans++;
	printf("%d", ans - 1);
}