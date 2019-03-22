#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>

using ll = long long;
const int N = 1e5 + 51, M = 6e6 + 66, INF = 0x3f3f3f3f, dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0}, head[y] = cnt;
}

int lv[N];
bool bfs(int s, int t) {
	memset(lv, 0, sizeof lv);
	std::queue<int> q;
	lv[s] = 1;
	for (q.push(s); !q.empty(); q.pop()) {
		int x = q.front();
		for (int i = head[x]; i; i = e[i].next) {
			int nx = e[i].to;
			if (e[i].w && !lv[nx]) lv[nx] = lv[x] + 1, q.push(nx);
		}
	}
	return lv[t];
}
int dfs(int s, int t, int f) {
	if (s == t || !f) return f;
	int r = 0;
	for (int i = head[s]; f && i; i = e[i].next) {
		int nx = e[i].to;
		if (!e[i].w || lv[nx] != lv[s] + 1) continue;
		int tmp = dfs(nx, t, std::min(f, e[i].w));
		e[i].w -= tmp, e[i ^ 1].w += tmp;
		f -= tmp, r += tmp;
	}
	if (f) lv[s] = -1;
	return r;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

int n, m;
ll id(int x, int y) { return (x - 1ll) * m + y; }

int x[N], y[N], z[N], col[N], k;
std::map<ll, int> mp;
int main() {
	scanf("%d%d%d", &m, &n, &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d%d%d", x + i, y + i, z + i);
		mp[id(x[i], y[i])] = i;
		col[i] = (int[]){0, 1, 3, 2}[x[i] % 4] + (!(x[i] % 4) || x[i] % 4 == 3 ? 1 : -1) * (y[i] % 2);
	}
	for (int i = 1; i <= k; i++) {
		if (col[i] == 1)
			addedge(1e5, i, z[i]);
		else if (col[i] == 3)
			addedge(i, 1e5 + 1, z[i]);
		else {
			for (int j = 0; j < 4; j++) {
				int nx = x[i] + dir[j][0], ny = y[i] + dir[j][1], idx = mp[id(nx, ny)];
				if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
				if (idx) {
					if (col[i] == 0 && col[idx] == 1) addedge(idx, i, INF);
					if (col[i] == 0 && col[idx] == 2) addedge(i, idx, std::min(z[i], z[idx]));
					if (col[i] == 2 && col[idx] == 3) addedge(i, idx, INF);
				}
			}
		}
	}
	printf("%d", dinic(1e5, 1e5 + 1));
}