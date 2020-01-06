#include <algorithm>
#include <cstdio>
#include <cstring>

double p, f, a, b;
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf", &p);
		f += p * (3 * a + 3 * b + 1);
		a = p * (a + 2 * b + 1);
		b = (b + 1) * p;
	}
	printf("%.1f", f);
}