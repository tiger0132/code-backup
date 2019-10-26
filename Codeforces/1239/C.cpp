#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#define x first
#define y second

typedef std::pair<int, int> pii;
typedef long long ll;
const int N = 1e5 + 51;

std::priority_queue<pii, std::vector<pii>, std::greater<pii>> src;
std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
std::queue<int> q;

int n, k, p, a[N], id[N];
ll t, ans[N];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), src.push({a[i], i});
	for (int i = 1; i <= n; i++, t += k) {
		if (q.empty()) t = src.top().x + k;
		for (pii x; !src.empty() && (x = src.top()).x <= t; src.pop())
			if (q.empty() || x.y < q.back())
				q.push(x.y);
			else
				pq.push(x.y);
		ans[q.front()] = t, q.pop();
		if (!pq.empty() && q.empty()) q.push(pq.top()), pq.pop();
	}
	for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);
}