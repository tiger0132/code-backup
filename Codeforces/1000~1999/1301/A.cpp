#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e2 + 21;

char a[N], b[N], c[N];
int n;
int main() {
	for (scanf("%*d"); ~scanf("%s%s%s", a, b, c);) {
		n = strlen(a);
		for (int i = 0; i < n; i++)
			if ((a[i] == b[i] && a[i] != c[i]) ||
				(a[i] != b[i] && a[i] != c[i] && b[i] != c[i])) {
				puts("NO");
				goto end;
			}
		puts("YES");
	end:;
	}
}