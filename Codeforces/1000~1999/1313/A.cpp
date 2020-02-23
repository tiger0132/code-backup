#include <algorithm>
#include <cstdio>
#include <cstring>

int a[3];

int main() {
	for (scanf("%*d"); ~scanf("%d%d%d", &a[0], &a[1], &a[2]);) {
		int ans = 0;
		if (a[0]) a[0]--, ans++;
		if (a[1]) a[1]--, ans++;
		if (a[2]) a[2]--, ans++;
		std::sort(a, a + 3);
		if (a[1] && a[2]) ans++, a[1]--, a[2]--;
		if (a[0] && a[2]) ans++, a[0]--, a[2]--;
		if (a[0] && a[1]) ans++, a[1]--, a[0]--;
		if (a[0] && a[1] && a[2]) ans++;
		printf("%d\n", ans);
	}
}