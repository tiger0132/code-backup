#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e3 + 32, K = 1e3 + 31, M = 2e6 + 62;
struct edge {
	int to, next;
} e[M << 1];
int head[N], d[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, head[x]}, head[x] = cnt, d[y]++; }

int n, m, p[N], ord[N], tot;
char a[K][K];
int F(int x) { return p[x] ? p[x] = F(p[x]) : x; }
void M_(int x, int y) {
	if ((x = F(x)) != (y = F(y))) p[x] = y;
}
std::queue<int> q;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", a[i] + 1);
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == '=') M_(i, j + n);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == '<') addedge(F(i), F(j + n));
			if (a[i][j] == '>') addedge(F(j + n), F(i));
		}
	}
	for (int i = 1; i <= n + m; i++)
		if (!d[i]) q.push(i), ord[i] = 1;
	for (; !q.empty(); q.pop()) {
		int x = q.front();
		for (int i = head[x]; i; i = e[i].next) {
			ord[e[i].to] = std::max(ord[e[i].to], ord[x] + 1);
			if (!--d[e[i].to]) q.push(e[i].to);
		}
	}
	for (int i = 1; i <= n + m; i++)
		if (!ord[i]) return puts("No"), 0;
	puts("Yes");
	for (int i = 1; i <= n + m; i++) printf("%d ", ord[i]);
}