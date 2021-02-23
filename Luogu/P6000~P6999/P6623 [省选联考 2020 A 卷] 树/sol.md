考虑用一棵 Trie 维护子树中所有的点权，其中点权按照二进制位从小到大的顺序插入到 Trie 中（即根是最低位）。

那么有了一个显然的想法：把子树的 Trie 合并起来然后全局 +1。

考虑到二进制下 +1 实际上是将极长全 $1$ 后缀和前面的一个 $0$ 翻转，而且 Trie 的深度只有 $\log w$，所以可以直接操作。显然也可以同时维护全局异或和。单次操作严格 $O(\log w)$。

显然可以规约到普通线段树合并。可得复杂度为 $O(n\log w)$。

---

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define L ch][0
#define R ch][1

const int N = 6e5 + 56, M = 1.4e7 + 741, K = 21;

int rt[N], ch[M][2], sum[M], pari[M], nc;
inline void up(int x) {
	x[pari] = x[L][pari] ^ x[R][pari];
	x[sum] = ((x[L][sum] ^ x[R][sum]) << 1) | x[R][pari];
}
void ins(int x, int v) {
	for (int i = 0; i < K; i++, v >>= 1) {
		x[sum] ^= v;
		x[pari] ^= 1;
		if (x[ch][v & 1])
			x = x[ch][v & 1];
		else
			x = x[ch][v & 1] = ++nc;
	}
	x[pari] ^= 1;
}
int mg(int x, int y) {
	if (!x || !y) return x | y;
	x[sum] ^= y[sum], x[pari] ^= y[pari];
	x[L] = mg(x[L], y[L]);
	x[R] = mg(x[R], y[R]);
	return x;
}
void upd(int x) {
	std::swap(x[L], x[R]);
	if (x[L]) upd(x[L]);
	if (x[L] || x[R]) up(x);
}

std::vector<int> g[N];
long long ans;
int v[N];
void dfs(int x) {
	x[rt] = ++nc;
	for (int nx : x[g]) {
		dfs(nx);
		x[rt] = mg(x[rt], nx[rt]);
	}
	upd(x[rt]);
	ins(x[rt], x[v]);
	ans += x[rt][sum];
}

int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", v + i);
	for (int i = 2, x; i <= n; i++) {
		scanf("%d", &x);
		x[g].push_back(i);
	}
	dfs(1);
	printf("%lld\n", ans);
}
```