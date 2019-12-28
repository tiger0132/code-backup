#include <cstdio>

int b, k, x;
long long a;

int main() {
	for (scanf("%d%d", &b, &k); k--;) {
		scanf("%d", &x);
		a = (a * b + x) % 2;
	}
	puts(a ? "odd" : "even");
}