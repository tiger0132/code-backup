#include <algorithm>
#include <cstdio>
#include <cmath>

typedef long double ld;
const int N = 5e2+25;
const ld eps = 1e-6;

struct $ {
	int x; ld y[N];
	bool operator<(const $& rhs) const {
		return x < rhs.x;
	}
} a[N];

int n, m, lb[N];
bool ins(int x) {
	for (int i = m; i >= 1; i--) {
		if (fabsl(a[x].y[i]) < eps) continue;
		if (!lb[i]) return (lb[i] = x), 1;
		ld t = a[x].y[i] / a[lb[i]].y[i];
		for (int j = 1; j <= i; j++) {
			a[x].y[j] -= a[lb[i]].y[j] * t;
		}
	}
	return 0;
}

int cnt, ans;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%Lf", a[i].y+j);
		}
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].x);
	}
	std::sort(a+1, a+n+1);
	for (int i = 1; i <= n; i++) {
		if (ins(i)) {
			cnt++; ans += a[i].x;
		}
	}
	printf("%d %d\n", cnt, ans);
}