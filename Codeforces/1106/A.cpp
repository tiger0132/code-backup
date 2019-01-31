#include <algorithm>
#include <cstdio>
#include <cstring>

char buf[999][999];
int n, ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%s", buf[i] + 1);
	for (int i = 2; i < n; i++) {
		for (int j = 2; j < n; j++) {
			if (buf[i][j] == 'X' && buf[i - 1][j - 1] == 'X' &&
				buf[i - 1][j + 1] == 'X' && buf[i + 1][j - 1] == 'X' &&
				buf[i + 1][j + 1] == 'X') {
				ans++;
			}
		}
	}
	printf("%d", ans);
}