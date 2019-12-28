#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2e5 + 52;
struct edge {
	int x, y, z;
	bool operator<(const edge& r) const { return z < r.z; }
} a[N];

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }

int n, m, q[N], id[N], sz[N];
ll lans, ans[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) sz[i] = 1;
	for (int i = 1; i < n; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
	for (int i = 1; i <= m; i++) scanf("%d", q + i), id[i] = i;
	std::sort(a + 1, a + n);
	std::sort(id + 1, id + m + 1, [](int x, int y) { return q[x] < q[y]; });
	for (int i = 1, j = 1; i <= m; i++) {
		for (; j < n && a[j].z <= q[id[i]]; j++) {
			int u = f(a[j].x), v = f(a[j].y);
			lans += 1ll * u[sz] * v[sz];
			u[p] = v, v[sz] += u[sz];
		}
		ans[id[i]] = lans;
	}
	for (int i = 1; i <= m; i++) printf("%lld ", ans[i]);
}