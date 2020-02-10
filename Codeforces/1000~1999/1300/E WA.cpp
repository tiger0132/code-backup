#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e6 + 61;

int p[N], sz[N];
ll sum[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void u(int x, int y) {
	x = f(x), y = f(y);
	x[p] = y, y[sum] += x[sum], y[sz] += x[sz];
}

int n, x, l;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &x), i[sum] = x, i[sz] = 1;
	for (l = 1; l < n;)
		for (int i = l, j, fl = 1; i <= n; i++) {
			i = f(i), j = f(i + 1);
			if (i < n && 1. * i[sum] / i[sz] > 1. * j[sum] / j[sz])
				u(i, j), fl = 0;
			else if (fl)
				l = i;
		}
	for (int i = 1; i <= n; i++) {
		i = f(i);
		for (int j = 0; j < i[sz]; j++) printf("%.9f\n", 1. * i[sum] / i[sz]);
	}
}