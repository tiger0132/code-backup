#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cmath>

typedef unsigned long long u;
const int N = 3e6+63, M = 1e5+51;

int sz;
struct $ {
	int l, r; u *ans;
	inline bool operator<(const $& rhs) const {
		return l / sz == rhs.l / sz ? r < rhs.r : l < rhs.l;
	}
} q[M];

u h[N], p[N], b[N], out[N], lans;
int n, m, k, l, r, cnt[N];
char a[N];

inline void add(int x) { lans += cnt[x]++; }
inline void del(int x) { lans -= --cnt[x]; }
std::unordered_map<u, int> mp;
inline int id(u x) {
	if (!mp.count(x)) return mp[x] = mp.size()+1;
	return mp[x];
}
int main() {
	register int i;
	scanf("%d%d%d%s", &n, &m, &k, a+1);
	sz = n / std::sqrt(m); *p = 1;
	for (i = 1; i <= n; i++) {
		h[i] = h[i-1] * 131 + a[i];
		p[i] = p[i-1] * 131;
	}
	for (i = 0; i <= n-k+1; i++) {
		b[i+1] = id(h[i+k] - h[i] * p[k]);
	}
	for (i = 1; i <= m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].r = std::min(q[i].r, n-k+1);
		q[i].ans = out+i;
	}
	std::sort(q+1, q+m+1);
	l = 1; r = 0;
	for (i = 1; i <= m; i++) {
		if (q[i].l > q[i].r) continue;
		while (r < q[i].r) add(b[++r]);
		while (l > q[i].l) add(b[--l]);
		while (r > q[i].r) del(b[r--]);
		while (l < q[i].l) del(b[l++]);
		*q[i].ans = lans;
	}
	for (i = 1; i <= m; i++) {
		printf("%llu\n", out[i]);
	}
}