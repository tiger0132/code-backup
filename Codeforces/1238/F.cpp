#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5 + 53;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int ans, dp[N];
void dfs(int x, int p) {
	int s = 0, m1 = 0, m2 = 0;
	x[dp] = 0;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs(nx, x);
			if (nx[dp] > m1)
				m2 = m1, m1 = nx[dp];
			else if (nx[dp] >= m2)
				m2 = nx[dp];
			s++, x[dp] = std::max(x[dp], nx[dp]);
		}
	ans = std::max(ans, m1 + m2 + 1 + s + !!p), x[dp] += s;
}

int n, x, y;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
		dfs(1, 0);
		printf("%d\n", ans);
		memset(head, 0, (n + 1) * 4), memset(dp, 0, (n + 1) * 4), cnt = ans = 0;
	}
}