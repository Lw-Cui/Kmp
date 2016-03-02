#include <cstdio>
#include <cstring>
int main() {
	char text[100] = "BCBAABACAABABACAA";
	int t_len = strlen(text);
	char pattern[100] = "ABABAC";
	int p_len = strlen(pattern);
	// next[i] indicates the max-prefix of pattern[0, i](inclusive).
	int next[100];
	next[0] = 0;
	for (int i = 1; i < p_len; i++) {
		/* P is also the next element of end of max-prefix.
		 * e.g.char *s = ababac; s[5] = 'c', next[5 - 1] = 3, s[next[5 - 1]] = 'b'
		 */
		int p = next[i - 1];
		/* p > 0 means that there is at least one prefix in s[0, i - 1] 
		 * pattern[p] != pattern[i] means the prefix doesn't match
	     */
		while (p > 0 && pattern[p] != pattern[i])
			/* IMPORTANT: if ABC XYZ has max-prefix 3, ABC has max-prefix 1
			 * then A = Z, which is a smaller prefix, but maybe match new element
			 */
			p = next[p - 1];
		/*	if p == 0 and pattern[p] != pattern[i] then there is no prefix for the element
		 *	else if pattern[p] == pattern[i] then we find a new prefix.
		 */
		if (pattern[p] != pattern[i]) next[i] = 0;
		else next[i] = p + 1;
	}
 	int i = 0, j = 0;
	while (i < t_len && j < p_len)
		// if text and pattern corresponsive element match, then increase them.
		if (text[i] == pattern[j]) i++, j++;
		// if they don't match at all and j == 0 then text should move its index.
		else if (j == 0) i++;
		// Maybe there is other similar pattern in text, we only move j to next[j - 1]
		else j = next[j - 1];
	if (j == p_len) {
		for (int ite = 0; ite < t_len; ite++) {
			if (ite == i || ite == i - j) putchar(' ');
			putchar(text[ite]);
		}
		printf("\n");
		for (int ite = 0; ite <= i - j; ite++) putchar(' ');
		puts(pattern);
	}
	return 0;
}
