#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const int N = 2e6 + 62;

int ch[N][26], fail[N], v[N], c[N], nc;
struct ACAM {
	int root;
	void init() { root = ++nc; }
	void ins(const std::string &s) {
		int x = root;
		for (int i : s) {
			int &nx = ch[x][i - 'a'];
			if (!nx) nx = ++nc;
			x = nx;
		}
		x[c]++;
	}
	void build() {
		std::queue<int> q;
		for (int i = 0, nx; i < 26; i++)
			if ((nx = root[ch][i]))
				nx[fail] = root, q.push(nx);
			else
				root[ch][i] = root;
		for (; !q.empty(); q.pop()) {
			int x = q.front();
			if (!x[fail]) x[fail] = root;
			for (int i = 0; i < 26; i++) {
				int &nx = x[ch][i];
				if (nx)
					nx[fail] = x[fail][ch][i], q.push(nx);
				else
					nx = x[fail][ch][i];
			}
			x[v] = x[c] + x[fail][v];
		}
	}
	void merge(int &x, int y, int rx, int ry) {
		if ((x == rx) || (y == ry)) return x |= (y == ry ? x : y), void();
		x[v] += y[v];
		for (int i = 0; i < 26; i++) merge(x[ch][i], y[ch][i], rx, ry);
	}
	int qry(const std::string &s) {
		int ret = 0, x = root;
		for (int i : s) {
			x = x[ch][i - 'a'];
			ret += x[v];
		}
		return ret;
	}
};
struct _bg {
	std::vector<std::string> v;
	int st[N], top;
	ACAM acam[N];
	void ins(const std::string &s) {
		int lb = v.size();
		v.push_back(s);
		ACAM tmp;
		tmp.init();
		while (top) {
			if (lb - st[top] > v.size() - lb) break;
			tmp.merge(tmp.root, acam[top].root, tmp.root, acam[top].root), lb = st[top--];
		}
		st[++top] = lb, acam[top] = tmp;
		for (int i = lb; i < v.size(); i++) acam[top].ins(v[i]);
		acam[top].build();
	}
	int qry(const std::string &s) {
		int ret = 0;
		for (int i = 1; i <= top; i++) ret += acam[i].qry(s);
		return ret;
	}
} ds, rm;

char s[N];
int n, op;
int main() {
	for (scanf("%d", &n); n--;) {
		scanf("%d%s", &op, s);
		if (op == 1)
			ds.ins(s);
		else if (op == 2)
			rm.ins(s);
		else {
			printf("%d\n", ds.qry(s) - rm.qry(s));
			fflush(stdout);
		}
	}
}