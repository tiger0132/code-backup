#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>

const int N = 1e5 + 51;

__gnu_pbds::priority_queue<int> g[N], q;

int n, m, x, y, vis[N];
void dfs(int x) {
	q.join(g[x]);
	vis[x] = 1;
	printf("%d ", x);
	while (!q.empty()) {
		int nx = -q.top();
		q.pop();
		if (vis[nx]) continue;
		dfs(nx);
	}
}

int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d", &x, &y);
		g[x].push(-y);
		g[y].push(-x);
	}
	dfs(1);
}