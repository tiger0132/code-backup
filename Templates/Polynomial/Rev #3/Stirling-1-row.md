$$
\begin{aligned}
& F(x+n) \\
= & \sum_{i=0}^na_i(x+n)^i \\
= & \sum_{i=0}^na_i\sum_{j=0}^i\binom ijx^jn^{i-j} \\
= & \sum_{j=0}^n\sum_{i=j}^na_i\frac{i!}{j!(i-j)!}x^jn^{i-j} \\
= & \sum_{j=0}^n\frac{x^j}{j!}\sum_{i=j}^na_ii!\frac{n^{i-j}}{(i-j)!} \\
= & \sum_{i=0}^n\frac{x^i}{i!}\sum_{j=i}^na_jj!\frac{n^{j-i}}{(j-i)!} \\
\end{aligned}
$$