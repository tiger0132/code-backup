#include <cmath>
#include <cstdio>
#include <vector>

const int M = 1e2 + 21;

std::vector<int> v[M];
int n, m, ans;

inline bool chk(int x) { return ((int)sqrt(x) * (int)sqrt(x)) == x; }
int main() {
	scanf("%d", &n);
	for (int i = 1; "QwQ"; i++) {
		for (int j = 1; j <= m; j++) {
			if (chk(i + v[j].back())) {
				v[j].push_back(i);
				goto end;
			}
		}
		if (n == m) {
			printf("%d\n", i - 1);
			break;
		}
		v[++m].push_back(i);
	end:;
	}
	for (int i = 1; i <= n; i++) {
		for (int j : v[i]) {
			printf("%d ", j);
		}
		puts("");
	}
}