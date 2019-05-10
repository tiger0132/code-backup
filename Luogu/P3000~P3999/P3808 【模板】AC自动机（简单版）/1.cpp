// luogu-judger-enable-o2
// just test
// TLE!

#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 62;

int trie[N][26], cnt, _;
int fail[N];
int val[N];

int ans[N];
int st[N];

void add(const char *str) {
	int pos = 0, n = strlen(str);
	for (int i = 0; i < n; i++) {
		int nx = str[i] - 97;
		if (!trie[pos][nx]) {
			trie[pos][nx] = ++cnt;
		}
		pos = trie[pos][nx];
	}
	val[pos] = ++_;
}

void ac() {
	queue<int> bfs;
	// fail[0] = 0;
	for (int i = 0; i < 26; i++) {
		int nx = trie[0][i];
		if (nx) {
			fail[nx] = 0;
			bfs.push(nx);
		}
	}
	while (!bfs.empty()) {
		int pos = bfs.front();
		bfs.pop();
		for (int i = 0; i < 26; i++) {
			int &nx = trie[pos][i];
			if (nx) {
				fail[nx] = trie[fail[pos]][i];
				bfs.push(nx);
			} else {
				nx = trie[fail[pos]][i];
			}
		}
	}
}

void query(const char *str) {
	int pos = 0, n = strlen(str);
	for (int i = 0; i < n; i++) {
		pos = trie[pos][str[i] - 97];
		for (int t = pos; t; t = fail[t]) {
			ans[val[t]]++;
		}
	}
}

char buf[N];
char src[N];
int n, ret;

int main() {
	// freopen("C:\\Users\\Administrator\\Documents\\testdata (15).in", "r", stdin);
	scanf("%d", &n);
	{
		memset(trie, 0, sizeof trie);
		memset(fail, 0, sizeof fail);
		memset(val, 0, sizeof val);
		memset(ans, 0, sizeof ans);
		memset(st, 0, sizeof st);
		cnt = _ = 0;

		for (int i = 1; i <= n; i++) {
			scanf("%s", buf);
			add(buf);
		}
		ac();
		scanf("%s", src);
		query(src);
		//		printf("%d\n", ret = *max_element(ans+1, ans+n+1));
		for (int i = 1; i <= n; i++) {
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}