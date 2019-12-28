char s[1111111], t1[1111111], t2[1111111];
n1, n2;
main(n, i, j) {
	scanf("%s", s);
	n = strlen(s);
	for (i = 0, j = n - 1; i <= j;) {
		if (i + 1 == j && s[i] != s[j]) {
			t1[n1++] = s[i];
			break;
		}
		if (i == j) {
			if (s[i] == s[j]) t1[n1++] = s[i];
			break;
		}
		if (s[i] == s[j])
			t1[n1++] = t2[n2++] = s[i], i++, j--;
		else if (i < j - 1 && s[i] == s[j - 1])
			t1[n1++] = t2[n2++] = s[i], i++, j -= 2;
		else if (i + 1 < j && s[i + 1] == s[j])
			t1[n1++] = t2[n2++] = s[j], i += 2, j--;
		else
			i++, j--;
	}
	printf("%s", t1);
	for (i = n2 - 1; i >= 0; i--) putchar(t2[i]);
}