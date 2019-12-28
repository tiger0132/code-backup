#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e5 + 51;

int n, m, a[N];
ll x, y;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n / 2; i++) x += a[i];
	for (int i = n / 2 + 1; i <= n; i++) y += a[i];
	printf("%lld", x * x + y * y);
}