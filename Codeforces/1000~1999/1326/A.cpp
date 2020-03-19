#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int n;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		if (n == 1)
			puts("-1");
		else {
			putchar('2');
			for (int i = 1; i < n; i++) putchar('3');
			puts("");
		}
	}
}