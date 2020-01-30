#include <algorithm>
#include <cstdio>
#include <cstring>

int n;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		n -= 2;
		putchar(n % 2 ? '7' : '1');
		n &= ~1;
		while (n) n -= 2, putchar('1');
		puts("");
	}
}