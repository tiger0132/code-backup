n, st[222222], v[222222], top;
char s[222222];
main(i, j, k, l, x) {
	for (scanf("%*d"); ~scanf("%d%s", &n, s);) {
		top = 0;
		for (i = 0; i < n; i++) {
			while (top && st[top][s] > i[s]) top--;
			st[++top] = i;
		}
		for (i = 1; i <= top; i++) st[i][v] = 1;
		for (i = 0; i < n; i++)
			if (!i[v]) {
				x = i[s];
				break;
			}
		while (top && st[top][s] > x) st[top--][v] = 0;
		for (i = 0, l = 0; i < n; i++)
			if (!i[v]) {
				if (i[s] < l) {
					puts("-");
					for (i = 0; i < n; i++) i[v] = 0;
					goto end;
				}
				l = i[s];
			}
		for (i = 0; i < n; i++) putchar(!i[v] + '1'), i[v] = 0;
		puts("");
	end:;
	}
}