// 毒瘤李欣隆，正气满乾坤
// 碳碳键键能能否否定定理一？

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

typedef long long ll;

const int N = 100001, M = 3500, K = 169, _$ = 32004, P = 19260817;

static int sz;
struct node {
	int l, r, *ans;
	inline bool operator<(const node& rhs) const {
		return l / sz == rhs.l / sz ? r < rhs.r : l < rhs.l;
	}
} q[N];

static int np[_$], prime[M], inv[2 * N] = {0, 1}, pcnt, _;
static int n, m, mx, a[N], c$[N][K], cnt[2 * N], ans[N];
static std::vector<int> v[N];
static int l, r;
static ll lans;

inline void add(int x, int o) {
	static int _i;
	for (_i = 0; _i < v[x].size(); _i++) {
		(lans *= inv[cnt[v[x][_i]] + 1]) %= P;
		(cnt[v[x][_i]] += P + o) %= P;
		(lans *= cnt[v[x][_i]] + 1) %= P;
	}
}

static std::map<int, int> mp;
inline int id(int x) {
	if (!mp.count(x)) return mp[x] = mp.size() + 1;
	return mp[x];
}

int main() {
	register int i, j;
	for (i = 2; i < 2 * N; i++) {
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	}
	for (i = 2; i <= 32000; i++) {
		if (np[i]) continue;
		prime[++pcnt] = i;
		for (j = 2 * i; j <= 32000; j += i) np[j] = 1;
	}
	scanf("%d%d", &n, &m);
	sz = ceil(sqrt(n));
	for (i = 1; i <= n; i++) {
		scanf("%d", a + i);
		mx = std::max(mx, a[i]);
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= 168; j++) {
			c$[i][j] = c$[i - 1][j];
			while (a[i] % prime[j] == 0) a[i] /= prime[j], c$[i][j]++;
		}
		if (a[i] == 1) continue;
		for (j = 169; j <= pcnt; j++) {
			while (a[i] % prime[j] == 0) {
				a[i] /= prime[j], v[i].push_back(id(prime[j]));
			}
		}
		if (a[i] > 1) v[i].push_back(id(a[i]));
	}
	for (i = 1; i <= m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].ans = ans + i;
	}
	std::sort(q + 1, q + m + 1);
	l = 1, lans = 1;
	for (i = 1; i <= m; i++) {
		while (l > q[i].l) add(--l, 1);
		while (r < q[i].r) add(++r, 1);
		while (l < q[i].l) add(l++, -1);
		while (r > q[i].r) add(r--, -1);
		ll tmp = lans;
		for (j = 1; j <= 168; j++) {
			(tmp *= c$[r][j] - c$[l - 1][j] + 1) %= P;
		}
		*q[i].ans = tmp;
	}
	for (i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
}