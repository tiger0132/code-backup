#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e5 + 52;
struct edge {
	int to, next, w;
} e[N << 1];
int n, head[N], cnt;
void ad(int x, int y, int z) { e[++cnt] = {y, x[head], z}, x[head] = cnt; }

std::queue<int> q;
int dis[N];
int main() {
	memset(head, -1, sizeof head);
	memset(dis, 0x3f, sizeof dis), dis[1] = 1;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) ad(i, (i + 1) % n, 1);
	for (int i = 1; i < n; i++) ad(i, i * 10 % n, 0);
	for (q.push(1); !q.empty(); q.pop())
		for (int x = q.front(), i = x[head], nx; ~i; i = e[i].next)
			if ((nx = e[i].to)[dis] > x[dis] + e[i].w) nx[dis] = x[dis] + e[i].w, q.push(nx);
	printf("%d", 0 [dis]);
}