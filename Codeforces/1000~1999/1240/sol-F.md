有 $n$ 个球队、$m$ 场比赛和 $k$ 个体育场，第 $i$ 场比赛是 $a_i$ 和 $b_i$ 打。您可以选择每场比赛在哪个体育场打，或者不打。

设 $s_{i,j}$ 为 $i$ 球队在 $j$ 体育场打的比赛的数量，那么对于每一个 $i$，必须有：$s_{i,1},s_{i,2},\ldots,s_{i,k}$ 的极差 $\le2$。

每个球队有一个 $w_i$。如果这个球队打了 $l$ 场，那么价值为 $w_i\cdot l$。您要给出一个比赛方案，使得价值总和尽可能大。

$3\le n\le100$，$0\le m\le1000$，$1\le k\le1000$，$1\le w_i\le1000$。

---

# 做法 1

考虑开 $n$ 个新点 $n+1\sim2n$，对于原图的每条边 $(x,y)$，改成 $(x,y+n)$ 加到新图中，那么就得到了一个新二分图。

根据 [#81 (CF212A)](/p/81) 的结论，二分图上每个点邻边颜色出现次数的极差可以 $\le1$，那么把 $i$ 和 $i+n$ 拼起来之后极差一定 $\le2$。

所以我们直接按照 [#81 (CF212A)](/p/81) 的做法来就好了。

*代码都只要改一两行……很难不怀疑是故意的*

# 做法 2

还有一个 nb 随机化做法……先咕了

---

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e2 + 22, M = 8e4 + 48;

int n, m, k, deg[2 * N], nid[2 * N], g[M][N], eid[M][N], col[M], cnt;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%*d");
	auto dfs = [&](auto d, int x, int cur, int last) -> void {
		std::swap(x[g][cur], x[g][last]);
		std::swap(x[eid][cur], x[eid][last]);
		x[eid][last][col] = last;
		if (x[g][last]) d(d, x[g][last], last, cur);
	};
	for (int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &x, &y), y += n;
		if (x[deg]++ % k == 0) x[nid] = ++cnt;
		if (y[deg]++ % k == 0) y[nid] = ++cnt;
		x = x[nid], y = y[nid];
		int u = 0, v = 0;
		for (int j = 1; !u && j <= k; j++)
			if (!x[g][j]) u = j;
		for (int j = 1; !v && j <= k; j++)
			if (!y[g][j]) v = j;
		if (x[g][v]) dfs(dfs, x, v, u);
		x[g][v] = y, x[eid][v] = i;
		y[g][v] = x, y[eid][v] = i;
		i[col] = v;
	}
	for (int i = 1; i <= m; i++) printf("%d\n", col[i]);
}
```