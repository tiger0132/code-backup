#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 51;

struct edge {
	int to, next, w;
} e[N << 3];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z};
	head[x] = cnt;
}

long long n, ans, dis[N];
int x, y, z, vis[N];
std::queue<int> q;
int main() {
	scanf("%lld%d%d%d", &n, &z, &x, &y);
	for (int i = 0; i < z; i++) {
		addedge(i, (i + x) % z, x);
		addedge(i, (i + y) % z, y);
	}
	memset(dis, 0x3f, sizeof dis);
	dis[1 % z] = 1;
	q.push(1 % z);
	while (!q.empty()) {
		int pos = q.front();
		q.pop();
		vis[pos] = 0;
		for (int i = head[pos]; i; i = e[i].next) {
			int nx = e[i].to;
			if (dis[nx] > dis[pos] + e[i].w) {
				dis[nx] = dis[pos] + e[i].w;
				if (!vis[nx]) {
					q.push(nx);
					vis[nx] = 1;
				}
			}
		}
	}
	for (int i = 0; i < z; i++) {
		if (dis[i] <= n) ans += (n - dis[i]) / z + 1;
	}
	printf("%lld", ans);
}