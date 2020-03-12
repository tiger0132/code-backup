#include <algorithm>
#include <cstring>
#include <cstdio>

typedef long long ll;
const int N = 1e2 + 21;

int n, k, v[66];
ll x;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &k);) {
		memset(v, 0, sizeof v);
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &x);
			for (int j = 0; x; j++, x /= k) v[j] += x % k;
		}
		for (int i = 0; i < 55; i++)
			if (v[i] > 1) {
				puts("NO");
				goto end;
			}
		puts("YES");
	end:;
	}
}