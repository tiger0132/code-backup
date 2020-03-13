#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>

const int N = 5e3 + 35;

inline int fl_log2(int n) { return 31 - __builtin_clz(n); }
inline int mndep(int n) {
	int r = 0;
	for (int i = 2; i <= n; i++) r += fl_log2(i);
	return r;
}
inline bool is_pow2(int n) { return !(n & (n - 1)); }

int n, d, p[N], path[N], l, len;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &d);) {
		if (d < mndep(n) || d > n * (n - 1) / 2) {
			puts("NO");
			continue;
		}
		len = 0, l = 1, d -= mndep(n);
		puts("YES");
		for (int i = 1; i <= n; i <<= 1) path[++len] = i;
		for (int i = n; i >= 2; i--)
			if (!d || is_pow2(i))
				i[p] = i >> 1, l++;
			else
				i[p] = path[len - l + std::min(d, l)], d -= std::min(d, l),
				path[++len] = i, l++;
		for (int i = 2; i <= n; i++) printf("%d%c", i[p], " \n"[i == n]);
	}
}