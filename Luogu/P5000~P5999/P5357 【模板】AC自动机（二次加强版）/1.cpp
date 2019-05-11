#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 2e6 + 62;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

int ch[N][26], fail[N], v[N], c;
int ins(char *s) {
	int x = 0;
	for (int i = 0; s[i]; i++) {
		int &nx = ch[x][s[i] - 'a'];
		if (!nx) nx = ++c;
		x = nx;
	}
	return x;
}
void build() {
	std::queue<int> q;
	for (int i = 0, nx; i < 26; i++)
		if (nx = ch[0][i]) fail[nx] = 0, q.push(nx);
	for (; !q.empty(); q.pop()) {
		int x = q.front();
		for (int i = 0; i < 26; i++) {
			int &nx = ch[x][i];
			if (nx)
				fail[nx] = ch[fail[x]][i], q.push(nx);
			else
				nx = ch[fail[x]][i];
		}
	}
}
void dfs(int x, int p) {
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x), v[x] += v[nx];
}

std::vector<int> endp;
char s[N];
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%s", s), endp.push_back(ins(s));
	build();
	scanf("%s", s);
	for (int i = 0, x = 0; s[i]; i++) v[x = ch[x][s[i] - 'a']]++;
	for (int i = 1; i <= c; i++) addedge(i, fail[i]);
	dfs(0, 0);
	for (int i : endp) printf("%d\n", v[i]);
}