首先我们可以观察到下面这些性质：

- 如果 $x\to y$ 合法，那么 $y\to x$ 合法。
- 如果 $x\leftrightarrow y$，$y\leftrightarrow z$ 合法，那么 $x\leftrightarrow z$ 合法。
- 如果存在边 $x\xrightarrow wz$，$y\xrightarrow wz$，那么 $x\leftrightarrow y$ 合法。

前两个性质意味着，如果 $x\leftrightarrow y$，那么 $x,y$ 可以合并成一个点，并且合法性不变。而第三个性质给出了合并图中的节点的方式。

一个合理的想法是，用类似拓扑排序的方法合并。首先把所有满足性质三的 $x,y$ 入队，每次合并完后，检查是否形成了新的 $x,y$ 对。如果无法继续合并，显然剩下的点之间不可能形成新的。

检测存在 $x,y$ 对的方法也很简单：对于每一个点，开一个哈希表 / map 记录它每种颜色的其中一条入边的起点。如果在尝试更新记录时发现已经有记录了，那么将这两个点合并。

最终答案为 $\sum\binom{sz}2$。sz 可以在使用并查集维护从属关系时同时维护。

合并点的同时需要合并对应的数据结构，可以使用启发式合并降低复杂度。

总复杂度为 $O(m\log m)$。

---

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <unordered_map>

const int N = 6e5 + 56;

std::unordered_map<int, int> mp[N];
std::queue<std::pair<int, int>> q;
int p[N], sz[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void mg(int x, int y) {
	if ((x = f(x)) == (y = f(y))) return;
	y[p] = x, x[sz] += y[sz];
	if (mp[x].size() < mp[y].size()) mp[x].swap(mp[y]);
	for (auto [col, z] : mp[y])
		if (mp[x][col])
			q.push({mp[x][col], z});
		else
			mp[x][col] = z;
	mp[y].clear();
}

long long ans;
int n, m, k;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) i[sz] = 1;
	for (int i = 1, x, y, z; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		if (mp[y][z])
			q.push({mp[y][z], x});
		else
			mp[y][z] = x;
	}
	for (; !q.empty(); q.pop()) {
		auto [x, y] = q.front();
		mg(x, y);
	}
	for (int i = 1; i <= n; i++)
		if (!i[p]) ans += i[sz] * (i[sz] - 1ll) / 2;
	printf("%lld", ans);
}
```