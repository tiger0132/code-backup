#include <algorithm>
#include <cstdio>
#include <cstring>

int n, x, s, zc;

int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		s = zc = 0;
		while (n--) {
			scanf("%d", &x);
			s += x;
			zc += !x;
		}
		if (!zc)
			puts(s ? "0" : "1");
		else
			printf("%d\n", zc + !(s + zc));
	}
}