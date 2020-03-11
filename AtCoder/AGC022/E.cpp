#include <algorithm>
#include <cstring>
#include <cstdio>

const int P = 1e9 + 7;

int n, a[22], *p = a, *q = a + 9;
char ch;
void $(int& x) { x += x >> 31 & P; }
int main() {
	for (p[0] = 1; (ch = getchar()) != '\n'; std::swap(p, q), memset(q, 0, 36))
		for (int i = 0; i < 9; i++) {
			if (ch != '1')
				if (i % 3 == 2)
					$(q[i - 1] += p[i] - P);
				else
					$(q[i + 1] += p[i] - P);
			if (ch != '0')
				if (i % 3 == 0)
					$(q[std::min(i + 3, 6)] += p[i] - P);
				else
					$(q[i - 1] += p[i] - P);
		}
	printf("%d", n == 2 ? p[3] : (1ll * p[0] + p[3] + p[4] + p[6] + p[7] + p[8]) % P);
}