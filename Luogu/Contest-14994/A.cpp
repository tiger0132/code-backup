#include <algorithm>
#include <cstdio>
#include <cstring>

using ll = long long;
using lll = __int128;
const int N = 3e7 + 73;

int t, n, f;
char a[N];
ll l, r;
lll x;
int main() {
	for (scanf("%lld%lld%d", &l, &r, &t); t--;) {
		scanf("%s", a);
		n = strlen(a), x = 0, f = 1;
		// 特判 "-", "-0*", "0*"
		if ((*a == '-' && (n == 1 || a[1] == '0')) || (n > 1 && a[0] == '0')) {
			puts("1");
			continue;
		}
		// 太长直接 2
		if (n > 25) {
			puts("2");
			continue;
		}
		for (int i = 0; i < n; i++) {
			if (a[i] == '-')
				f = -1;
			else
				x = x * 10 + a[i] - '0';
			if ((x * f) < l || r < (x * f)) {
				puts("2");
				goto end;
			}
		}
		puts("0");
	end:;
	}
}