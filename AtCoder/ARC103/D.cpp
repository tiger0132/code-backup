#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e3;

int n, m, x[N], y[N], c[2];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", x + i, y + i);
		c[(x[i] + y[i]) & 1]++;
	}
	if (c[0] && c[1]) return puts("-1"), 0;
	printf(c[0] ? "32\n1 " : "31\n");
	for (int i = 30; i >= 0; i--) printf("%d%c", 1 << i, " \n"[!i]);
	for (int i = 1; i <= n; i++) {
		if (c[0]) putchar('R'), x[i]--;
		for (int j = 30; j >= 0; j--)
			if (abs(x[i]) > abs(y[i])) {
				if (x[i] > 0)
					x[i] -= 1 << j, putchar('R');
				else
					x[i] += 1 << j, putchar('L');
			} else {
				if (y[i] > 0)
					y[i] -= 1 << j, putchar('U');
				else
					y[i] += 1 << j, putchar('D');
			}
		puts("");
	}
}