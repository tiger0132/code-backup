#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, out[N], top;
char s[N], t[N];

void flip(int x) { out[++top] = x; }
int main() {
	for (scanf("%*d"); ~scanf("%d%s%s", &n, s + 1, t + 1);) {
		for (int i = n, j = 0, id = 1; i >= 1; i--, j ^= 1) {
			if (t[i] == (s[id] ^ j)) flip(1);
			flip(i);
			id = n + 1 + j - id;
		}
		printf("%d ", top);
		for (int i = 1; i <= top; i++) printf("%d ", out[i]);
		puts("");
		top = 0;
	}
}