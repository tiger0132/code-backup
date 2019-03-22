#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long

const int N = 1e3 + 31, M = 2e6 + 62, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w, c;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}
int ek(int s, int t) {
	static int dis[N], vis[N], pre[N], flow[N];
	std::queue<int> q;
	int ret = 0, m = 0;
	while ("每日一膜：G♂LX") {
		memset(dis, 0xc0, sizeof dis);
		flow[s] = INF, dis[s] = 0;
		for (q.push(s); !q.empty();) {
			int x = q.front();
			vis[x] = 0;
			q.pop();
			for (int i = head[x]; i; i = e[i].next) {
				int nx = e[i].to;
				if (e[i].w && dis[nx] < dis[x] + e[i].c) {
					dis[nx] = dis[x] + e[i].c;
					flow[nx] = std::min(flow[x], e[i].w);
					pre[nx] = i;
					if (!vis[nx]) vis[nx] = 1, q.push(nx);
				}
			}
		}
		if (dis[t] == 0xc0c0c0c0) return ret;
		if (m + flow[t] * dis[t] < 0) return ret - m / dis[t];
		for (int i = pre[t]; i; i = pre[e[i ^ 1].to]) {
			e[i].w -= flow[t];
			e[i ^ 1].w += flow[t];
		}
		ret += flow[t];
		m += flow[t] * dis[t];
	}
}

int $(int x) {
	int ret = 0;
	for (int i = 2; i <= sqrt(x); i++)
		for (; x % i == 0; ret++) x /= i;
	return ret + (x > 1);
}
int n, a[N], b[N], c[N], f[N];
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a + i);
		f[i] = $(a[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", b + i);
		if (f[i] & 1)
			addedge(1, i + 2, b[i], 0);
		else
			addedge(i + 2, 2, b[i], 0);
	}
	for (int i = 1; i <= n; i++) scanf("%lld", c + i);
	for (int i = 1; i <= n; i++) {
		if (f[i] & 1)
			for (int j = 1; j <= n; j++) {
				if ((f[i] == f[j] + 1 && a[i] % a[j] == 0) || (f[j] == f[i] + 1 && a[j] % a[i] == 0))
					addedge(i + 2, j + 2, INF, c[i] * c[j]);
			}
	}
	printf("%lld", ek(1, 2));
}