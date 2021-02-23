设 $f_0=0$，$f_1=1$，$f_i=f_{i-1}+f_{i-2}$。那么显然对于 $i>1$，有 $F_i=(a\cdot f_{i-1}+b\cdot f_i)\bmod m$。

$$
F_i\equiv a\cdot f_{i-1}+b\cdot f_i\equiv0\pmod m
$$

如果 $m$ 是质数，那么我们可以直接将式子化成 $\frac{f_i}{f_{i-1}}\equiv-\frac ab\pmod p$。由于 $f$ 的周期是 $O(m)$ 的，所以可以直接记录每个 $\frac{f_i}{f_{i-1}}$ 第一次出现的位置。

对于 $m$ 是合数的情况，$b^{-1},f_{i-1}^{-1}$ 不一定存在。

$$
\begin{aligned}
a\cdot f_{i-1}+b\cdot f_i&\equiv0\pmod m\\
\frac{a\cdot f_{i-1}}{\gcd(a,b,p^k)}+\frac{b\cdot f_i}{\gcd(a,b,p^k)}&\equiv0\enspace\left(\!\bmod{\frac m{\gcd(a,b,p^k)}}\right)\\
a'\cdot f_{i-1}+b'\cdot f_i&\equiv0\pmod{m'}\\
\end{aligned}
$$

其中 $t=\gcd(a,b,p^k)$，$a'=a/t$，$b'=b/t$，$m'=m/t$。但是 $\gcd(b',m')$ 还是可能大于 $1$。

设 $p=\gcd(b',m')$，$q=\gcd(a',m')$，$p'=\gcd(f_{i-1},m')$，$q'=\gcd(f_i,m')$。

因为 $\gcd(a',b',m')=1,\gcd(f_{i-1},f_i)=1$，所以 $\gcd(p,q)=\gcd(p',q')=1$。可得：

$$
\begin{aligned}
&\begin{cases}
pq\mid a'\cdot f_{i-1}+b'\cdot f_i\\
p'q'\mid a'\cdot f_{i-1}+b'\cdot f_i\\
\end{cases}\\
&\begin{cases}
q\mid a'\cdot f_{i-1}+b'\cdot f_i\\
q'\mid a'\cdot f_{i-1}+b'\cdot f_i\\
\end{cases}\\
&q\perp b',\quad q'\perp f_{i-1}\\
&\begin{cases}
q\mid f_i\\
q'\mid a'\\
\end{cases}\\
&\begin{cases}
q\mid\gcd(f_i,m')\\
q'\mid\gcd(a',m')\\
\end{cases}\\
&\begin{cases}
\gcd(a',m')\mid\gcd(f_i,m')\\
\gcd(f_i,m')\mid\gcd(a',m')\\
\end{cases}\\
&q=\gcd(a',m')=\gcd(f_i,m')
\end{aligned}
$$

同理可得 $p=\gcd(b',m')=\gcd(f_{i-1},m')$。

$$
\begin{aligned}
a'\cdot f_{i-1}+b'\cdot f_i&\equiv0\pmod{m'}\\
\frac{a'}q\frac{f_{i-1}}p+\frac{b'}{p}\frac{f_i}q&\equiv0\pmod{m'}\\
\frac{f_i/q}{f_{i-1}/p}&\equiv-\frac{a'/q}{b'/p}\enspace\left(\!\bmod{\frac{m'}{pq}}\right)\\
\end{aligned}
$$

那么我们实际上只需要枚举 $m'$，然后把 $\frac{f_i/q}{f_{i-1}/p}$ 丢到 map 里就好了。

复杂度为 $O(n\log m+\sigma(m)\log m)=O(n\log m+m\log m\log\log m)$。

---

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

typedef long long L;
const int N = 6e5 + 56;

void exgcd(int a, int b, int& x, int& y) {
	if (!b)
		x = 1, y = 0;
	else
		exgcd(b, a % b, y, x), y -= a / b * x;
}
int inv(int a, int m) {
	int x, y;
	exgcd(a, m, x, y);
	return (x % m + m) % m;
}

struct _ {
	int p, q, v;
	bool operator<(const _& rhs) const {
		return p < rhs.p || (p == rhs.p && (q < rhs.q || (q == rhs.q && v < rhs.v)));
	}
};

int n, m, a, b, f[N];
std::map<_, int> mp[N];
signed main() {
	scanf("%d%d", &n, &m);
	f[1] = 1;
	for (int m0 = 2; m0 <= m; m0++)
		if (m % m0 == 0)
			for (int i = 2;; i++) {
				f[i] = (f[i - 1] + f[i - 2]) % m0;
				if (f[i] == 1 && f[i - 1] == 0) break;
				int p = std::__gcd(f[i - 1], m0), q = std::__gcd(f[i], m0);
				int m1 = m0 / p / q;
				_ frac = {p, q, int((L)(f[i] / q) * inv(f[i - 1] / p, m1) % m1)};
				if (!mp[m0].count(frac)) mp[m0][frac] = i;
			}
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a, &b);
		if (!a) {
			puts("0");
			continue;
		}
		if (!b) {
			puts("1");
			continue;
		}
		int t = std::__gcd(std::__gcd(a, b), m), m0 = m / t, m1;
		a /= t, b /= t;
		int p = std::__gcd(b, m0), q = std::__gcd(a, m0);
		m1 = m0 / p / q;
		_ frac = {p, q, int((m1 - (L)(a / q) * inv(b / p, m1) % m1) % m1)};
		if (mp[m0].count(frac))
			printf("%d\n", mp[m0][frac]);
		else
			puts("-1");
	}
}
```