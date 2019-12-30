#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 1e5 + 51;

int n, x, B, A;
signed main() {
	for (scanf("%*d"); ~scanf("%lld", &n);) {
		A = B = 0;
		for (int i = 1; i <= n; i++) scanf("%lld", &x), B ^= x, A += x;
		printf("2\n%lld %lld\n", B, A + B);
	}
}