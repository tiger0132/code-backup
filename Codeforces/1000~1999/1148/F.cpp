#include <algorithm>
#include <cstring>
#include <cstdio>

typedef long long ll;
const int N = 3e5 + 53;

ll msk[N], s, ans;
int n, v[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%lld", v + i, msk + i), s += v[i];
	if (s < 0) {
		for (int i = 1; i <= n; i++) v[i] = -v[i];
		s = -s;
	}
	for (int i = 61; i >= 0; i--) {
		ll s0 = 0;
		for (int j = 1; j <= n; j++)
			if ((msk[j] & -msk[j]) == (1ll << i)) s0 += v[j];
		if (s0 > 0) {
			ans |= 1ll << i;
			for (int j = 1; j <= n; j++)
				if ((msk[j] >> i) & 1) v[j] = -v[j];
		}
	}
	printf("%lld", ans);
}