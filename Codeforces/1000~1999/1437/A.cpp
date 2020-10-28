#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

int l, r;
signed main() {
	for (scanf("%*d"); ~scanf("%lld%lld", &l, &r);) {
		puts(r - l >= l ? "NO" : "YES");
	}
}