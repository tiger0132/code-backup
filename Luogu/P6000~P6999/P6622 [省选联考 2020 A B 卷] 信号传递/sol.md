考虑从头到尾依次填写 $\rho$。

![](http://d.akioi.ml:8201/index.php/apps/files_sharing/publicpreview/4diqKTfKbPTgBbf?fileId=16905&file=/71/1.png&x=1920&y=1080)

设 $f(S)$ 为 $S$ 已经被填进 $\rho$ 中，红线左边部分的**蓝色、橙色、黄色边**的最小代价。

然后考虑一下加入 $S$ 之外的某个数 $x$ 对答案的贡献。

为了方便描述，设 $\operatorname{cnt}(x\to S)$ 代表 $\sum_i[S_{i-1}=x][S_i\in S]$，$\operatorname{cnt}(S\to x),\operatorname{cnt}(S\to T)$ 等同理。

- $\footnotesize\color{blue}\text{蓝色}$ 和 $\footnotesize\color{orange}\text{橙色}$ 的贡献已经被统计，$\footnotesize\color{lightgreen}\text{绿色}$ 的贡献暂时无需统计。
- $\footnotesize\color{yellow}\text{黄色}$：所有从 $S$ 到 $U\setminus S$ 的路径。贡献为 $\operatorname{cnt}(S\to(U\setminus S))$。
- $\footnotesize\color{purple}\text{紫色}$：所有从 $x$ 到 $S$ 的路径，和所有从 $(U\setminus S\setminus\{x\})$ 的路径。贡献为 $k\cdot x\cdot(\operatorname{cnt}(x\to S)+\operatorname{cnt}((U\setminus S\setminus\{x\})\to x))$。

*另外一种可行的思路是把 $i<j$ 的贡献也差分，这样就不需要计算集合到集合的路径数，这是我在考场上使用的方法。这里不使用这种方法。*

设 $g(S)=\operatorname{cnt}(S\to(U\setminus S))$，于是我们得出 DP 转移：

$$
f(S)+g(S)+k\cdot x\cdot (\operatorname{cnt}(x\to S)+\operatorname{cnt}((U\setminus S\setminus\{x\})\to x)))\to_{\min}f(S\cup\{x\})
$$

于是我们得到了一个时间复杂度 $O(m2^m)$ 的优秀做法，然后我们来计算一下空间占用。

$f,g(S),\operatorname{cnt}(x\to S),\operatorname{cnt}(S\to x)$ 的总空间占用为 $(2^{23}+2^{23}+23\cdot 2^{23})\cdot4\operatorname{B}/2^{20}=1536\operatorname{MiB}$，这显然是不可接受的。

设 $\operatorname{high}(S)=S/2^{12}$，$\operatorname{low}(S)=S\bmod2^{12}$，那么 $\operatorname{cnt}(x\to S)=\operatorname{cnt}(x\to\operatorname{high}(S))+\operatorname{cnt}(x\to\operatorname{low}(S))$。于是我们只需要预处理出两个大小可以忽略不记的数组就可以了。同理可以预处理出 $f(S\to x)$。

于是空间复杂度优化到 $O(2^m)$，具体空间占用为 $(2^{23}+2^{23})\cdot4/2^{20}=64\operatorname{MiB}$，可以轻松通过本题。

最后是 $g$ 数组的预处理。显然有：

$$
g(S)=g(S\setminus\{\min S\})-\operatorname{cnt}((S\setminus\{\min S\})\to(\min S))+\operatorname{cnt}((\min S)\to(U\setminus S))
$$

**这个故事告诉我们：不要无聊绕远路。**

---

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#define popcnt(S) __builtin_popcount(S)
#define ctz(S) __builtin_ctz(S)

const int N = 1e5 + 51, M = 24, K = 1 << M, U0 = (1 << 12) - 1;

int c0[M][U0 + 1], c1[M][U0 + 1], c2[M][U0 + 1], c3[M][U0 + 1];
int s[N], g[K], rec[M][M], f[K];
int n, m, k, U;
inline int cnt1(int x, int S) {
	int hi = S >> 12, lo = S & U0;
	return c0[x][lo] + c1[x][hi];
}
inline int cnt2(int S, int x) {
	int hi = S >> 12, lo = S & U0;
	return c2[x][lo] + c3[x][hi];
}
int main() {
	scanf("%d%d%d", &n, &m, &k), U = (1 << m) - 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", s + i), s[i]--;
		if (i > 1) rec[s[i - 1]][s[i]]++;
	}
	for (int i = 0; i < m; i++)
		for (int S = 1; S <= U0; S++) {
			int x0 = ctz(S), x1 = x0 + 12;
			c0[i][S] = c0[i][S & (S - 1)] + rec[i][x0];
			c1[i][S] = c1[i][S & (S - 1)] + rec[i][x1];
			c2[i][S] = c2[i][S & (S - 1)] + rec[x0][i];
			c3[i][S] = c3[i][S & (S - 1)] + rec[x1][i];
		}
	for (int S = 1; S <= U; S++) {
		int S0 = S & (S - 1), x = ctz(S);
		g[S] = g[S0] + cnt1(x, U ^ S) - cnt2(S0, x);
	}
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for (int S = 0; S < U; S++)
		for (int i = 0; i < m; i++)
			if (!((S >> i) & 1))
				f[S | (1 << i)] = std::min(
					f[S | (1 << i)],
					f[S] + g[S] +
						k * (popcnt(S) + 1) * (cnt1(i, S) + cnt2(U ^ S ^ (1 << i), i)));
	printf("%d\n", f[U]);
}
```