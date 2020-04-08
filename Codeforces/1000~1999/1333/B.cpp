#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;
int n, a[N], b[N], tmp[233], *cnt = tmp + 10;
inline int sgn(int x) { return x < 0 ? -1 : x > 0; }
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		for (int i = 1; i <= n; i++) scanf("%d", b + i);
		cnt[1] = cnt[-1] = 0, cnt[0] = 1;
		for (int i = 1; i <= n; i++) cnt[sgn(a[i])]++;
		for (int i = n; i >= 1; i--) {
			cnt[sgn(a[i])]--;
			if (!cnt[sgn(b[i] - a[i])]) {
				puts("NO");
				goto end;
			}
		}
		puts("YES");
	end:;
	}
}