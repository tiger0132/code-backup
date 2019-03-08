#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55;

int n, m, fail[N];
char a[N], b[N];
void getfail() {
	fail[0] = -1;
	for (int i = 1, cnt = -1; i < m; i++) {
		while (cnt >= 0 && b[cnt + 1] != b[i]) cnt = fail[cnt];
		if (b[cnt + 1] == b[i]) cnt++;
		fail[i] = cnt;
	}
}

int k, a0, a1, b0, b1, c0, c1;
char c[N];
int main() {
	scanf("%s%s", a, b);
	n = strlen(a);
	m = strlen(b);
	getfail();
	k = fail[m - 1];
	for (int i = 0; i < n; i++) {
		a0 += a[i] == '0';
		a1 += a[i] == '1';
	}
	for (int i = 0; i < m; i++) {
		b0 += b[i] == '0';
		b1 += b[i] == '1';
	}
	for (int i = k + 1; i < m; i++) {
		c[i - k - 1] = b[i];
		c0 += b[i] == '0';
		c1 += b[i] == '1';
	}
	if (a0 < b0 || a1 < b1) return puts(a), 0;
	a0 -= b0, a1 -= b1;
	printf("%s", b);
	for (int i = 1;; i++) {
		if (a0 < c0 || a1 < c1) break;
		a0 -= c0, a1 -= c1;
		printf("%s", c);
	}
	for (int i = 0; i < a0; i++) putchar('0');
	for (int i = 0; i < a1; i++) putchar('1');
}