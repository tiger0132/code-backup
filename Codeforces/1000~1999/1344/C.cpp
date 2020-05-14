#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>

const int N = 2e5 + 52;

std::vector<int> g[N][2];
int col[N][2];
void dfs(int x, int id, int c) {
	x[col][id] = c;
	for (int nx : x[g][id])
		if (!nx[col][id]) dfs(nx, id, c);
}

int n, m, x, y, ans, d[N], cnt;
std::queue<int> q;
char out[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		x[g][0].push_back(y);
		y[g][1].push_back(x);
		y[d]++;
	}
	for (int i = 1; i <= n; i++)
		if (!i[d]) q.push(i);
	for (; !q.empty(); q.pop(), cnt++) {
		int x = q.front();
		for (int nx : x[g][0])
			if (!--nx[d]) q.push(nx);
	}
	if (cnt != n) return puts("-1"), 0;
	for (int i = 1; i <= n; i++) {
		if (!i[col][0] && !i[col][1])
			i[out] = 'A', ans++;
		else
			i[out] = 'E';
		dfs(i, 0, 1), dfs(i, 1, 1);
	}
	printf("%d\n%s", ans, out + 1);
}