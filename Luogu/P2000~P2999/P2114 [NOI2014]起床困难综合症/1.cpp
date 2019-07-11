#include <algorithm>
#include <cstdio>

const int N = 1e5 + 51;

int n, m, t0, t1 = -1, x, ans;
char op[4];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s%d", op, &x);
		if (*op == 'A') t0 &= x, t1 &= x;
		if (*op == 'O') t0 |= x, t1 |= x;
		if (*op == 'X') t0 ^= x, t1 ^= x;
	}
	for (int i = 1 << 30; i; i >>= 1) {
		if (!(t0 & i) && (t1 & i) && m >= i) ans += i, m -= i;
		if (t0 & i) ans += i;
	}
	printf("%d", ans);
}