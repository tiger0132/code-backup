// bf method, best method

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#define int long long

int n, a[3], b[3], p[4][3];
int s[3], b1[3];
signed main() {
	scanf("%lld", &n);
	for (int i = 0; i < 3; i++) scanf("%lld", a + i);
	for (int i = 0; i < 3; i++) scanf("%lld", b + i);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++) p[i][j] = j;

	int mn = n, mx = 0;
	do {
		do {
			do {
				do {
					memset(s, 0, sizeof s);
					memcpy(b1, b, sizeof b);
					int lans = 0;
					for (int _i = 0; _i < 3; _i++) {
#define i p[3][_i]
						for (int _j = 0; b1[i] && _j < 3; _j++) {
#define j p[i][_j]
							if (s[j] < a[j]) {
								int t = std::min(a[j] - s[j], b1[i]);
								b1[i] -= t, s[j] += t;
								if ((j == 0 && i == 1) || (j == 1 && i == 2) ||
									(j == 2 && i == 0))
									lans += t;
							}
						}
					}
					mn = std::min(mn, lans);
					mx = std::max(mx, lans);
					assert(!b1[0] && !b1[1] && !b1[2]);
				} while (std::next_permutation(p[2], p[2] + 3));
			} while (std::next_permutation(p[1], p[1] + 3));
		} while (std::next_permutation(p[0], p[0] + 3));
	} while (std::next_permutation(p[3], p[3] + 3));  // all
	printf("%lld %lld\n", mn, mx);
}