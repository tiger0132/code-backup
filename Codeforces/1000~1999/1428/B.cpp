#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5 + 53;

char s[N];
int n;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		scanf("%s", s);
		bool L = false, R = false;
		int ans = 0;
		for (int i = 0; i < n; i++) {
			L |= s[i] == '<';
			R |= s[i] == '>';
			if (s[i] == '-' || s[(i + 1) % n] == '-') ans++;
		}
		if (L + R <= 1)
			printf("%d\n", n);
		else
			printf("%d\n", ans);
	}
}