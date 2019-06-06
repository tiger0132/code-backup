#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <unordered_map>
#define int u

typedef unsigned long long u;
typedef __int128 _;
struct $ {
	static u nxt(u x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	int operator()(u x) const {
		static const u rnd = std::chrono::steady_clock::now().time_since_epoch().count();
		return nxt(x + rnd);
	}
};

int bsgs(int a, int b, int p) {
	std::unordered_map<int, int, $> mp;
	int m = ceil(sqrtl(p)), t1 = b, t2 = 1;
	for (int i = 0; i < m; i++, t1 = (_)t1 * a % p, t2 = (_)t2 * a % p) mp[t1] = i;
	for (int i = 1, j = t2; i <= m; i++, j = (_)j * t2 % p)
		if (mp.count(j)) return i * m - mp[j];
	return -1;
}

int k, p;
signed main() {
	scanf("%llu%llu", &k, &p);
	printf("%llu", bsgs(10, (9 * k + 1) % p, p));
}