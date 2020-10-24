#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

int a, b, c, d;

int main() {
	for (scanf("%*d"); ~scanf("%d%d%d%d", &a, &b, &c, &d);) {
		printf("%d\n", abs(c - a) + abs(d - b) + (a == c || b == d ? 0 : 2));
	}
}