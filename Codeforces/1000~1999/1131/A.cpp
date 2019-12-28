#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

ll a, b, c, d;

int main() {
	scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
	printf("%lld", 2 * (a + b + d + 2));
}