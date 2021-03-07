# 做法 1

考虑矩阵树。我们用变元 $x$ 来标记与给定树重复的边数。具体来说，我们认为给定的是一张完全图，其中树边的边权为 $x$，非树边的边权为 $1$。那么所有生成树的边权乘积的和的多项式系数就是我们要求的答案。

直接在矩阵树时暴力算卷积是 $O(n^5)$ 的，显然过不了。一个自然的想法是计算出多项式的点值最后再插值，然后这样显然就可以做到 $O(n^4)$ 了，可以通过本题。

# 做法 2

假设我们求出，对于选择原树中边的子集的所有方式下，剩余边任选的生成树个数，那么我们就能得到「至少选出 $k$ 条边」的方案数，然后二项式反演一下就能得到答案了。

设选出了 $k$ 个连通块，大小分别为 $s_1,s_2,\ldots,s_k$，那么生成树个数为：

$$
\begin{aligned}
&\begin{vmatrix}
s_1(n-s_1)&-s_1s_2&\dots&s_1s_{k-1}\\
-s_1s_2&s_2(n-s_2)&\dots&s_2s_{k-1}\\
\vdots&\vdots&\ddots&\vdots\\
s_1s_{k-1}&s_2s_{k-1}&\dots&s_{k-1}(n-s_{k-1})
\end{vmatrix}\\
=&\prod_is_i\begin{vmatrix}
(n-s_1)&-s_2&\dots&s_{k-1}\\
-s_1&(n-s_2)&\dots&s_{k-1}\\
\vdots&\vdots&\ddots&\vdots\\
s_1&s_2&\dots&(n-s_{k-1})
\end{vmatrix}\\
=&n^{k-2}\prod_is_i
\end{aligned}
$$

考虑 $\prod_is_i$ 的组合意义：先将树分成若干个连通块，然后在每个连通块里标记一个点的方案数。

于是可以设 $f(x,i,0/1)$ 为 $x$ 子树里，有 $i$ 个连通块，$x$ 所在的连通块有没有标记点的方案数。

$$
\begin{aligned}
&f(x,i+j,0)\gets f(x,i,0)\cdot(f(nx,j,0)+f(nx,j,1))\\
&f(x,i+j,1)\gets f(x,i,1)\cdot(f(nx,j,0)+f(nx,j,1))+f(x,i,0)\cdot f(nx,j,1)\\
\end{aligned}
$$

然后二项式反演一下。

设 $f_i$ 为至少重复 $i$ 条边的答案，$g_i$ 为正好重复 $i$ 条边的答案，那么 $f_i=n^{n-i-2}f(1,n-i,1)$。

$$
\begin{aligned}
G(x+1)&=F(x)\\
G(x)&=F(x-1)\\
&=\sum_{i\ge0}f_i(x-1)^i\\
&=\sum_{i\ge0}\sum_{j\le i}\binom ijx^j(-1)^{i-j}f_i\\
&=\sum_{j\ge0}x^j\sum_{i\ge j}\binom ij(-1)^{i-j}f_i\\
g_n&=\sum_{i\ge n}\binom in(-1)^{i-n}f_i\\
\end{aligned}
$$

---

# 做法 1

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 1e2 + 21, P = 1e9 + 7;
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
	Z operator-() const { return norm(-x); }
	Z operator*(const Z& rhs) const { return (L)x * rhs.x % P; }
	void operator+=(const Z& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const Z& rhs) { norm2(x -= rhs.x); }
	void operator*=(const Z& rhs) { x = (L)x * rhs.x % P; }
};
Z pw(Z x, int y) {
	Z r = 1;
	for (; y; y >>= 1, x *= x)
		if (y & 1) r *= x;
	return r;
}

Z g[N][N];
int n;
Z det() {
	Z ret = 1;
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; !g[i][i].x && j < n; j++)
			if (g[j][i].x) ret = -ret, std::swap(g[i], g[j]);
		for (int j = i + 1; j < n; j++) {
			Z d = g[j][i] * pw(g[i][i], P - 2);
			for (int k = i; k < n; k++) g[j][k] -= g[i][k] * d;
		}
		ret = ret * g[i][i];
	}
	return ret;
}

Z dif[N][N], coef[N][N], ans[N];
int ed[N][N];
int main() {
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		ed[x][y] = ed[y][x] = 1;
	}
	for (int k = 0; k < n; k++) {
		for (int i = 1; i <= n; i++) g[i][i] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i != j) {
					int v = ed[i][j] ? k ? P - k : 0 : P - 1;
					g[i][i] -= v, g[i][j] = v;
				}
		dif[0][k] = det();
	}
	coef[1][1] = 1;
	for (int i = 2; i < n; i++)
		for (int j = 1; j <= i; j++)
			coef[i][j] = coef[i - 1][j - 1] - coef[i - 1][j] * (i - 1);
	ans[0] = dif[0][0];
	Z fac = 1;
	for (int i = 1; i < n; i++) {
		Z inv = pw(fac = fac * i, P - 2);
		for (int j = i; j < n; j++) dif[i][j] = dif[i - 1][j] - dif[i - 1][j - 1];
		for (int j = 1; j <= i; j++) ans[j] += dif[i][i] * coef[i][j] * inv;
	}
	for (int i = 0; i < n; i++) printf("%d%c", ans[i].x, " \n"[i == n - 1]);
}
```

# 做法 2

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long L;
const int N = 1e2 + 21, P = 1e9 + 7;
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
	Z operator-() const { return norm(-x); }
	Z operator*(const Z& rhs) const { return (L)x * rhs.x % P; }
	void operator+=(const Z& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const Z& rhs) { norm2(x -= rhs.x); }
	void operator*=(const Z& rhs) { x = (L)x * rhs.x % P; }
};
Z pw(Z x, int y) {
	Z r = 1;
	for (y = (y + P - 1) % (P - 1); y; y >>= 1, x *= x)
		if (y & 1) r *= x;
	return r;
}

Z f[N][N][2], tmp[N][2];
std::vector<int> g[N];
int n, sz[N];
void dfs(int x, int p) {
	f[x][0][0] = f[x][1][1] = 1;
	x[sz] = 1;
	for (int nx : x[g])
		if (nx != p) {
			dfs(nx, x);
			memset(tmp, 0, sizeof tmp);
			for (int i = 0; i <= x[sz]; i++)
				for (int j = 0; j <= nx[sz]; j++) {
					tmp[i + j][0] += f[x][i][0] * (f[nx][j][0] + f[nx][j][1]);
					tmp[i + j][1] += f[x][i][1] * (f[nx][j][0] + f[nx][j][1]) +
									 f[x][i][0] * f[nx][j][1];
				}
			x[sz] += nx[sz];
			memcpy(f[x], tmp, sizeof tmp);
		}
}

Z C[N][N], t[N], ans[N];
int main() {
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		x[g].push_back(y);
		y[g].push_back(x);
	}
	dfs(1, -1);
	for (int i = 0; i <= n; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	for (int i = 0; i < n; i++) t[i] = f[1][n - i][1] * pw(n, n - i - 2);
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			if ((j - i) & 1)
				ans[i] -= C[j][i] * t[j];
			else
				ans[i] += C[j][i] * t[j];
	for (int i = 0; i < n; i++) printf("%d%c", ans[i].x, " \n"[i == n - 1]);
}
```