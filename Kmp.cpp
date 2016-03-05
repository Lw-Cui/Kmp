#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <cstring>
#include <string>
#include <set>
#include <map>
using namespace std;
const int COLUMN = 80;
const int ROW = 35;
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

map<int, queue<int> > query(const vector<string> &article,
		const string pattern, int &cnt) {
    map<int, queue<int> > res;
	for (int i = 0; i < article.size(); i++) {
		res[i] = query(article[i], pattern);
		cnt += res[i].size();
	}
	return res;
}

ostream& newline(ostream &out) {
    static int num = 0;
    out << endl;
    if (++num > ROW) {
        getchar();
        system("clear");
        num = 0;
    }
    return out;
}

void print(ostream &out, const string& sentence, queue<int> pos) {
	int len = sentence.length();
	// Because of the screen limitation there is at most COLUMN character in a line.
	int line = len / COLUMN + (len % COLUMN ? 1: 0);
	int p = -1;
	if (!pos.empty()) { 
		p = pos.front(); pos.pop();
	}
	// Divide the whole sentence into len / COLUMN( + 1) line.
	for (int i = 0; i < line; i++) {
		int offset = i * COLUMN;
		newline(out) << sentence.substr(offset, COLUMN);
		bool flag = true;
		// when the postion is in this line we print "^"
		while (p >= i * COLUMN && p < (i + 1) * COLUMN) {
			if (flag) {
				newline(out); flag = !flag;
			}
			// offset indicates the distance between "^"
			for (int blank = 0; blank < p - offset; blank++) out << " ";
			out << "^";
			if (!pos.empty()) {
			// update offset
				offset = p + 1; p = pos.front(); pos.pop(); 
			} else {
				p = -1;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cout << "Need File name. Please try again." << endl;
		return -1;
	}
	ifstream fin(argv[1]);
	vector<string> article;
	string sentence;
	while (getline(fin, sentence))
		article.push_back(sentence);
	int cnt = 0;
	clock_t start = clock();
    map<int, queue<int> > line = query(article, argv[2], cnt);
	clock_t end = clock();
	printf("Find pattern %d, Elapse time: %.2f",
			cnt, (double)(end - start) / CLOCKS_PER_SEC);
	for (int i = 0; i < article.size(); i++)
		if (!line[i].empty()) {
            newline(cout);
			newline(cout) << "line (" << i << ")";
			print(cout, article[i], line[i]);
		}
	cout << endl;
	return 0;
}
