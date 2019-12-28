#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>

const int N = 2e5 + 52;

int n, p, a[N];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	p = std::max_element(a, a + n) - a;
	puts(std::is_sorted(a, a + p) && std::is_sorted(a + p + 1, a + n, std::greater<int>()) ? "YES" : "NO");
}