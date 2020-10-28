#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, a[N];

int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		int h = 1, last = 1, cur = 0, cnt = 0;
		a[1] = 1e9;
		for (int i = 2; i <= n; i++) {
			if (a[i - 1] > a[i]) {
				if (cur == last) {
					h++;
					last = cnt;
					cnt = cur = 0;
				}
				cur++;
			}
			cnt++;
		}
		printf("%d\n", h);
	}
}