#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

typedef std::pair<int, int> pii;
const int N = 6e5 + 56;

std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
int n, top, m, x, y, ans;
pii a[N];
int main() {
	scanf("%d%d", &n, &m), pq.push(-1e9);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x, &y);
		a[++top] = pii(x, 1), a[++top] = pii(x + y, 0);
	}
	std::sort(a + 1, a + top + 1);
	for (int i = 1; i <= top; i++)
		if (a[i].second) {
			if (pq.top() + m >= a[i].first) pq.pop(), ans++;
		} else
			pq.push(a[i].first);
	printf("%d", ans);
}