#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e5 + 52;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], od[N], d[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt, x[od]++, y[d]++;
}

double dp[N], p[N];
int n, m, x, y, z;
std::queue<int> q;
int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	memcpy(d, d, (n + 1) * 4);
	p[1] = 1;
	for (q.push(1); !q.empty(); q.pop())
		for (int i = (x = q.front())[head], nx; i; i = e[i].next) {
			nx = e[i].to;
			nx[p] += x[p] / x[od];
			nx[dp] += (x[dp] + e[i].w * x[p]) / x[od];
			if (!--nx[d]) q.push(nx);
		}
	printf("%.2f", dp[n]);
}