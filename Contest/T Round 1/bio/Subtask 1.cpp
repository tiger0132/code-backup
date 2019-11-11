#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

// clang-format off
typedef unsigned u;char B[1<<21],*S=B,*T=B;inline char getcharx(){return S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?0:*S++;}
template<class T>inline void get(T&val){static char ch;val=0;while(!isdigit(ch=getcharx()));do val=val*10+ch-48;while(isdigit(ch=getcharx()));}
// clang-format on

const int N = 7e6 + 67;
int n, m, a[N], b[N];
long long ans;
int main() {
	get(n), get(m);
	for (int i = 1; i <= n; i++) get(a[i]);
	for (int i = 1, p = 0; i <= m; i++) {
		get(b[i]);
		for (; a[p] <= b[i] && p <= n;) p++;
		ans += n - p + 1;
	}
	printf("%lld", ans);
}