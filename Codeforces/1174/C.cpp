#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, a[N], d;
int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		if (!a[i]) {
			d++;
			for (int j = i; j <= n; j += i)
				if (!a[j]) a[j] = d;
		}
	}
	for (int i = 2; i <= n; i++) printf("%d ", a[i]);
}