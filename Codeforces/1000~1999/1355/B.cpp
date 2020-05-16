#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5 + 53;

int n, ans, cnt, a[N];
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		std::sort(a + 1, a + n + 1);
		ans = cnt = 0;
		for (int i = 1; i <= n; i++)
			if (++cnt >= a[i]) ans++, cnt = 0;
		printf("%d\n", ans);
	}
}