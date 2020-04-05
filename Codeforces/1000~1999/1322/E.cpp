#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>

const int N = 5e5 + 55, LN = 20;

template <typename comp>
struct ST {
	inline static int lg2(int n) { return 31 - __builtin_clz(n); }
	inline static int _(int x, int y) { return comp()(x, y) ? x : y; }
	int st[LN][N];
	void init(int *a, int n) {
		memcpy(st[0], a, n << 2);
		for (int j = 1; j < LN; j++)
			for (int i = 0; i + (1 << j) - 1 < n; i++)
				st[j][i] = _(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
	}
	int operator()(int l, int r) {
		int k = lg2(r - l + 1);
		return _(st[k][l], st[k][r - (1 << k) + 1]);
	}
};

int n, ans, a[N], t[2][N], out[N];
ST<std::greater<int>> mx;
ST<std::less<int>> mn;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	a[0] = a[1], a[n + 1] = a[n];
	for (int i = 0; i <= n; i++) {
		t[0][i] = std::min(a[i], a[i + 1]);
		t[1][i] = std::max(a[i], a[i + 1]);
	}
	mn.init(t[1], n + 1);
	mx.init(t[0], n + 1);
	for (int i = 1; i <= n; i++) {
		int l = 1, r = std::min(i, n + 1 - i);
#define mid (l + r) / 2
#define Q(x, y) x(i - y, i + y - 1)
		while (l <= r)
			if (Q(mn, mid) <= Q(mx, mid))
				r = mid - 1;
			else
				l = mid + 1;
		if (r) {
			if (a[i] < a[i + 1])
				out[i] = l % 2 ? Q(mx, l) : Q(mn, l);
			else
				out[i] = l % 2 ? Q(mn, l) : Q(mx, l);
		} else
			out[i] = a[i];
		ans = std::max(ans, r);
	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++) printf("%d ", out[i]);
}