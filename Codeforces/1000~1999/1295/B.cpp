#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int n, x, t[N];
char s[N];
int main() {
	for (scanf("%*d"); ~scanf("%d%d%s", &n, &x, s + 1);) {
		int ans = 0, cur = 0;
		for (int i = 1; i <= n; i++) {
			cur += (s[i] == '0' ? 1 : -1);
			t[i] = cur;
		}
		if (!x) ans++;
		if (!cur) {
			for (int i = 1; i <= n; i++)
				if (t[i] == x) {
					puts("-1");
					goto end;
				}
			puts("0");
		} else {
			for (int i = 1; i <= n; i++) {
				if (1ll * (x - t[i]) * cur < 0) continue;
				if ((x - t[i]) % cur == 0) ans++;
			}
			printf("%d\n", ans);
		}
	end:;
	}
}