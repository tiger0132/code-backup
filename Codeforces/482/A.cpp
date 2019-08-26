#include <algorithm>
#include <cstdio>
#include <cstring>

int n, k, x, y;

int main() {
	scanf("%d%d", &n, &k), x = 1, y = n;
	for (int i = 1; i <= k; i++) {
		printf("%d ", x);
		x += i % 2 ? 1 : -1;
		std::swap(x, y);
	}
	for (n -= k; n--; y += y < x ? 1 : -1) printf("%d ", y);
}