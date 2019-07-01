#include <algorithm>
#include <cmath>
#include <cstdio>

int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int l = 1, r = n; l <= r; l++, r--) {
		if (l == r)
			for (int p1 = 1, p2 = m; p1 <= p2; p1++, p2--)
				if (p1 == p2)
					printf("%d %d\n", l, p1);
				else
					printf("%d %d\n%d %d\n", l, p1, l, p2);
		else
			for (int p1 = 1, p2 = m; p1 <= m; p1++, p2--) printf("%d %d\n%d %d\n", l, p1, r, p2);
	}
}