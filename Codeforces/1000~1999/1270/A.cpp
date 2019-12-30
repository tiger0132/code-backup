#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, A, B, m1, m2, x;
int main() {
	for (scanf("%*d"); ~scanf("%d%d%d", &n, &A, &B);) {
		m1 = m2 = 0;
		for (int i = 1; i <= A; i++) scanf("%d", &x), m1 = std::max(x, m1);
		for (int i = 1; i <= B; i++) scanf("%d", &x), m2 = std::max(x, m2);
		puts(m1 > m2 ? "YES" : "NO");
	}
}