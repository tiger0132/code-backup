给 $n,k$，对于每个 $j=1\sim k$，求排列 $1,2,\ldots,n$ 进行 $j$ 次交换之后可以得到的排列数量。答案对 $10^9+7$ 取模。

$2\le n\le10^9$，$1\le k\le200$。

---

考虑设 $f(i,j)$ 代表长度为 $i$ 的排列，**最少**经过 $j$ 次交换可以变回 $1,2,\ldots,i$，那么对于某个 $j$，输出的答案应该是 $f(n,j)+f(n,j-2)+\ldots$。

然后考虑转移。考虑将长度为 $i-1$ 的排列拓展到长度为 $i$ 的，那么有两种情况：

- 最后一位是 $i$，那么所需的交换次数不变。即 $f(i,j)\gets f(i-1,j)$。
- 最后一位不是 $i$，那么所需的交换次数 $+1$，且可以将 $i$ 放在前 $i-1$ 个位置中的任意一个。即 $f(i,j)\gets(i-1)\cdot f(i-1,j-1)$。

那么得到转移 $f(i,j)=f(i-1,j)+(i-1)f(i-1,j-1)$，$f(0,0)=1$。直接矩阵快速幂即可通过本题。复杂度 $O(k^3\log n)$。

# 优化尝试

设 $F_i(x)=\sum_jf(i,j)x^j$，那么可得 $F_i(x)=F_{i-1}(x)\cdot(1+(i-1)x)$，$F_0(x)=1$。即

$$
F_n(x)=\prod_{i=1}^{n-1}(1+ix)
$$

然后并不能优化……

# 优化 2

考虑求出有 $n-j$ 个置换环的排列数的 EGF：

$$
\begin{aligned}
&n![x^n]\left(\frac1{(n-j)!}\cdot(-\ln(1-x))^{n-j}\right)\\
=&n![x^n]\left(\frac1{(n-j)!}\cdot(-\ln(1-x))^{n-j}\right)\\
=&n^{\underline j}[x^n](-\ln(1-x))^{n-j}\\
=&n^{\underline j}[x^j]\left(-\frac{\ln(1-x)}x\right)^{n-j}\\
\end{aligned}
$$

我们要做的是对 $j=0\sim k$ 求出上式的值。

设 $G(x)=\left(-\frac{\ln(1-x)}x\right)^{n-k}$，$D(x)=-\ln(1-x)$，那么：

$$
\begin{aligned}
&n^{\underline j}[x^j]\left(-\frac{\ln(1-x)}x\right)^{n-j}\\
=&n^{\underline j}[x^j]G(x)\left(-\frac{\ln(1-x)}x\right)^{k-j}\\
=&n^{\underline j}[x^k]G(x)\cdot D(x)^{k-j}\\
\end{aligned}
$$

其中 $G(x)$ 可以通过 $\ln-\exp$ 在 $O(k^2)$ 时间算出。

注意到 $(D(x)^{k-j})'=(k-j)D'(x)\cdot D(x)^{k-j-1}$，且 $D'(x)=\frac1{1-x}$，所以我们可以在 $O(k)$ 时间计算出这个卷积，在 $O(k^2)$ 时间内完成 $D(x)^0,D(x)^1,\ldots,D(x)^{k-1}$ 的预处理。

最后对每个 $j$ 计算答案的复杂度也是 $O(k^2)$，所以总复杂度 $O(k^2)$。