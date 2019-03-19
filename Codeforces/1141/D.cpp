#include <algorithm>
#include <cstdio>
#include <queue>

const int N = 2e5 + 52;

std::queue<int> p[27], q[27], a1, a2;
char a[N], b[N];
int n;
int main() {
	scanf("%d%s%s", &n, a, b);
	for (int i = 0; i < n; i++) {
		p[a[i] == '?' ? 26 : a[i] - 'a'].push(i + 1);
		q[b[i] == '?' ? 26 : b[i] - 'a'].push(i + 1);
	}
	for (int i = 0; i < 27; i++) {
		while (!p[i].empty() && !q[i].empty()) {
			a1.push(p[i].front());
			a2.push(q[i].front());
			p[i].pop(), q[i].pop();
		}
		while (!p[i].empty() && !q[26].empty()) {
			a1.push(p[i].front());
			a2.push(q[26].front());
			p[i].pop(), q[26].pop();
		}
		while (!p[26].empty() && !q[i].empty()) {
			a1.push(p[26].front());
			a2.push(q[i].front());
			p[26].pop(), q[i].pop();
		}
	}
	printf("%d\n", a1.size());
	while (!a1.empty()) {
		printf("%d %d\n", a1.front(), a2.front());
		a1.pop(), a2.pop();
	}
}