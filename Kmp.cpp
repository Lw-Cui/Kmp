#include <cstdio>
#include <cstring>
int main() {
	char origin[100] = "BCBAABACAABABACAA";
	int olen = strlen(origin);
	//char sub[100] = "ABABAC";
	char sub[100] = "ABABAA";
	int slen = strlen(sub);
	// next[i] indicates the max-prefix of sub[0, i](inclusive).
	int next[100];
	next[0] = 0;
	for (int i = 1; i < slen; i++) {
		/* P is also the index where the max-prefix end.
		e.g.char *s = ababac; s[5] = 'c', next[5 - 1] = 3, s[next[5 - 1]] = 'b'
		*/
		int p = next[i - 1];
		/* if p == 0 then we'd know it's the first element or it has no prefix.
		   if sub[p] == sub[i] then we'd know we found the new max-prefix.
	    */
		while (p > 0 && sub[p] != sub[i])
			p = next[p - 1];
		if (sub[p] != sub[i]) next[i] = 0;
		else next[i] = p + 1;
	}
	for (int i = 0; i < slen; i++)
		printf("%d ", next[i]);
	/*
 	int i = 0, j = 0;
	while (i < olen && j < slen)
		if (origin[i] == sub[j]) {
			i++, j++;
		} else if (j == 0) {
			i++;
		} else {
			j = next[j - 1];
		}
		*/
	return 0;
}
