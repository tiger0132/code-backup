#include <cstdio>

char a[3], b[3];

int main() {
	scanf("%s", a);
	for (int i = 0; i < 5; i++) {
		scanf("%s", b);
		if (a[0] == b[0] || a[1] == b[1]) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
}