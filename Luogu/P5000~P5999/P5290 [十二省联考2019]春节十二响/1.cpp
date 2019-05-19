#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e5 + 52;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
inline void addedge(int x, int y) { e[++cnt] = (edge){y, head[x]}, head[x] = cnt; }

std::priority_queue<int> pq[N];
std::queue<int> tmp;
int a[N];
void dfs(int x) {
	for (int i = head[x], nx; i; i = e[i].next) {
		dfs(nx = e[i].to);
		if (pq[x].size() < pq[nx].size()) pq[x].swap(pq[nx]);
		for (; !pq[nx].empty(); pq[x].pop(), pq[nx].pop()) tmp.push(std::max(pq[x].top(), pq[nx].top()));
		for (; !tmp.empty(); tmp.pop()) pq[x].push(tmp.front());
	}
	pq[x].push(a[x]);
}

long long ans;
int n, x;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 2; i <= n; i++) scanf("%d", &x), addedge(x, i);
	for (dfs(1); !pq[1].empty(); pq[1].pop()) ans += pq[1].top();
	printf("%lld", ans);
}