根据 $\varphi*1=\operatorname{id}$，可以推出下面的式子：

$$
\begin{aligned}
&\sum_T\left(\sum_{e\in T}w_e\right)\left(\gcd_{e\in T}w_e\right)\\
=&\sum_T\left(\sum_{e\in T}w_e\right)\sum_{d\mid\gcd_{e\in T}w_e}\varphi(d)\\
=&\sum_T\left(\sum_{e\in T}w_e\right)\sum_{d\mid w_{e_1},d\mid w_{e_2},\ldots}\varphi(d)\\
=&\sum_d\varphi(d)\sum_{\substack{T\\d\mid w_{e_1},d\mid w_{e_2},\ldots}}\left(\sum_{e\in T}w_e\right)\\
\end{aligned}
$$

那么我们只需要求出所有生成树的权值和的和就好了。

注意到矩阵树定理只能计算生成树权值乘积的和，所以我们要想一个办法把乘化成加。

一个显然的想法是利用 $x^a\cdot x^b=x^{a+b}$。如果我们能有办法得到最终关于 $x$ 的多项式的各项系数，设其为 $a_i$，那么答案就是 $\sum i\cdot a_i$。

设原多项式为 $F(x)=\sum_ia_ix^i$，那么您会惊讶地发现 $[x^1]F(e^x)$ 就是我们要求的玩意。

于是我们把图的边权设成 $e^{wx}\equiv1+wx\pmod{x^2}$，计算出行列式的一次项系数就好了。

但是有个坑：高消在找不到常数项不为 $0$ 的项时，可以用一次项不为 $0$ 的。这时需要特判除法。

---

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long L;
const int N = 33, M = 1e3 + 31, K = 2e5 + 52, P = 998244353;

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
struct poly {
	Z x, y;
	inline poly operator+(const poly& r) const { return {x + r.x, y + r.y}; }
	inline void operator+=(const poly& r) { x += r.x, y += r.y; }
	inline poly operator-(const poly& r) const { return {x - r.x, y - r.y}; }
	inline void operator-=(const poly& r) { x -= r.x, y -= r.y; }
	inline poly operator*(const poly& r) const { return {x * r.x, x * r.y + y * r.x}; }
	inline poly operator/(const poly& r) const {
		Z inv = pw(r.x, P - 2);
		return {x * inv, (y * r.x - x * r.y) * inv * inv};
	}
	inline poly operator!() const { return {y, 0}; }
};

poly g[N][N];
int n, m;
Z det() {
	poly ret{1, 0};
	Z f = 1;
	for (int i = 1; i < n; i++) {
		if (g[i][i].x.x) goto skip;
		for (int j = i + 1; j < n; j++)
			if (g[j][i].x.x) {
				f = -f, std::swap(g[i], g[j]);
				goto skip;
			}
		if (g[i][i].y.x) goto skip;
		for (int j = i + 1; j < n; j++)
			if (g[j][i].y.x) {
				f = -f, std::swap(g[i], g[j]);
				goto skip;
			}
	skip:
		for (int j = i + 1; j < n; j++) {
			poly p = g[i][i], q = g[j][i];
			if (!p.x.x) p = !p, q = !q;
			poly d = q / p;
			for (int k = i; k < n; k++) g[j][k] -= g[i][k] * d;
		}
		ret = ret * g[i][i];
	}
	return ret.y * f;
}

int phi[K], p[K], cnt;
bool f[K];
void init() {
	f[1] = true, phi[1] = 1;
	for (int i = 2; i < K; i++) {
		if (!f[i]) p[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && i * p[j] < K; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				phi[i * p[j]] = phi[i] * (p[j] - 1);
			else {
				phi[i * p[j]] = phi[i] * p[j];
				break;
			}
		}
	}
}

int fa[N], cc;
int fd(int x) { return x[fa] ? x[fa] = fd(x[fa]) : x; }
void mg(int x, int y) {
	if ((x = fd(x)) != (y = fd(y))) x[fa] = y, cc--;
}

int x[M], y[M], z[M];
Z ans;
int main() {
	init();
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", x + i, y + i, z + i);

	for (int i = 1; i < K; i++) {
		memset(fa, 0, sizeof fa), cc = n;
		for (int j = 1; j <= m; j++)
			if (!(z[j] % i)) mg(x[j], y[j]);
		if (cc > 1) continue;
		memset(g, 0, sizeof g);
		for (int j = 1; j <= m; j++)
			if (!(z[j] % i)) {
				g[x[j]][x[j]] += {1, z[j]};
				g[y[j]][y[j]] += {1, z[j]};
				g[x[j]][y[j]] -= {1, z[j]};
				g[y[j]][x[j]] -= {1, z[j]};
			}
		Z w = det();
		ans += w * phi[i];
	}
	printf("%d", ans.x);
}
```