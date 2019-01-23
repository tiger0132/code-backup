#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

#define be(x) (((x)-1) / m + 1)
#define lb(x) (((x)-1) * m + 1)
#define rb(x) std::min((x)*m, n)

const int N = 6e5 + 56, M = 8e2 + 28;

int n, m, q, l, r, L, R, ans, out, a[N], _[N], cnt[M][M], mode[M][M], sum[N],
	lnk[N], S$, sz[N];
std::vector<int> idx[N];

int main() {
	scanf("%d%d", &n, &q);
	m = ceil(sqrt(n));
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		_[i] = a[i];
	}
	std::sort(_ + 1, _ + n + 1);
	S$ = std::unique(_ + 1, _ + n + 1) - _ - 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = std::lower_bound(_ + 1, _ + S$ + 1, a[i]) - _;
		idx[a[i]].push_back(i);
		++sz[a[i]];
		lnk[i] = sz[a[i]] - 1;
	}
	memset(mode, 0x3f, sizeof mode);
	for (int i = 1; i <= m; ++i) {
		memset(sum, 0, sizeof sum);
		for (int j = i; j <= m; ++j) {
			cnt[i][j] = cnt[i][j - 1];
			mode[i][j] = mode[i][j - 1];
			for (int k = lb(j); k <= rb(j); ++k) {
				++sum[a[k]];
				if (sum[a[k]] > cnt[i][j] ||
					(sum[a[k]] == cnt[i][j] && a[k] < mode[i][j])) {
					cnt[i][j] = sum[a[k]];
					mode[i][j] = a[k];
				}
			}
		}
	}
	while (q--) {
		scanf("%d%d", &l, &r);
		L = be(l);
		R = be(r);
		ans = cnt[L + 1][R - 1];
		out = mode[L + 1][R - 1];
		if (!ans) {
			ans = 1;
			out = a[l];
		}
		for (int i = l; i <= std::min(rb(L), r); ++i) {
			int orig = lnk[i] + ans - 1;
			if (0 <= orig && orig < sz[a[i]] && l <= idx[a[i]][orig] &&
				idx[a[i]][orig] <= r && a[i] < out) {
				out = a[i];
			}
			while (lnk[i] + ans < sz[a[i]] && idx[a[i]][lnk[i] + ans] <= r) {
				out = a[i];
				++ans;
			}
		}
		if (L != R)
			for (int i = lb(R); i <= r; ++i) {
				int orig = lnk[i] - ans + 1;
				if (0 <= orig && orig < sz[a[i]] && l <= idx[a[i]][orig] &&
					idx[a[i]][orig] <= r && a[i] < out) {
					out = a[i];
				}
				while (lnk[i] - ans >= 0 && idx[a[i]][lnk[i] - ans] >= l) {
					out = a[i];
					++ans;
				}
			}
		printf("%d\n", (ans > (r - l + 1) / 2) * _[out]);
	}
}