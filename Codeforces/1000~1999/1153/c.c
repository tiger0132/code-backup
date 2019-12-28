char s[333333], t[333333];
x, y, c;
main(n, i) {
	scanf("%d%s", &n, s + 1);
	for (i = 1; i <= n; i++) {
		x += s[i] == '(';
		y += s[i] == ')';
	}
	x = n / 2 - x, y = n / 2 - y;
	if (n % 2 || x < 0 || y < 0) return puts(":("), 0;
	for (i = 1; i <= n; i++) {
		if (s[i] == '(')
			t[i] = s[i], c++;
		else if (s[i] == ')')
			t[i] = s[i], c--;
		else {
			if (x)
				t[i] = '(', x--, c++;
			else
				t[i] = ')', y--, c--;
		}
		if (c < 0 || (!c && i < n)) return puts(":("), 0;
	}
	puts(t + 1);
	// puts(t + 1);
}