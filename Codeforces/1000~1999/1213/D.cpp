#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e5 + 52;

int n, k, x, l, ans = 1e9;
std::vector<int> v[N];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1, j; i <= n; i++) {
		scanf("%d", &x), j = 0;
		do
			v[x].push_back(j++);
		while (x /= 2);
	}
	for (int i = 0; i < N; i++)
		if (v[i].size() >= k) {
			std::sort(v[i].begin(), v[i].end());
			for (int j = l = 0; j < k; j++) l += v[i][j];
			ans = std::min(ans, l);
		}
	printf("%d", ans);
}