#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef long long ll;
const int N = 2e5 + 52;

std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
int n, cnt, p[N], m[N], pre[N];
std::vector<int> v[N];
ll ans;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 0; i < n; i++) i[v].clear();
		for (int i = 1; i <= n; i++) scanf("%d%d", m + i, p + i), m[i][v].push_back(p[i]);
		for (int i = 0; i < n; i++) pre[i] = (i > 0) * pre[i - 1] + i[v].size();
		for (int i = n - 1; i >= 1; i--) {
			for (int j : i[v]) pq.push(j);
			while (pre[i - 1] + cnt < i) ans += pq.top(), pq.pop(), cnt++;
		}
		while (!pq.empty()) pq.pop();
		printf("%lld\n", ans);
		memset(pre, 0, n * 4), ans = cnt = 0;
	}
}