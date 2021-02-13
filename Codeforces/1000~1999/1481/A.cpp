#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int x, y, n;
char s[N];
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &x, &y);) {
		int cx = 0, cy = 0, f = 1;
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for (int i = 1; (cx != x || cy != y) && i <= n; i++) {
			int dx = 0, dy = 0;
			if (s[i] == 'U') dy = 1;
			if (s[i] == 'D') dy = -1;
			if (s[i] == 'L') dx = -1;
			if (s[i] == 'R') dx = 1;

			if (abs(x - (cx + dx)) < abs(x - cx) || abs(y - (cy + dy)) < abs(y - cy))
				cx += dx, cy += dy;
		}
		puts(cx == x && cy == y ? "YES" : "NO");
	}
}