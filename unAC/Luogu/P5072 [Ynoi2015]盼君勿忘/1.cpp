#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cmath>

typedef long long ll;
const int N = 1e5+51;

int sz;
struct node {
	int l, r, p, *ans;
	bool operator<(const node& rhs) const {
		return l / sz == rhs.l / sz ? r < rhs.r : l < rhs.l;
	}
} q[N];
int n, m, l, r, p, lans, a[N], b[N], ans[N], cnt[N], u[N], v[N];
int L[N], R[N], H;
ll sum[N];
int p2(int x) { return 1ll * u[x % sz] * v[x / sz] % p; }
void A(int x) {
	R[x] = H; L[H] = x; H = x; L[x] = 0;
	printf("%d -- %d -- %d\n", L[x], x, R[x]);
}
void D(int x) {
	if (x == H) H = R[x];
	else R[L[x]] = L[x], L[R[x]] = R[x];
}
void add(int x, int o) {
	if (cnt[x] && !(sum[cnt[x]] -= b[x])) D(cnt[x]);
	if (cnt[x] += o) {
		if (!sum[cnt[x]]) A(cnt[x]);
		sum[cnt[x]] += b[x];
	}
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
	l = 1; r = 0; lans = 0;
	for (int i = 1; i <= m; i++) {
		u[0] = v[0] = 1; p = q[i].p;
		for (int j = 1; j <= sz; j++) u[j] = u[j-1] * 2ll % p;
		for (int j = 1; j <= sz; j++) v[j] = 1ll * v[j-1] * u[sz] % p;
		while (l > q[i].l) add(a[--l], 1);
		while (r < q[i].r) add(a[++r], 1);
		while (l < q[i].l) add(a[l++], -1);
		while (r > q[i].r) add(a[r--], -1);
		int tmp = p2(r-l+1);
		for (int j = H; j; j = R[j]) {
			// printf("(%d)", j);
			(*q[i].ans += // 括号缩进大法……
				(
					1ll * sum[j] * (tmp - p2(r-l-j+1) + p)
				) % p
			) %= p;
		}
		puts("");
		*q[i].ans = lans;
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