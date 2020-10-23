#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 2e4 + 42;

struct node {
	int x, d;
	bool operator<(const node &r) const { return d > r.d; }
};

std::priority_queue<node> pq;
std::vector<pii> g[N];
int n;
void spfa(int id, int *dis) {
	memset(dis, 0x3f, (n + 1) << 4);
	dis[id] = 0;
	for (pq.push({id, 0}); !pq.empty();) {
		auto [x, d] = pq.top();
		pq.pop();
		if (d != x[dis]) continue;
		for (auto [nx, w] : x[g])
			if (nx[dis] > x[dis] + w) pq.push({nx, nx[dis] = x[dis] + w});
	}
}

#define dis(i, j) dis0[i + 2][j + 2]
#define f(i, S) f0[i][squ(S, i)]
#define cmin(x, y) x = std::min(x, y)

int dis0[25][N], f0[25][1 << 19], L[25];
int m, k, l, U, ans;
inline int squ(int S, int i) {
	return (S & ((1 << i) - 1)) | ((S >> 1) & ~((1 << i) - 1));
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, x, y, z; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		x[g].emplace_back(y, z);
		y[g].emplace_back(x, z);
	}
	scanf("%d", &l);
	for (int i = 1, x, y; i <= l; i++) {
		scanf("%d%d", &x, &y), x -= 2, y -= 2;
		L[y] |= 1 << x;
	}
	for (int i = 1; i <= k + 1; i++) spfa(i, dis0[i]);

	n -= 2;
	U = (1 << k) - 1;
	ans = 1e9;

	if (!k) return !printf("%d\n", dis(-1, n));

	memset(f0, 0x3f, sizeof f0);
	for (int i = 0; i < k; i++)
		if (!L[i]) f(i, 1 << i) = dis(-1, i);
	for (int S = 0; S <= U; S++)
		for (int i = 0; i < k; i++)
			if ((S >> i) & 1)
				for (int j = 0; j < k; j++)
					if (!((S >> j) & 1) && ((S & L[j]) == L[j]))
						cmin(f(j, S | (1 << j)), f(i, S) + dis(i, j));
	for (int i = 0; i < k; i++) cmin(ans, f(i, U) + dis(i, n));
	printf("%d\n", ans);
}