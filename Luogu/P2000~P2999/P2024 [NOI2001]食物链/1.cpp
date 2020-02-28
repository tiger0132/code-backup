#include <algorithm>
#include <cstdio>
#include <cstring>
#define A(x) x
#define B(x) x + n
#define C(x) x + 2 * n

const int N = 5e4 + 45, K = 2e5 + 52;

int p[K];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void u(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}

int n, m, op, x, y, ans;
int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%d%d%d", &op, &x, &y);
		if (x > n || y > n)
			ans++;
		else if (op == 1) {
			if (f(A(x)) == f(B(y)) || f(B(x)) == f(A(y)))
				ans++;
			else
				u(A(x), A(y)), u(B(x), B(y)), u(C(x), C(y));
		} else {
			if (f(A(x)) == f(A(y)) || f(B(x)) == f(A(y)))
				ans++;
			else
				u(A(x), B(y)), u(B(x), C(y)), u(C(x), A(y));
		}
	}
	printf("%d", ans);
}