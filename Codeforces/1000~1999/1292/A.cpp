#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int n, x, y, a[3][N], cnt;
int main() {
	for (scanf("%d%*d", &n); ~scanf("%d%d", &x, &y);) {
		a[x][y] ^= 1;
		if (!a[x][y])
			cnt -= a[3 - x][y - 1] + a[3 - x][y] + a[3 - x][y + 1];
		else
			cnt += a[3 - x][y - 1] + a[3 - x][y] + a[3 - x][y + 1];
		puts(cnt ? "No" : "Yes");
	}
}