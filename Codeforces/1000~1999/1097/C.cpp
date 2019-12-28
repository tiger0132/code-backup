#include <algorithm>
#include <cstring>
#include <cstdio>
#include <stack>
#include <map>

const int N = 5e5+55;

int mmp[N<<3];
std::stack<int> st;
int n, m, ans;
char s[N<<3];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s);
		m = strlen(s);
		int lf = 0, rf = 0, c;
		for (int j = 0; j < m; j++) {
			if (s[j] == ')') {
				if (st.empty() || st.top() == ')') st.push(')');
				else st.pop();
			} else st.push('(');
		}
		c = st.size();
		while (!st.empty()) {
			char ch = st.top(); st.pop();
			if (ch == '(') lf = 1;
			if (ch == ')') rf = 1;
		}
		if (!lf && !rf) ans++;
		else if (lf && !rf) mmp[N+c]++;
		else if (!lf && rf) mmp[N-c]++;
	}
	ans >>= 1;
	for (int i = 0; i < 500005; i++) {
		ans += std::min(mmp[N+i], mmp[N-i]);
	}
	printf("%d", ans);
}