#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>

typedef long double ld;
const int N = 1e5 + 51;

ld pw(ld x, int y) {
	ld r = 1;
	for (; y; y >>= 1, x *= x)
		if (y & 1) r *= x;
	return r;
}

int n, L, P, sum[N];
ld f[N];
inline ld w(int i, int j) { return pw(abs(sum[j] - sum[i] - 1 - L), P); }
int find(int i, int j) {  // 第一个满足 f[i] + w(i, k) >= f[j] + w(j, k) 的点
	int l = j, r = n + 1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (f[i] + w(i, mid) >= f[j] + w(j, mid))
			r = mid - 1;
		else
			l = mid + 1;
	}
	return l;
}

int l, r, q[N], rb[N], pre[N];
char s[N][33];
int main() {
	for (scanf("%*d"); ~scanf("%d%d%d", &n, &L, &P);) {
		for (int i = 1; i <= n; i++) {
			scanf("%s", s[i]);
			sum[i] = sum[i - 1] + strlen(s[i]) + 1;
		}
		q[l = r = 1] = 0;
		for (int i = 1; i <= n; i++) {
			while (l < r && rb[l] < i) l++;
			f[i] = f[q[l]] + w(q[l], i);
			pre[i] = q[l];
			while (l < r && rb[r - 1] >= find(q[r], i)) r--;
			rb[r] = find(q[r], i) - 1;
			q[++r] = i;
		}
		if (f[n] > 1e18) {
			puts("Too hard to arrange\n--------------------");
			continue;
		}
		printf("%lld\n", (long long)f[n]);
		std::function<void(int)> prt = [&](int pt) {
			if (pre[pt]) prt(pre[pt]);
			for (int i = pre[pt] + 1; i <= pt; i++) printf("%s%c", s[i], " \n"[i == pt]);
		};
		prt(n);
		puts("--------------------");
	}
}