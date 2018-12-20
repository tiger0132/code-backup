#include <cstdio>
#define int long long

const int _[] = {2, 7, 61}, M = 3, C = 19260817;
int p_(int x, int y, int z) {
	int ret = 1;
	for (; y; (x *= x) %= z, y >>= 1) if (y & 1) (ret *= x) %= z;
	return ret;
}
bool chk(int p, int x) {
	int s = 0, t = p-1;
	while (!(t & 1)) {
		t >>= 1;
		s++;
	}
	int y = p_(x, t, p);
	if (y == 1 || y == p-1) return 1;
	while (s--) {
		(y *= y) %= p;
		if (y == p-1) return 1;
	}
	return 0;
}
bool prime(int x) { // 假装 _[x] 里面都是质数
	if (x == 1) return 0;
	for (int i = 0; i < M; i++) {
		if (x == _[i]) return 1;
	}
	for (int i = 0; i < M; i++) {
		if (!(x % _[i]) || !chk(x, _[i])) return 0;
	}
	return 1;
}
int n, x;
signed main() {
	for (scanf("%*d%lld", &n); n--; ) {
		scanf("%lld", &x);
		puts(prime(x) ? "Yes" : "No");
	}
}