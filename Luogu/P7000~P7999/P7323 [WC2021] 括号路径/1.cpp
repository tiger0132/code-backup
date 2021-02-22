#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <unordered_map>

const int N = 6e5 + 56;

std::unordered_map<int, int> mp[N];
std::queue<std::pair<int, int>> q;
int p[N], sz[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void mg(int x, int y) {
	if ((x = f(x)) == (y = f(y))) return;
	y[p] = x, x[sz] += y[sz];
	if (mp[x].size() < mp[y].size()) mp[x].swap(mp[y]);
	for (auto [col, z] : mp[y])
		if (mp[x][col])
			q.push({mp[x][col], z});
		else
			mp[x][col] = z;
	mp[y].clear();
}

long long ans;
int n, m, k;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) i[sz] = 1;
	for (int i = 1, x, y, z; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		if (mp[y][z])
			q.push({mp[y][z], x});
		else
			mp[y][z] = x;
	}
	for (; !q.empty(); q.pop()) {
		auto [x, y] = q.front();
		mg(x, y);
	}
	for (int i = 1; i <= n; i++)
		if (!i[p]) ans += i[sz] * (i[sz] - 1ll) / 2;
	printf("%lld", ans);
}