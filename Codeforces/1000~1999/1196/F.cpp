#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <unordered_map>

typedef long long ll;
typedef std::pair<int, int> pii;
const int N = 2e3 + 32, M = 1e6 + 64;

struct ed {
	int x, y, z;
	bool operator<(const ed& r) const { return z < r.z; }
} e2[M << 1];

struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}, head[y] = cnt;
}

std::unordered_map<int, int> mp;
int id(int x) {
	if (!mp.count(x)) return mp[x] = mp.size() + 1;
	return mp[x];
}

ll dis[N], a[M];
void dijspfa(int s) {
	memset(dis, 0x3f, sizeof dis);
	std::priority_queue<pii> pq;
	for (pq.push(pii(0, s)), dis[s] = 0; !pq.empty();) {
		int x = pq.top().second, y = -pq.top().first;
		pq.pop();
		if (dis[x] < y) continue;
		for (int i = head[x], nx; i; i = e[i].next)
			if (dis[nx = e[i].to] > dis[x] + e[i].w) {
				dis[nx] = dis[x] + e[i].w;
				pq.push(pii(-dis[nx], nx));
			}
	}
}

int n, m, k, u, v, t;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &e2[i].x, &e2[i].y, &e2[i].z);
	std::sort(e2 + 1, e2 + m + 1);
	for (int i = 1; i <= std::min(m, k); i++) {
		u = id(e2[i].x), v = id(e2[i].y);
		addedge(u, v, e2[i].z);
	}
	n = mp.size();
	for (int i = 1; i <= n; i++) {
		dijspfa(i);
		for (int j = i + 1; j <= n; j++) a[++t] = dis[j];
	}
	std::sort(a + 1, a + t + 1);
	printf("%lld", a[k]);
}