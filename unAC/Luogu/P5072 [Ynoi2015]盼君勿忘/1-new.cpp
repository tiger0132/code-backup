#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cmath>

typedef std::unordered_map<int, int>::const_iterator $;
typedef unsigned long long ull;
const int N = 1e5+51;

struct _ {
	ull operator()(ull x) const {
		x += 0x9e3779b97f4a7c15;
		x = (x^(x>>30)) * 0xbf58476d1ce4e5b9;
		x = (x^(x>>27)) * 0x94d049bb133111eb;
		return x^(x>>31);
	}
};
int sz;
struct node {
	int l, r, p, *ans;
	bool operator<(const node& rhs) const {
		return l / sz == rhs.l / sz ? r < rhs.r : l < rhs.l;
	}
} q[N];

int n, m, l, r, a[N], b[N], ans[N], cnt[N], u[N], v[N];
std::unordered_map<int, int> mmp;
int p2(int x, int y) { return 1ll * u[x % sz] * v[x / sz] % y; }
void add(int x) {
	if (cnt[x]) mmp[cnt[x]] -= b[x];
	mmp[++cnt[x]] += b[x];
}
void del(int x) {
	mmp[cnt[x]] -= b[x];
	if (--cnt[x]) mmp[cnt[x]] += b[x];
}
int main() {
	scanf("%d%d", &n, &m); sz = ceil(sqrt(n));
	for (int i = 1; i <= n; i++) {
		scanf("%d", a+i); b[i] = a[i];
	}
	std::sort(b+1, b+n+1);
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(b+1, b+n+1, a[i]) - b;
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].p);
		q[i].ans = ans+i;
	}
	std::sort(q+1, q+m+1);
	l = 1; r = 0;
	for (int i = 1; i <= m; i++) {
		u[0] = v[0] = 1;
		for (int j = 1; j <= sz; j++) u[j] = u[j-1] * 2ll % q[i].p;
		for (int j = 1; j <= sz; j++) v[j] = 1ll * v[j-1] * u[sz] % q[i].p;
		while (l > q[i].l) add(a[--l]);
		while (r < q[i].r) add(a[++r]);
		while (l < q[i].l) del(a[l++]);
		while (r > q[i].r) del(a[r--]);
		int tmp = p2(r-l+1, q[i].p);
		for ($ it = mmp.begin(); it != mmp.end(); it++) {
			(*q[i].ans += // 括号缩进大法……
				(
					1ll * it->second *
					(tmp - p2(r-l-it->first+1, q[i].p) + q[i].p)
				) % q[i].p
			) %= q[i].p;
		}
	}
	for (int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
}

#if 0
5 5
1 2 2 3 4
1 2 233333
2 3 333333
1 5 5
3 5 15
2 4 8
#endif