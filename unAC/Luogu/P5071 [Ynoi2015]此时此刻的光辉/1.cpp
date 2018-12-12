#include <algorithm>
#include <cstdio>
#include <cmath>
#include <map>
#define int long long

const int N = 1e5+51, M = 11, P = 19260817;

int size;

struct node {
	int l, r, *ans;
	bool operator<(const node& rhs) const {
		return l / size == r / size ? r < rhs.r : l < rhs.l;
	}
} q[N];

int u[N], v[N][M], w[N][M];
int a[N], ans[N], cnt[N];
int n, m, l, r, lans;

int inv(int x) {
	int y = P-2, _ = 1;
	for (; y; (x *= x) %= P, y >>= 1) if (y & 1) (_ *= x) %= P;
	return _;
}
void add(int x, int o) {
	for (int i = 1; i <= u[x]; i++) {
		(lans *= inv(cnt[v[x][i]] + 1)) %= P;
		// printf("[%lld] ", lans);
		(cnt[v[x][i]] += o * w[x][i]) %= P;
		(cnt[v[x][i]] += P) %= P;
		(lans *= cnt[v[x][i]] + 1) %= P;
		// printf("%lld(%lld) %s %lld: %lld\n", v[x][i], cnt[v[x][i]], o == 1 ? "+=" : "-=", w[x][i], lans);
	}
}
std::map<int, int> mmp;
int id(int x) {
	// static std::map<int, int> mmp;
	if (!mmp.count(x)) mmp[x] = mmp.size()+1;
	return mmp[x];
}
signed main() {
	scanf("%lld%lld", &n, &m);
	size = ceil(sqrt(n));
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a+i); int _x = a[i];
		for (int j = 2; j*j <= _x && a[i] > 1; j++) {
			if (a[i] % j) continue;
			// v[i][++u[i]] = j;
			// printf("(%lld)*", j);
			v[i][++u[i]] = id(j);
			while (a[i] % j == 0) {
				w[i][u[i]]++;
				a[i] /= j;
			}
		}
		if (a[i] > 1) {
			// printf("(%lld)", a[i]);
			v[i][++u[i]] = id(a[i]);
			w[i][u[i]] = 1;
		}
		// puts("");
	}
	// puts("!");
	for (int i = 1; i <= m; i++) {
		scanf("%lld%lld", &q[i].l, &q[i].r);
		q[i].ans = ans+i;
	}
	std::sort(q+1, q+m+1);
	// for (int i = 1; i <= 1; i++) {
	// 	for (int j = 1; j <= u[i]; j++) {
	// 		printf("(%lld^%lld)", v[i][j], w[i][j]);
	// 	} puts("");
	// }
	// puts("!");
	l = 1; r = 0; lans = 1;
	for (int i = 1; i <= m; i++) {
		while (l > q[i].l) add(--l, 1);
		while (r < q[i].r) add(++r, 1);
		while (l < q[i].l) add(l++, -1);
		while (r > q[i].r) add(r--, -1);
		// for (int j = 1; j <= mmp.size(); j++) {
		// 	printf("(%lld)", cnt[j]);
		// } puts("");
		*q[i].ans = lans;
	}
	// for (int i = 1; i <= mmp.size(); i++) {
	// 	printf("%lld", cnt[i]);
	// } puts("");
	for (int i = 1; i <= m; i++) {
		printf("%lld\n", ans[i]);
	}
}

#if 0
5 1
2 4 3 5 10
1 5
#endif