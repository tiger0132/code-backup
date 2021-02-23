首先建出表达式树。

# 70pts 做法

设 $a_{i,j}=A_{j,i}$，$f(x,i,j)$ 代表 $x$ 子树中，$a_i$ 这一行，计算结果是 $a_{i,j}$ 的方案数。

那么 `<` 和 `>` 的转移分别对应两个 $\min$ 和 $\max$ 卷积的式子，`?` 的转移是 `<` 和 `>` 相加。这里给出 `<` 的转移：

$$
f(x,i,j)=\sum_{\min(a,b)=j}f(l,i,a)f(l,i,b)
$$

其中 $l,r$ 为 $x$ 的左右儿子。

这些转移可以在 $O(m)$ 完成。所以总复杂度为 $O(nm|S|)$ 的。

按照这个做法的思路，每次计算一整行的答案，总共的需要计算的行数为 $\min(n,m!)$，无法优化。

# 100pts 做法

70pts 做法的问题在于无法减少行数。考虑如何压缩行的信息，并减少需要计算的行数。

观察到对于某个元素 $a_{i,j}$，它成为当前行的最终答案的方案数只与 $a_{i,0},a_{i,1},\ldots a_{i,m}$ 和它的大小关系有关。

于是考虑构造一个 01 串来描述行的状态。定义 ${\sf State}(a_i,j)$ 为一个长为 $m$ 的 01 串，其中第 $k$ 位的值是 $[a_{i,k}<a_{i,j}]$。

于是我们得到了做法的大致轮廓：预处理出每种行状态的结果，然后扫一遍所有行直接计算出答案。

然后考虑具体怎么转移。设 $f(x,S,0/1)$ 为 $x$ 子树中，行状态为 $S$ 时，答案小于 / 大于等于 $a_{*,j}$ 的方案数。同样的，这里仅给出 `<` 的转移：

$$
f(x,S,op)=\sum_{\min(a,b)=op}f(l,S,a)f(r,S,b)
$$

最后是统计答案。设 $a'_i$ 为 $a_i$ 从小到大排序后的结果，那么答案为：

$$
\sum_{j=1}^m(a'_j-a'_{j-1})\cdot f({\rm root},{\sf State}(a'_i,j),1)
$$

# 代码

```cpp
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#define L ch][0
#define R ch][1

typedef long long ll;
const int N = 5e4 + 45, P = 1e9 + 7;
struct Z {
	static int norm(int x) { return x + (x >> 31 & P); }
	static void norm2(int& x) { x += x >> 31 & P; }
	int x;
	Z() {}
	Z(int v) : x(v) {}
	Z(long long v) : x(v) {}
	Z(char v) : x(v) {}
	Z operator+(const Z& rhs) const { return norm(x + rhs.x - P); }
	Z operator-(const Z& rhs) const { return norm(x - rhs.x); }
	Z operator*(const Z& rhs) const { return (ll)x * rhs.x % P; }
	void operator+=(const Z& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const Z& rhs) { norm2(x -= rhs.x); }
	void operator*=(const Z& rhs) { x = (ll)x * rhs.x % P; }
};

int ch[N][2], rt, nc;
char s[N], op[N];
int lb[N];
void build(int& x, int l, int r) {
	if (s[r] == ')' && lb[r] == l) return build(x, l + 1, r - 1);
	x = ++nc;
	if (l == r) return x[op] = s[l], void();
	int pos = lb[r] - 1;
	x[op] = s[pos];
	build(x[L], l, pos - 1);
	build(x[R], pos + 1, r);
}

Z F[N], f[N][2], ans;
void dfs(int x, int S) {
	if (!x[L]) {
		x[f][0] = (S >> (x[op] - '0')) & 1;
		x[f][1] = !((S >> (x[op] - '0')) & 1);
		return;
	}
	dfs(x[L], S), dfs(x[R], S);
	for (int a = 0; a <= 1; a++)
		for (int b = 0; b <= 1; b++) {
			if (x[op] != '>') x[f][std::min(a, b)] += x[L][f][a] * x[R][f][b];
			if (x[op] != '<') x[f][std::max(a, b)] += x[L][f][a] * x[R][f][b];
		}
}

int n, m, len, a[N][22], tmp[22];
int st[N], top;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) scanf("%d", a[j] + i);

	scanf("%s", s + 1), len = strlen(s + 1);
	for (int i = 1; i <= len; i++)
		if (s[i] == '(')
			st[++top] = i;
		else if (s[i] == ')')
			lb[i] = st[top--];
		else
			lb[i] = i;
	build(rt, 1, len);

	for (int S = 0; S < (1 << m); S++) {
		memset(f, 0, sizeof f);
		dfs(rt, S);
		F[S] = rt[f][1];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) tmp[j] = a[i][j];
		std::sort(tmp + 1, tmp + m + 1);
		for (int j = 1; j <= m; j++) {
			int S = 0;
			for (int k = 1; k <= m; k++) S |= (a[i][k] < tmp[j]) << (k - 1);
			ans += F[S] * (tmp[j] - tmp[j - 1]);
		}
	}
	printf("%d\n", ans.x);
}
```

# 一些思考

在最开始设计 100pts DP 时，我想到了这样一个状态：$f(j,S,\ldots)$ 代表当前枚举的列下标为 $j$，行中另外 $m-1$ 个数与 $a_{*,j}$ 的大小关系为 $S$，并且答案满足某些条件的方案数。

这个 DP 的状态空间是 $m2^{m-1}$ 的，远大于正解的 $2^m$。

前者的冗余主要体现在这里：例如 $(2,10100),(3,10100),(5,10010),(6,10010)$ 在后者仅需要用 $100100$ 一个状态表示。

冗余的原因也非常简单：当前枚举的列下标对答案的影响是平凡的（无论状态是 $<$ 还是 $\le$）

由于我看了题解，所以不加思考地获得了正解的构造方式，这显然不怎么阳间。我们考虑通过纯计算得出真正的状态空间。

对于两个冗余状态 $(i,S),(j,S)$，如果在 $S$ 中，$i,j$ 下标都与同一个 $0$ 连续段（可能为空）相邻（或者在其中），那么它们是等价的。换句话说，有 $m-\operatorname{popcount}(S)+1$ 个本质不同的状态。所以可以推出式子：

$$
\begin{aligned}
&\sum_S(m-\operatorname{popcount}(S)+1)\\
=~&(m+1)2^{m-1}-\sum_S\operatorname{popcount}(S)\\
=~&(m+1)2^{m-1}-(m-1)2^{m-1}\\
=~&2^m\\
\end{aligned}
$$

于是我们得到了和正解状态相同的状态空间。