给一棵树，每个点有点权，每次操作可以断掉树上的若干条边，您可以操作任意次（也可以不操作），要求每次操作后，剩下的每个连通块点权和相等。求可行的操作序列数。

$1\le n\le10^6$，$1\le a_i\le10^9$。

---

考虑建一张图，每一个树的状态代表图中的一个点，那么我们将原问题转化为了，求图中以 $1$ 为起点的路径条数。

然后观察到一个性质：对于整数 $v$，连通块数为 $v$ 的状态数至多只有一个……

那么我们可以推出：对于整数 $p,q$，如果 $p\mid q$，那么若状态 $q$ 存在，则状态 $p$ 存在，且 $p$ 可以通过一次操作到达 $q$。

考虑设 $f(x)$ 为从 $1$ 到 $x$ 的路径数，那么有 $f(x)=[x\text{ exists}]\sum_{y\mid x}f(y)$。

于是我们需要得出每个状态的存在性。

考虑一个暴力做法：我们对于每个 $v$，判断状态 $v$ 是否存在。判断方法也比较显然：设 $1$ 为根，$S$ 为整棵树的点权和，如果 $v$ 是 $S$ 的约数，且正好有 $v$ 个子树的点权和可以被 $\frac Sv$ 整除，那么这个状态存在（且唯一）。

设 $\operatorname{sz}(x)$ 为 $x$ 子树的点权和，$g(v)$ 为有多少个子树的点权和可以被 $\frac Sv$ 整除，那么可以写出 $g(v)$ 和答案的式子：

$$
\begin{aligned}
g(v)=&\sum_{i=1}^n\left[\tfrac Sv\mid\operatorname{sz}(i)\right]\\
f(x)=&[v\mid S][g(v)=v]\sum_{y\mid x}f(y)
\end{aligned}
$$

然后考虑加速 $g$ 的计算。

$$
\begin{aligned}
\operatorname{sz}(i)&\equiv0\pmod{\frac Sv}\\
\operatorname{sz}(i)&=t\frac Sv\\
v&=t\frac S{\operatorname{sz}(i)}\\
\end{aligned}
$$

由于 $v$ 必须是整数，所以有 $\frac S{\gcd(S,\operatorname{sz}(i))}\mid v$。

于是对于每个 $\operatorname{sz}(i)$，我们枚举 $\frac S{\gcd(S,\operatorname{sz}(i))}$ 的倍数就好了（$\frac S{\gcd(S,\operatorname{sz}(i))}$ 相同的时候一起处理）。最坏情况下每个点的点权为 $1$，树是一条链，此时复杂度为 $O(n\ln n)$。于是总复杂度为 $O(n(\ln n+\log10^{15}))$。（$\log10^{15}$ 为 gcd 复杂度）

---

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define int long long

const int N = 1e6 + 61, P = 1e9 + 7;

int n, sz[N], p[N], f[N], g[N], c[N], S, ans;
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", sz + i);
	for (int i = 2; i <= n; i++) scanf("%lld", p + i);
	for (int i = n; i >= 2; i--) i[p][sz] += i[sz];
	S = sz[1];
	for (int i = 1; i <= n; i++) {
		int t = S / std::__gcd(S, sz[i]);
		if (t <= n) c[t]++;
	}
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i) f[j] += c[i];
	g[1] = 1;
	for (int i = 1; i <= n; i++)
		if (S % i == 0 && f[i] == i) {
			ans += g[i];
			for (int j = 2 * i; j <= n; j += i) g[j] += g[i];
		}
	printf("%lld\n", ans % P);
}
```