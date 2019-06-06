#include <algorithm>
#include <cmath>
#include <cstdio>
#include <unordered_map>

typedef long long ll;
int pw(int x, int y, int p) {
	int r = 1;
	for (; y; y >>= 1, x = (ll)x * x % p)
		if (y & 1) r = (ll)r * x % p;
	return r;
}
int bsgs(int a, int b, int p) {
	std::unordered_map<int, int> mp;
	int m = ceil(sqrtl(p)), t1 = b, t2 = 1;
	for (int i = 0; i < m; i++, t1 = (ll)t1 * a % p, t2 = (ll)t2 * a % p) mp[t1] = i;
	for (int i = 1, j = t2; i <= m; i++, j = (ll)j * t2 % p)
		if (mp.count(j) && i * m - mp[j] >= 0) return i * m - mp[j];
	return -1;
}

int t, k, x, y, p;
int main() {
	for (scanf("%d%d", &t, &k); t--;) {
		scanf("%d%d%d", &x, &y, &p);
		if (k == 1) {
			x %= p;
			printf("%d\n", pw(x, y, p));
		}
		if (k == 2) {
			x %= p, y %= p;
			printf(!x && y ? "Orz, I cannot find x!\n" : "%lld\n", (ll)y * pw(x, p - 2, p) % p);
		}
		if (k == 3) {
			x %= p, y %= p;
			int tmp = bsgs(x, y, p);
			printf((!x && y) || tmp == -1 ? "Orz, I cannot find x!\n" : "%d\n", tmp);
		}
	}
}