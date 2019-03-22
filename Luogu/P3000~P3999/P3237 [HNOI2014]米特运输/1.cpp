#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>

const int N = 5e5 + 55;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

struct node {
	double x;
	bool operator<(const node& rhs) const { return rhs.x - x > 1e-8; }
};

std::map<node, int> mp;
double a[N], b[N];
void dfs(int x, int p) {
	int tot = 0;
	mp[(node){a[x] + b[x]}]++;
	for (int i = head[x]; i; i = e[i].next) tot += e[i].to != p;
	for (int i = head[x], nx; i; i = e[i].next) {
		if ((nx = e[i].to) == p) continue;
		b[nx] = b[x] + log(tot);
		dfs(nx, x);
	}
}

int n, x, y, ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		a[i] = log(x);
	}
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	dfs(1, 0);
	for (auto i : mp) ans = std::max(ans, i.second);
	printf("%d", n - ans);
}