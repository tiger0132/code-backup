# 1119E Pavel and Triangles
# 1036E Covered Points
# 993E Nikita and Order Statistics

## 题意

给一个序列 $a_i$ 和一个数 $x$，对于 $k\in[0,n]$，求包含 $k$ 个 $<x$ 的数的子段个数。

$1\le n\le2\cdot10^5$。

## 解法

前缀和，然后就转化成求 $s_i-s_j=k,j<i$ 的对数，然后直接卷就好了。注意要特判 $0$，然后模数最好取一个大点的，比如我用的是 $75161927681$。

# 1096G Lucky Ticket

## 题意

有 $k$ 个 $0\sim9$ 的数字，求有多少种方法用它们组成一个长为 $n$（偶数）的序列，每种数字可以用任意次，使得前 $n/2$ 位和后 $n/2$ 位的和相等。答案模 $998244353$。

$1\le n\le2\cdot10^5,1\le k\le10$。

## 解法

考虑对于每个 $i$，计算出 $f(i)$，表示有多少种方法用 $n/2$ 个物品拼出 $i$，那么答案就是 $\sum_if(i)^2$。

然后发现是一个完全背包的形式，于是直接做多项式快速幂就好了。

# 528D Fuzzy Search

## 题意

给两个串 $S,T$ 和一个正整数 $k$，对于每一对数 $(i,j)$，如果称 $S_i$ 和 $T_j$ 是匹配的，那么 $\exists p\in[i-k,i+k],S_i=T_j$。求 $T$ 在 $S$ 中完全匹配的次数。

$1\le n,m\le2\cdot10^5,0\le k\le2\cdot10^5$，字符集大小为 $4$。

## 解法

对于 $S$ 中的每个位置，预处理出它能和字符集中哪些字符匹配。

然后随便卷就完事了，略。

# 632E Thief in a Shop

## 题意

求完全背包装 $k$ 个物品可以得到的所有重量。

$1\le n,k,a_i\le10^3$。

## 解法

多项式快速幂，每次乘完把系数全部替换成 $0,1$，最后输出非 $0$ 项的系数。

# 914G Sum the Fibonacci
# 1218E Product Tuples
# 286E Ladies' Shop

## 题意

给一个集合 $S$，求出它的一个最小的子集 $T$，使得 $\{\sum_{i\in A}i\mid A\subseteq T,A\ne\varnothing,\sum_{i\in A}i\le m\}=S$。

$1\le n,m\le10^6$。

## 解法

可以证明，如果存在解，那么对于一个最优解 $T$，$\forall x,y\in S,x\ne y,x+y\notin T$。（可以考虑 $T=S$ 的情况？）

然后我们要找的就是 $\{x+y\mid x,y\in S,x\ne y\}$，显然可以用 NTT 卷一下。

# 954I Yet Another String Matching Problem

## 题意

给两个字符串 $S,T$，$\forall i\in[0,n-m]$，求对于 $S[i,i+m-1],T$ 这两个字符串，每次操作可以选择两个字符 $(s,t)$，把两个串中出现的 $s$ 全部替换成 $t$，最小进行几次操作可以让两个串相等。

$1\le m\le n\le125000$，字符集大小为 $6$。

## 解法

假设 $n=m$，然后考虑给 $\forall i\in[1,n],S_i\ne T_i$ 的 $(S_i,T_i)$ 连边，那么 $6-\small\sf{连通块数}$ 就是答案。

那么可以做 $6^2$ 次卷积，判定每个 $S$ 的长度为 $m$ 的子串是否和 $T$ 有连边，然后并查集就好了。

# 1251F Red-White Fence

## 题意

给两个序列 $a,b$，每次查询一个 $Q_i$，求有多少个以 $b$ 中的某一个元素 $x$ 为峰顶，其它元素都在 $a$ 中的一个单峰序列 $s$，满足 $|s|+x=\frac{Q_i}2$。

$1\le n\le3\cdot10^5,1\le|b|\le5,1\le q\le3\cdot10^5,4\le Q_i\le1.2\cdot10^6$，$Q_i$ 均为偶数。

## 解法

首先显然可以枚举 $k$，然后我们忽略 $x$ 的影响。然后注意到出现次数 $>2$ 的数没有意义，因为一个数最多在序列中出现两次。

假设 $a_i$ 互不相同，那么询问 $i$ 的答案就是 $\binom ni2^i$。

然后我们一对一对地插入相同的数。对于每一对数，有下面三种情况：

- 都放进去，那么只有一种方案，对答案的贡献是 $x^2F(x)$。
- 放一个进去，那么有两种方案，对答案的贡献是 $2xF(x)$。
- 不放进去，那么只有一种方案，对答案的贡献是 $F(x)$。

那么每一个数对答案的贡献就是 $(1+2x+x^2)F(x)=(1+x)^2F(x)$。

假设这样的数对有 $m$ 个，那么总的对答案的影响就是 $(1+x)^{2m}$。

所以我们只需要算出 $\displaystyle\left(\sum_{i=0}^{n-2m}\binom ni2^ix^i\right)\left(\sum_{i=0}^{2m}\binom{2m}i	x^i\right)$ 就好了。

# 958F3 Lightsabers (hard)
# 986D Perfect Encoding
# 1218D Xor Spanning Tree
# 300D Painting Square
# 827E Rusty String
# 1257G Divisor Set
# 662C Binary Table
# 960G Bandit Blues
# 754E Dasha and cyclic table
# 1033F Boolean Computer
# 472G Design Tutorial: Increase the Constraints
# 850E Random Elections
# 981H K Paths
# 1334G Substring Search
# 438E The Child and Binary Tree
# 755G PolandBall and Many Other Balls
# 923E Perpetual Subtraction
# 1119H Triple
# 1184A3 Heidi Learns Hashing (Hard)
# 1286F Harry The Potter
# 553E Kyoya and Train
# 623E Transforming Sequence
# 1103E Radix sum
# 901E Cyclic Cipher
# 715E Complete the Permutations
# 1010F Tree
# 773F Test Data Generation
# 1054H Epic Convolution
# 848E Days of Floral Colours
# 1270I Xor on Figures