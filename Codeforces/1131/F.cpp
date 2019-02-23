#include <cstdio>

const int N = 2e5 + 52;

int n, a[N], l[N], r[N], p[N], d[N];
int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }
void m(int x, int y) {
	if ((x = f(x)) != (y = f(y))) p[x] = y;
}

int x, y;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) l[i] = r[i] = i;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		x = f(x), y = f(y);
		a[r[x]] = l[y], d[l[y]]++, l[y] = l[x];
		m(x, y);
		for (int i = 1; i <= n; i++) {
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!d[i]) {
			for (int j = i; j; j = a[j]) {
				printf("%d ", j);
			}
			return 0;
		}
	}
}