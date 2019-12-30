#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, a[N], b[N], l, r;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		l = r = 0;
		for (int i = 2; i <= n; i++)
			if (abs(a[i] - a[i - 1]) > 1) {
				printf("YES\n%d %d\n", i - 1, i);
				goto end;
			}
		puts("NO");
	end:;
	}
}