#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <utility>

typedef long long ll;
typedef std::pair<ll, int> pii;

const int M = 4e4 + 44;

int _, a, b, p, q, q2, n, m, T;
pii B[M], ans;

int g(int x) { return 2ll * p * x % q2; }
int main() {
	for (scanf("%d", &_); _--;) {
		memset(B, 0, sizeof B), a = b = p = q = q2 = n = m = T = 0;
		scanf("%d%d%d%d", &a, &b, &p, &q);
		T = sqrt(n = b - a + 1), q2 = 2 * q;
		for (int i = 0; i < T; i++) B[i + 1] = pii(g(a + i), i);
		std::sort(B + 1, B + T + 1);
		for (int i = 1; i <= T; i++)
			if (i == 1 || B[i].first != B[i - 1].first) B[++m] = B[i];
		B[0] = B[m], B[m + 1] = B[1];
		ans = {2e9, 2e9};
		for (int i = 0; i < T; i++) {
			int it = std::lower_bound(B + 1, B + m + 1, pii((3ll * q - 2ll * p * T * i % q2) % q2, 0)) - B - 1;
			ans = std::min(ans, pii(llabs((B[it].first + 2ll * p * T * i) % q2 - q), B[it].second + a + i * T));
			ans = std::min(ans, pii(llabs((B[it + 1].first + 2ll * p * T * i) % q2 - q), B[it + 1].second + a + i * T));
		}
		for (int i = a + T * T; i <= b; i++) ans = std::min(ans, pii(llabs(2ll * p * i % q2 - q), i));
		printf("%d\n", ans.second);
	}
}