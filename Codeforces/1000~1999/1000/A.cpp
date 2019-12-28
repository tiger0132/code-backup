#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>

const int N = 1e2 + 21;

std::multiset<std::string> a;
std::string s;
int n, ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) std::cin >> s, a.insert(s);
	for (int i = 1; i <= n; i++) {
		std::cin >> s;
		if (a.count(s))
			a.erase(a.find(s));
		else
			ans++;
	}
	printf("%d", ans);
}