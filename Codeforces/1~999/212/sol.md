给一张 $n$ 个左部点，$m$ 个右部点，$k$ 条边的二分图，您需要把每条边染成 $1\sim t$ 中的一种颜色。

设一个点的代价为所有以其为端点的边中，颜色出现次数的极差。您要给出一种染色方案，使得所有点（含左部和右部）的代价和尽可能小。

$1\le n,m,t\le200$，$1\le k\le5000$。

---

首先，答案的下界是 $\sum[\deg(i)\bmod k>0]$。

然后我们可以证明，这个下界是一定可以取到的……

证明：考虑一条一条加边，如果某条边 $(x,y)$ 的某个顶点 $u\in\{x,y\}$（或者两个顶点）的度数达到了 $t$，那么开一个新点 $u'$，把 $(x,y)$ 中的 $u$ 换成 $u'$，然后再连边（两个顶点度数均达到了 $t$ 则都进行类似处理）。那么最后每一个点 $x$ 会被拆成 $\lceil\deg(x)/t\rceil$ 个点，其中最多有一个点的度数不是 $t$，其它点的度数均为 $t$。

这样我们将原图拆成了若干个连通块，其中每个点度数 $\le t$。如果我们将每个连通块的边染色，使得块中每个点的邻边颜色互不相同，由于度数为 $t$ 的点的所有邻边会使每种颜色的出现次数整体 $+1$，所以这显然取到了答案的下界。

根据结论，二分图的边色数为其最大度数，所以一定存在这种方案。

具体的构造方法可以参考 [#83. 二分图学习笔记](/b/83) 中的算法。结合这里的拆点做法可以在 $O(nmt)/O(mt^2\sqrt n)/O(mt\sqrt n\log t)/O(mt\log m\log t)/O(mt\log m)$ 的时间解决。

显然我懒得碰后面的做法，就写了一个 $O(nmt)$ 的。

---

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e2 + 22, M = 8e4 + 48;

int n, m, t, k, deg[2 * N], nid[2 * N], g[M][N], eid[M][N], col[M], ans, cnt;
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &t);
	auto dfs = [&](auto d, int x, int cur, int last) -> void {
		std::swap(x[g][cur], x[g][last]);	   // swap edges
		std::swap(x[eid][cur], x[eid][last]);  // sync edge ids
		x[eid][last][col] = last;  // change the out edge (x, y, cur) -> (x, y, last)
		if (x[g][last]) d(d, x[g][last], last, cur);
	};
	for (int i = 1, x, y; i <= k; i++) {
		scanf("%d%d", &x, &y), y += n;
		if (x[deg]++ % t == 0) x[nid] = ++cnt;
		if (y[deg]++ % t == 0) y[nid] = ++cnt;
		x = x[nid], y = y[nid];
		int u = 0, v = 0;
		for (int j = 1; !u && j <= t; j++)
			if (!x[g][j]) u = j;
		for (int j = 1; !v && j <= t; j++)
			if (!y[g][j]) v = j;
		if (x[g][v]) dfs(dfs, x, v, u);
		x[g][v] = y, x[eid][v] = i;
		y[g][v] = x, y[eid][v] = i;
		i[col] = v;
	}
	for (int i = 1; i <= n + m; i++) ans += deg[i] % t > 0;
	printf("%d\n", ans);
	for (int i = 1; i <= k; i++) printf("%d%c", col[i], " \n"[i == k]);
}
```