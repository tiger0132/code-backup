给一个 $n\cdot m$ 的数组，其中的元素为 $1\sim nm$ 的一个排列，您可以依次进行下面的操作：

- 重排每一行的数。
- 重排每一列的数。
- 重排每一行的数。

要求依次做完这些操作后，第 $i$ 行第 $j$ 列的数为 $(i-1)m+j$，并给出方案。可以证明一定有解。

$1\le n,m\le100$。

---

设 $[(i-1)m+1,im)$ 区间里的整数的颜色为 $i$，那么实际上原问题等价于：做完前两次操作后，对于任意的 $i$，第 $i$ 行的颜色都是 $i$。

那么这又等价于：做完第一次操作后，每一列都正好出现了 $1\sim n$ 这 $n$ 种颜色。

换句话说，我们要从每一行选一个，使得颜色互不相同，然后这样选 $m$ 次。

考虑给每一行开一个点，每种颜色开一个点。如果某一行存在某种颜色，那么在它们之间连边，如果存在多次则连多条边。我们要将这张图分解成 $m$ 个完美匹配。

……然后注意到这是一个 $m$-正则图，这意味着这个方案一定是存在的。这意味着我们可以直接使用边染色的增量方案。

复杂度 $O(nm^2)$。

---

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e2 + 22, M = 4e4 + 44;

int n, m, g[N][N], id[N][N], col[M], a[N][N], b[N][N], c[N][N], tmp[N];
inline int _(int i, int j) { return m * (i - 1) + j; }
int main() {
	scanf("%d%d", &n, &m);
	auto dfs = [&](auto d, int x, int cur, int last) -> void {
		std::swap(x[g][cur], x[g][last]);
		std::swap(x[id][cur], x[id][last]);
		x[id][last][col] = last;
		if (x[g][last]) d(d, x[g][last], last, cur);
	};
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			scanf("%d", a[i] + j);
			int x = (a[i][j] - 1) / m + 1, y = i + n, u = 0, v = 0, nid = m * (i - 1) + j;
			for (int k = 1; !u && k <= m; k++)
				if (!x[g][k]) u = k;
			for (int k = 1; !v && k <= m; k++)
				if (!y[g][k]) v = k;
			if (x[g][v]) dfs(dfs, x, v, u);
			x[g][v] = y, x[id][v] = nid;
			y[g][v] = x, y[id][v] = nid;
			nid[col] = v;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) b[i][_(i, j)[col]] = a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) printf("%d%c", b[i][j], " \n"[j == m]);
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) tmp[i] = b[i][j];
		std::sort(tmp + 1, tmp + n + 1);
		for (int i = 1; i <= n; i++) c[i][j] = tmp[i];
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) printf("%d%c", c[i][j], " \n"[j == m]);
}
```