记 $\Sigma$ 为字符集，$|\Sigma|$ 为字符集大小。对于一个字符串 $s$，记 $|s|$ 为其长度。

## endpos

对于 $s$ 的某个非空子串，定义 $\operatorname{endpos}(t)=\{i\mid s_{i-|t|+1\ldots i}=t,|t|-1\le i<|s|\}$。即 $s$ 中 $t$ 的所有结束位置。它有以下重要结论：

- 对于 $s$ 中的两个非空子串 $u,w$，如果 $|u|\le|w|$，那么 $\operatorname{endpos}(u)=\operatorname{endpos}(w)$ 当且仅当，每次 $u$ 在 $s$ 中出现，都是以 $w$ 的后缀的形式。
- 对于 $s$ 中的两个非空子串 $u,w$，如果 $|u|\le|w|$，那么：
	- 如果 $u$ 是 $w$ 的后缀，那么 $\operatorname{endpos}(u)\subseteq\operatorname{endpos}(w)$。
	- 否则 $\operatorname{endpos}(u)=\operatorname{endpos}(w)$。
- 同一个 $\operatorname{endpos}$ 等价类里包含了长度连续的一些字符串，它们都是其中最长的串的后缀。
- $\operatorname{endpos}$ 等价类个数是 $O(n)$ 级别的。

## link

对于一个 $\operatorname{endpos}$ 等价类 $v$，$\operatorname{link}(v)$ 等于 $v$ 中某个字符串里最长的，不属于 $v$ 的后缀的 $\operatorname{endpos}$ 等价类。它有以下重要结论：

- 所有 $\operatorname{link}$ 构成了一棵树。
- 通过 $\operatorname{endpos}$ 构造的树和 $\operatorname{link}$ 构造的树相同。

