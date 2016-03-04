#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
#include <string>
#include <set>
#include <map>
using namespace std;
const int COLUMN = 80;
queue<int> query(const string &sentence, const string &pattern) {
	int t_len = sentence.length();
	int p_len = pattern.length();
	// next[i] indicates the max-prefix of pattern[0, i](inclusive).
	vector<int> next(p_len);
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
	queue<int> pos;
	while (i < t_len && j < p_len) {
		// if sentence and pattern corresponsive element match, then increase them.
		if (sentence[i] == pattern[j]) i++, j++;
		// if they don't match at all and j == 0 then sentence should move its index.
		else if (j == 0) i++;
		// Maybe there is other similar pattern in sentence, we only move j to next[j - 1]
		else j = next[j - 1];
		if (j == p_len) {
			pos.push(i - j);
			j = 0;
		}
	}
	return pos;
}

map<int, queue<int> > query(const vector<string> &article, const string pattern) {
	map<int, queue<int> > res;
	for (int i = 0; i < article.size(); i++)
		res[i] = query(article[i], pattern);
	return res;
}

void print(ostream &out, const string& sentence, queue<int> pos) {
	int len = sentence.length();
	int line = len / COLUMN + 1;
	int p = -1;
	if (!pos.empty()) { 
		p = pos.front(); pos.pop();
	}
	for (int i = 0; i < line; i++) {
		out << endl << sentence.substr(i * COLUMN, COLUMN);
		int dist = i * COLUMN;
		int flag = true;
		while (p >= i * COLUMN && p < (i + 1) * COLUMN) {
			if (flag) {flag = !flag; out << endl;}
			for (int blank = 0; blank < p - dist; blank++) out << " ";
			out << "^";
			if (!pos.empty()) {
				dist = p; p = pos.front(); pos.pop(); 
			} else break;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		cout << "Need File name. Please try again." << endl;
		return -1;
	}
	ifstream fin(argv[1]);
	vector<string> article;
	string sentence;
	while (getline(fin, sentence))
		article.push_back(sentence);
	map<int, queue<int> > line = query(article, "the");
	for (int i = 0; i < article.size(); i++) {
		cout << "\n\nline (" << i << ")";
		print(cout, article[i], line[i]);
	}
	cout << endl;
	return 0;
}
