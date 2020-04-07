# General suffix automaton construction algorithm and space bounds

## 定义

**定义一** 对于一个正整数 $k$，如果对于一个有限状态自动机 $A$，不存在两个 LCP 长度 $\ge k$ 的不同字符串能被 $A$ 接受，那么称是 **k-后缀唯一** 的。如果它是 $1$-后缀-唯一的，那么也称它是 **后缀唯一** 的。

**定义二** 令 $A$ 是一个有限状态自动机。对于任意一个字符串 $x$，定义 $\text{end-set}(x)$ 为在 $A$ 中所有能通过开头为 $x$ 的路径到达的状态。如果对于两个串 $x,y$，有 $\text{end-set}(x)=\text{end-set}(y)$，那么称 $x,y$ 是等价的，记做 $x\equiv y$。我们定义 $x$ 所在的等价类为 $[x]$。

**引理一** 假设 $A$ 是后缀唯一的。