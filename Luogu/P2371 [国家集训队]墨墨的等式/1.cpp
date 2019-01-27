#include <cstdio>
#include <cstring>
#include <queue>

typedef long long ll;
const int N = 22, M = 5e5 + 55, INF = 0x3f3f3f3f;

int n, a[N], vis[M];
std::queue<int> q;
ll l, r, dis[M];

ll query(ll x) {
	ll ret = 0;
	for (int i = 0; i < a[1]; i++) {
		if (dis[i] <= x) ret += (x - dis[i]) / a[1] + 1;
	}
	return ret;
}

int main() {
	scanf("%d%lld%lld", &n, &l, &r);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	memset(dis, 0x3f, sizeof dis);
	dis[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int pos = q.front();
		vis[pos] = 0;
		q.pop();
		for (int i = 2; i <= n; i++) {
			int nx = (pos + a[i]) % a[1];
			if (dis[nx] > dis[pos] + a[i]) {
				dis[nx] = dis[pos] + a[i];
				if (!vis[nx]) {
					vis[nx] = 1;
					q.push(nx);
				}
			}
		}
	}
	printf("%lld\n", query(r) - query(l - 1));
	return 0;
}