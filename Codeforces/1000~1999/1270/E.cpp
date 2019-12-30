#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

typedef std::pair<int, int> pii;
typedef long long ll;
const int N = 1e3 + 31, M = 2e6 + 62;

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int n, c[2][2], x[N], y[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
	while (1) {
		memset(c, 0, sizeof c);
		for (int i = 1; i <= n; i++) c[x[i] & 1][y[i] & 1]++;
		if ((c[0][0] + c[1][1]) && (c[0][1] + c[1][0])) {
			printf("%d\n", c[0][1] + c[1][0]);
			for (int i = 1; i <= n; i++)
				if ((x[i] ^ y[i]) & 1) printf("%d ", i);
			return 0;
		} else if ((c[0][0] || c[0][1]) && (c[1][0] || c[1][1])) {
			printf("%d\n", c[1][0] | c[1][1]);
			for (int i = 1; i <= n; i++)
				if (x[i] & 1) printf("%d ", i);
			return 0;
		}
		for (int i = 1; i <= n; i++) x[i] >>= 1, y[i] >>= 1;
	}
}