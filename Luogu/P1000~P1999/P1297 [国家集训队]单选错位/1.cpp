#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e7 + 71;
int n, A, B, C, a[N];
double ans;

int main() {
	scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
	for (int i = 2; i <= n; i++) a[i] = (1ll * a[i - 1] * A + B) % 100000001;
	for (int i = 1; i <= n; i++) a[i] = a[i] % C + 1;
	for (int i = 1; i <= n; i++) ans += 1. / std::max(a[i], a[i % n + 1]);
	printf("%.3f", ans);
}