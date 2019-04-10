#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>

const int N = 1e5 + 51;
struct edge {
	int to, next;
} e[N << 1];
int head[N], deg[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, head[x]}, head[x] = cnt, deg[y]++; }

std::priority_queue<int> pq;
std::stack<int> out;
int _, n, m, x, y;
bool flag;

int main() {
	for (scanf("%d", &_); _--;) {
		memset(head, 0, sizeof head), memset(deg, 0, sizeof deg), cnt = 0, flag = false;
		for (scanf("%d%d", &n, &m); m--;) {
			scanf("%d%d", &x, &y);
			addedge(y, x);
		}
		for (int i = 1; i <= n; i++)
			if (!deg[i]) pq.push(i);
		for (int x; !pq.empty();)
			for (int i = head[x = pq.top()], nx = (out.push(x), pq.pop(), 0); i; i = e[i].next)
				if (!--deg[nx = e[i].to]) pq.push(nx);
		if (flag || out.size() < n) {
			puts("Impossible!");
			while (!out.empty()) out.pop();
			continue;
		}
		for (; !out.empty(); out.pop()) printf("%d%c", out.top(), " \n"[out.size() == 1]);
	}
}