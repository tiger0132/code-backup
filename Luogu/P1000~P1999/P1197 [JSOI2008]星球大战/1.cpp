#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 4e5 + 54;

int p[N], lans;
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void u(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y, lans--;
}

int n, m, x, y, ans[N], vis[N], op[N];
std::vector<int> v[N];
int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d", &x, &y), x++, y++;
		x[v].push_back(y), y[v].push_back(x);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d", op + i), (++op[i])[vis] = 1;
	lans = n;
	for (int i = 1; i <= n; i++)
		if (!i[vis])
			for (int j : i[v])
				if (!j[vis]) u(i, j);
	for (int i = m; i >= 1; i--) {
		i[ans] = lans;
		op[i][vis] = 0;
		for (int j : op[i][v])
			if (!j[vis]) u(op[i], j);
	}
	printf("%d\n", lans);
	for (int i = 1; i <= m; i++) printf("%d\n", i[ans] - i);
}