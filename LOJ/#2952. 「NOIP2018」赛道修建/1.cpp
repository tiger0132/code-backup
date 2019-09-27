#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>

const int N = 5e4 + 45;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z}, y[head] = cnt;
}

int mid, ans, g[N];
void dfs(int x, int p) {
	std::multiset<int> s;
	x[g] = 0;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x);
	for (int i = x[head], nx, w; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			w = e[i].w;
			if (nx[g] + w >= mid)
				ans++;
			else
				s.insert(nx[g] + w);
		}
	for (int t; !s.empty();) {
		t = *s.begin();
		s.erase(s.begin());
		auto it = s.lower_bound(mid - t);
		if (it == s.end())
			x[g] = std::max(x[g], t);
		else
			s.erase(it), ans++;
	}
	s.clear();
}
int n, m, x, y, z, l = 1, r;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) scanf("%d%d%d", &x, &y, &z), addedge(x, y, z), r += z;
	while (l + 1 <= r) {
		mid = (l + 1 + r) / 2, ans = 0;
		dfs(1, 0);
		if (ans < m)
			r = mid - 1;
		else
			l = mid;
	}
	printf("%d", l);
}