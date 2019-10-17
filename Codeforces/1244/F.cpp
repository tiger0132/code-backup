#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define L(x) (x + n - 1) % n
#define R(x) (x + 1) % n

const int N = 2e5 + 52, INF = 0x3f3f3f3f;

std::queue<int> q;
int n, k, t[N];
char s[N];
int main() {
	memset(t, 0x3f, sizeof t);
	scanf("%d%d%s", &n, &k, s);
	for (int i = 0; i < n; i++)
		if (s[L(i)] == s[i]) {
			t[i] = 0;
			if (s[i] != s[R(i)]) q.push(i);
		} else if (s[i] == s[R(i)]) {
			t[i] = 0;
			if (s[L(i)] != s[i]) q.push(i);
		}
	for (int x; !q.empty(); q.pop()) {
		x = q.front();
		if (t[L(x)] == INF) t[L(x)] = t[x] + 1, q.push(L(x));
		if (t[R(x)] == INF) t[R(x)] = t[x] + 1, q.push(R(x));
	}
	for (int i = 0; i < n; i++) {
		putchar((std::min(k, t[i]) ^ (s[i] == 'B')) & 1 ? 'B' : 'W');
	}
}