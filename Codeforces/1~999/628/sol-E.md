给定 $n,m$，求有多少个每一项都在 $[1,2^m)$ 中，且长为 $n$ 的序列 $a_1,a_2,\ldots,a_n$ 满足，设 $b_i=a_1\mid a_2\mid\ldots\mid a_i$，那么 $b_i$ 严格递增。答案对 $10^9+7$ 取模。

注意：这里的 $m$ 在原题面中是 $k$。

$1\le n\le10^{18}$，$1\le m\le3\cdot10^4$。

---

首先显然当 $n>m$ 的时候答案为 $0$。

设 $f(i,j)$ 为前 $i$ 项，$\operatorname{popcnt}(b_i)=j$ 的方案数。那么有：

$$
\begin{aligned}
f(i,j)&=\sum_{k=1}^{j-1}f(i-1,k)\binom jk2^k\\
j![x^j/j!]F_i(x)&=\sum_{k=1}^{j-1}k![x^k/k!]F_{i-1}(x)\frac{j!}{k!(j-k)!}2^k\\
[x^j/j!]F_i(x)&=\sum_{k=1}^{j-1}[(2x)^k/k!]F_{i-1}(x)\frac1{(j-k)!}\\
F_i(x)&=(e^x-1)F_{i-1}(2x)
\end{aligned}
$$

其中 $F_i(x)$ 为 $f(i,*)$ 的 EGF，$F_0(x)=1$。

那么我们会发现 $F_1(x)=e^x-1$，$F_2(x)=(e^x-1)(e^{2x}-1)$，……，$F_n(x)=\prod_{i=0}^n(e^{2^ix}-1)$。

考虑对 $F_i(x)=(e^x-1)F_{i-1}(2x)$ 展开 $j$ 次，那么我们会得到 $F_i(x)=\prod_{k=0}^j(e^{2^kx}-1)F_{i-j}(2^jx)$。取 $i=2j$，则有

$$
\begin{aligned}
F_{2j}(x)&=\prod_{k=0}^j(e^{2^kx}-1)F_j(2^jx)\\
&=F_j(x)F_j(2^jx)
\end{aligned}
$$

那么可以倍增的算出 $F_n(x)$。由于多项式次数为固定的 $m$，所以总复杂度为 $O(m\log m\log n)$。