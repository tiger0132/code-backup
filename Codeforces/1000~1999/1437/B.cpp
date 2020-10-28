#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

char s[N];
int n;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		scanf("%s", s + 1);
		int ans = 0;
		for (int i = 1; i < n; i++) ans += (s[i] == s[i + 1]);
		printf("%d\n", (ans + 1) / 2);
	}
}