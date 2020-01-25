#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define int long long

int dist(int x1, int y1, int x2, int y2) { return llabs(x1 - x2) + llabs(y1 - y2); }

const int N = 1e2 + 21;

int n, x[N], y[N];
signed main() {
	int x0 = 0, y0 = 0, ax = 0, ay = 0, bx = 0, by = 0, xs = 0, ys = 0, t = 0, ans = 0;
	scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld", &x0, &y0, &ax, &ay, &bx, &by, &xs, &ys,
		  &t);
	x[0] = x0, y[0] = y0;
	for (n = 1;; n++) {
		x[n] = ax * x[n - 1] + bx;
		y[n] = ay * y[n - 1] + by;
		if (x[n] > 1e16 || y[n] > 1e16) break;
	}
	for (int i = 0; i <= n; i++) {
		int lans = 0, xx = xs, yy = ys, tt = t;
		for (int j = i; j >= 0; j--) {
			if ((tt -= dist(x[j], y[j], xx, yy)) >= 0)
				lans++;
			else
				goto end;
			xx = x[j], yy = y[j];
		}
		for (int j = i + 1; j <= n; j++) {
			if ((tt -= dist(x[j], y[j], xx, yy)) >= 0)
				lans++;
			else
				goto end;
			xx = x[j], yy = y[j];
		}
	end:
		ans = std::max(ans, lans);
	}
	printf("%lld", ans);
}