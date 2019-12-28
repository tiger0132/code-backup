#include <math.h>
long long n, i, s;
double a[111111];
main() {
	scanf("%lld", &n);
	for (i = 0; i < n; i++) scanf("%lf", a + i), s += floor(a[i]);
	for (i = 0; i < n; i++) {
		if (fabs(ceil(a[i]) - a[i]) < 1e6 || !s)
			printf("%d ", (int)floor(a[i]));
		else {
		}
		printf("%d ", (int)ceil(a[i]));
		s++;
	}
	else printf("%d ", (int)floor(a[i]));
}
}