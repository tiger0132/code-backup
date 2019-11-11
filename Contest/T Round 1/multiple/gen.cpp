#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e6 + 61;

int n, A, B, s, t, ban[11], v[N], pre[N], digit[N];
std::queue<int> q;
void prt(int x) {
	if (x[pre]) prt(x[pre]);
	printf("%d", x[digit]);
}
int cnt(int x) {
	if (x[pre]) return cnt(x[pre]) + 1;
	return 1;
}
int main() {
	// scanf("%d", &n);
	for (n = 850000; n >= 0; n--)
		for (A = 0; A <= 9; A++)
			for (B = A + 1; B <= 9; B++) {
				memset(v, 0, sizeof v);
				memset(pre, 0, sizeof pre);
				memset(digit, 0, sizeof digit);
				if (A == B) continue;
				for (int i = 0; i < 10; i++) i[ban] = i != A && i != B;
				for (int i = 1; i < 10; i++)
					if (!i[ban]) q.push(i), i[v] = 1, i[digit] = i;
				for (int x; !q.empty(); q.pop()) {
					if (!(x = q.front())) {
						if (cnt(x) > 30) printf("%d %d %d\n", n, A, B), prt(x), puts("");
						goto end;
					}
					for (int i = 0, nx; i < 10; i++)
						if (!i[ban] && !(nx = (x * 10 + i) % n)[v])
							nx[pre] = x, nx[v] = 1, nx[digit] = i, q.push(nx);
				}
				// printf("%d %d %d\nNO SOL\n", n, A, B);
			end:
				while (!q.empty()) q.pop();
			}
}