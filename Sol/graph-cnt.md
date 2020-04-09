## 有标号有根树

$$
\begin{aligned}
\hat F(x)&=x\operatorname{EIJ}\hat F(x)\\
\hat F(x)&=x\exp\hat F(x)\\
\end{aligned}
$$

然后可以证明这个就是 $n^{n-1}$……？

## 有标号无根树

就是上面的除以 $n$

然后就是 $n^{n-2}$……？

## 无标号有根树

$$
\begin{aligned}
F(x)&=x\operatorname{EIK}F(x)\\
F(x)&=x\exp\sum_{i=1}^\infty\frac{F(x^i)}i\\
\end{aligned}
$$

未完待续

## 有标号弱连通 DAG

设 $f(n)$ 为 $n$ 个点的有标号 DAG 数量，$h(n)$ 为 $n$ 个点的有标号弱连通 DAG 数量。

$$
\begin{aligned}
f(n)&=\sum_{k=1}^n(-1)^{k+1}\binom nk2^{k(n-k)}f(n-k)\\
&=\sum_{k=1}^n(-1)^{k+1}\frac{n!}{k!(n-k)!}2^{k(n-k)}f(n-k)\\
&=n!\sum_{k=1}^n\frac{(-1)^{k+1}}{k!}\frac{f(n-k)}{(n-k)!}2^{\frac{n^2-k^2-(n-k)^2}2}\\
&=n!\sqrt2^{n^2}\sum_{k=1}^n\frac{(-1)^{k+1}}{k!2^{k^2}}\frac{f(n-k)}{(n-k)!\sqrt2^{(n-k)^2}}\\
\frac{f(n)}{n!\sqrt2^{n^2}}&=\sum_{k=1}^n\frac{(-1)^{k+1}}{k!2^{k^2}}\frac{f(n-k)}{(n-k)!\sqrt2^{(n-k)^2}}\\
&\text{let}~F(x)=\sum_{i=0}^n\frac{f(i)}{i!\sqrt2^{i^2}}x^i,G(x)=\sum_{i=1}^n\frac{(-1)^{i+1}}{i!\sqrt2^{i^2}}x^i,\text{therefore}\\
F(x)&=F(x)G(x)+1\\
F(x)&=\frac1{1-G(x)}\\
&\text{let}~\hat F(x)=\sum_{i=0}^n\frac{f(i)}{i!}x^i,\hat H(x)=\sum_{i=0}^n\frac{h(i)}{i!}x^i,\text{therefore}\\
\hat H(x)&=\ln\hat F(x)
\end{aligned}
$$
