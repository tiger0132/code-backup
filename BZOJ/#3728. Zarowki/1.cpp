#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <queue>

const int N = 5e5 + 55;

std::priority_queue<int, std::vector<int>, std::greater<int>> pq, pq2;
int n, k, a[N], b[N];
long long ans;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) scanf("%d", b + i);
	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + n + 1);
	for (int i = n, j = n; i >= 1; i--) {
		while (j && a[j] >= b[i]) pq.push(a[j--]);
		if (pq.empty()) {
			ans += b[i];
			if (!k--) return puts("NIE"), 0;
		} else {
			int x = pq.top();
			ans += x, pq.pop();
			pq2.push(b[i] - x);
		}
	}
	for (; k-- && !pq2.empty(); pq2.pop()) ans += pq2.top();
	printf("%lld", ans);
}