#include <algorithm>
#include <cstdio>
#include <cstring>

int a, b, c, d, l, r;
int main() {
	for (scanf("%*d"); ~scanf("%d%d%d%d", &a, &b, &c, &d);) {
		if (a > b) std::swap(a, b);
		l = std::max(a, std::min(b, c - d));
		r = std::max(a, std::min(b, c + d));
		printf("%d\n", b - a - r + l);
	}
}