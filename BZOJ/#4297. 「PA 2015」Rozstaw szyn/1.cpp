#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 5e5 + 55;

std::vector<int> g[N];
int n, m, l[N], r[N];
long long ans;
void dfs(int x, int p) {
	std::vector<int> v;
	for (int nx : x[g])
		if (nx != p) {
			dfs(nx, x);
			v.push_back(nx[l]);
			v.push_back(nx[r]);
		}
	if (v.empty()) return;
	std::sort(v.begin(), v.end());
	x[l] = v[v.size() / 2 - 1];
	x[r] = v[v.size() / 2];
	for (int nx : x[g])
		if (nx != p && (x[l] < nx[l] || nx[r] < x[l]))
			ans += std::min({std::abs(x[l] - nx[l]), std::abs(x[l] - nx[r])});
}

int x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		x[g].push_back(y);
		y[g].push_back(x);
	}
	for (int i = 1; i <= m; i++) scanf("%d", l + i), r[i] = l[i];
	if (n == m) {
		for (int i = 1; i <= n; i++)
			for (int j : i[g]) ans += abs(i[l] - j[l]);
		printf("%lld", ans / 2);
		return 0;
	}
	dfs(n, 0);
	printf("%lld\n", ans);
}