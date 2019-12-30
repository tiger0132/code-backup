#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e3 + 31;

int n, k;
void qry(int *a, int &x, int &y) {
	printf("? ");
	for (int i = 1; i <= k; i++) printf("%d%c", a[i], " \n"[i == k]);
	fflush(stdout);
	scanf("%d%d", &x, &y);
}

int a[N], s[N], x, y, z, w, p, q;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; i++) a[i] = i;
	qry(a, x, y);
	for (int i = 1; i <= k; i++) a[i] = i == x ? n : i;
	qry(a, z, w);
	if (w > y)
		w = 1;
	else
		w = -1;
	for (int i = 1; i <= k; i++)
		if (i != x) {
			for (int j = 1; j <= k; j++) a[j] = j == i ? n : j;
			qry(a, p, q);
			if (p == x)
				s[i] = w;
			else
				s[i] = -w;
		}
	int ans = 1;
	for (int i = 1; i <= k; i++) ans += s[i] == -1;
	printf("! %d\n", ans);
	fflush(stdout);
}