#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int n, a[N], cnt[233], ans = 0;
int main() {
	scanf("%d", &n);
	a[0] = -1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		for (int j = 0; j < 30; j++)
			if ((a[i] >> j) & 1) cnt[j]++;
	}
	for (int i = 1; i <= n; i++) {
		int lans = 0;
		for (int j = 0; j < 30; j++)
			if (((a[i] >> j) & 1) && cnt[j] == 1) lans |= 1 << j;
		if (lans > a[ans]) ans = i;
	}
	printf("%d ", a[ans]);
	for (int i = 1; i <= n; i++)
		if (i != ans) printf("%d ", a[i]);
}