#include <algorithm>
#include <cstdio>
#include <cstring>

int n, x, c1, c2, d;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		if (x < 0) c1++;
		if (x > 0) c2++;
	}
	d = (n + 1) / 2;
	if (c1 >= d)
		puts("-1");
	else if (c2 >= d)
		puts("1");
	else
		puts("0");
}