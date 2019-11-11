#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e6 + 61;

int n, s, t, ban[11], v[N], pre[N], digit[N];
std::queue<int> q;
void prt(int x) {
	if (x[pre]) prt(x[pre]);
	printf("%d", x[digit]);
}
int main() {
	for (scanf("%d%d", &n, &s); s--;) scanf("%d", &t), t[ban] = 1;
	for (int i = 1; i < 10; i++)
		if (!i[ban]) q.push(i), i[v] = 1, i[digit] = i;
	for (int x; !q.empty(); q.pop()) {
		if (!(x = q.front())) return prt(x), 0;
		for (int i = 0, nx; i < 10; i++)
			if (!i[ban] && !(nx = (x * 10 + i) % n)[v])
				nx[pre] = x, nx[v] = 1, nx[digit] = i, q.push(nx);
	}
	puts("-1");
}