#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 3e5 + 53, M = 1e5 + 51;
struct edge {
	int x, y;
};

int n, m, x, y, z, dp[N], tmp[N];
std::vector<edge> ed[M];
int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d%d", &x, &y, &z);
		ed[z].push_back({x, y});
	}
	for (int i = 1; i < M; i++) {
		for (const edge& j : ed[i]) tmp[j.y] = dp[j.y];
		for (const edge& j : ed[i]) tmp[j.y] = std::max(tmp[j.y], dp[j.x] + 1);
		for (const edge& j : ed[i]) dp[j.y] = tmp[j.y];
	}
	printf("%d\n", *std::max_element(dp + 1, dp + n + 1));
}