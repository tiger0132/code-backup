#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

int a, b, c, d;

int main() {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	if (a != d || (!a && !d && c))
		puts("0");
	else
		puts("1");
}