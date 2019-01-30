#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>

const int N = 4e2 + 24, M = 2e3 + 32, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}

void ek(int s, int t, int &mflow, int &mcost) {
	static int dis[N], vis[N], flow[N], pre[N];
	std::queue<int> q;
	mflow = mcost = 0;
	while (1) {
		memset(dis, 0x3f, sizeof dis);
		q.push(s);
		flow[s] = 0x3f3f3f3f;
		dis[s] = 0;
		while (!q.empty()) {
			int pos = q.front();
			vis[pos] = 0;
			q.pop();
			for (int i = head[pos]; i; i = e[i].next) {
				int nx = e[i].to;
				if (e[i].w && dis[nx] > dis[pos] + e[i].c) {
					dis[nx] = dis[pos] + e[i].c;
					flow[nx] = std::min(flow[pos], e[i].w);
					pre[nx] = i;
					if (!vis[nx]) {
						q.push(nx);
						vis[nx] = 1;
					}
				}
			}
		}
		if (dis[t] == 0x3f3f3f3f) return;
		for (int i = pre[t]; i; i = pre[e[i ^ 1].to]) {
			e[i].w -= flow[t];
			e[i ^ 1].w += flow[t];
		}
		mflow += flow[t];
		mcost += dis[t] * flow[t];
	}
}

std::string x$, y$, r[N];
int n;
void dfs1(int x) {
	printf("%s ", r[x].c_str());
	for (int i = head[x]; i; i = e[i].next) {
		if (!e[i].w && (~i & 1)) {
			dfs1(e[i].to);
			e[i].w = 1;
			break;
		}
	}
}
void dfs2(int x) {
	for (int i = head[x]; i; i = e[i].next) {
		if (!e[i].w && (~i & 1)) {
			dfs2(e[i].to);
			e[i].w = 1;
			break;
		}
	}
	if (x != n) printf("%s ", r[x].c_str());
}

std::map<std::string, int> mp;
int m, x, y, f;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		std::cin >> r[i];
		mp[r[i]] = mp.size() + 1;
		addedge(i, i + 1, 1, 0);
	}
	while (m--) {
		std::cin >> x$ >> y$;
		x = mp[x$], y = mp[y$];
		if (x > y) std::swap(x, y);
		f |= x == 1 && y == n;
		addedge(n + x, y, 1, -1);
	}
	addedge(1, n + 1, 1, 0);
	addedge(n, 2 * n, 1, 0);
	ek(1, 2 * n, x, y);
	if (!x || (x == 1 && f)) return puts("No Solution!"), 0;
	if (f)
		return !printf("2\n%s %s %s", r[1].c_str(), r[n].c_str(), r[1].c_str());
	printf("%d\n", x);
	dfs1(1);
	dfs2(1);
}