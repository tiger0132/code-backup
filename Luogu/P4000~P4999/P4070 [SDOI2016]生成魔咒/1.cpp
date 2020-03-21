#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

const int N = 2e5 + 52;

int len[N], link[N], nc = 1, last = 1;
std::map<int, int> tr[N];
long long ans;
void ins(int c) {
	int cur = ++nc, p = last, q, cl;
	cur[len] = last[len] + 1;
	for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
	if (!p)
		cur[link] = 1;
	else if (p[len] + 1 == q[len])
		cur[link] = q;
	else {
		cl = ++nc, cl[len] = p[len] + 1, cl[link] = q[link], cl[tr] = q[tr];
		for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
		q[link] = cur[link] = cl;
	}
	printf("%lld\n", ans += cur[len] - cur[link][len]), last = cur;
}

int x;
int main() {
	for (scanf("%*d"); ~scanf("%d", &x);) ins(x);
}