# 定义

这是对计算划分对象的方式的变换的概括。

假设我们有不同颜色和尺寸的盒子。

序列 $\{a_n\}$ 表示容纳 $n$ 个球的盒子可以涂成的颜色数。变换后的序列 $\{b_n\}$ 表示把 $n$ 个球放到任意多个盒子里的方案数，但要遵循下列规则：

**盒子的顺序：**

- **A. 线性 (ordered):** 盒子从左到右排成一行；
- **B. 线性，可翻转 (reversible):** 盒子排成一行，但翻转视为相同的；
- **C. 循环 (necklace):** 盒子排成一个环，即轮转视为相同的；
- **D. 循环，可翻转 (bracelet):** 盒子排成一个环，但轮转和翻转都视为相同的；
- **E. 无序 (unordered):** 盒子无序，即任意重排都视为相同的。

**区分规则：**

- **F. 大小 (size)**: 任意两个盒子都能根据大小（指球的个数，下同）来区分，即大小两两不同;
- **G. 元素 (element)**: 任意两个盒子都能由大小和颜色区分，即不存在两个盒子大小和颜色都相同；
- **H. Identity**: 任意两个盒子都能根据大小、颜色和位置区分（具体见下）;
- **I. 无限制 (indistinct):** 没有这一类限制。

**标号规则：**

- **J. 有标号 (labeled):** 球有标号；
- **K. 无标号 (unlabeled):** 球没有标号。

## 术语

设 $\operatorname{XXX_k}$ 代表正好有 $k$ 个盒子的 XXX 变换。

# 算法

设 $\{a_n\}$ 为输入的序列，$\{b_n\}$ 为输出的序列。$A(x),B(x)$ 是它们的 OGF，$\hat A(x),\hat B(x)$ 是它们的 EGF。

$\displaystyle(\operatorname{XXX}a)_n=\sum_{k=1}^n(\operatorname{XXX_k}a)_n$。

## AIK = INVERT

盒子有序，无区分规则，球无标号。

$$\operatorname{AIK}A(x)=\sum_{i=0}^\infty A^i(x)=\frac1{1-A(x)}$$

$$\operatorname{AIK_k}A(x)=A^k(x)$$

## EIJ = EXP

盒子无序，无区分规则，球有标号。

$$\operatorname{EIJ}\hat A(x)=\exp\hat A(x)$$

### 例题

- 有标号无向连通图计数（城市规划）
- 有标号有根树计数

## EIK = EULER

盒子无序，无区分规则，球无标号。

$$
\begin{aligned}
\operatorname{EIK}A(x)=&\prod_{i=1}^\infty\frac1{(1-x^i)^{a_i}}\\
=&\exp\left[\sum_{i=1}^\infty\ln\frac1{(1-x^i)^{a_i}}\right]\\
=&\exp\left[\sum_{i=1}^\infty-a_i\ln(1-x^i)\right]\\
=&\exp\left(\sum_{i=1}^\infty a_i\sum_{j=1}^\infty\frac{x^{ij}}j\right)\\
=&\exp\left(\sum_{j=1}^\infty\frac1j\sum_{i=1}^\infty a_ix^{ij}\right)\\
=&\exp\left(\sum_{j=1}^\infty\frac{F(x^j)}j\right)\\
\end{aligned}
$$

Note：完全背包

### 例题

- 完全背包方案数计数（付公主的背包）
- 无标号有根树计数
- 无标号无根树计数（P5900）