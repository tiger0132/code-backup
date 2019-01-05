#include <cstdio>

int n, a[20];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", a+i);
	}
	for (int i = 0; i < (1 << n); i++) {
		int lans = 0;
		for (int j = 0; j < n; j++) {
			lans += (((i >> j) & 1) ? a[j] : -a[j]);
		}
		if (!(lans % 360)) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
}