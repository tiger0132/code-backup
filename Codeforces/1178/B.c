char s[1111111];
a[1111111];
long long ans;
main(n, i) {
	scanf("%s", s);
	n = strlen(s);
	for (i = 1; i < n; i++) a[i] = a[i - 1] + (s[i - 1] == s[i] && s[i] == 'v');
	for (i = 2; i < n; i++)
		if (s[i] == 'o') ans += 1ll * a[i - 1] * (a[n - 1] - a[i]);
	printf("%lld", ans);
}