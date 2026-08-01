#include<iostream>
#include<algorithm>
#include<cstring>	// memset
using namespace std;

class trie {
private:
	static const int MAX_CHAR = 26;
	trie* child[MAX_CHAR];
	bool isLeaf{ };

public:
	trie() {
		// set an array to 0s. Here pointers to null
		memset(child, 0, sizeof(child));
	}

	void insert(string str, int idx = 0) {
		if (!idx)
			reverse(str.begin(), str.end());
		if (idx == (int)str.size())
			isLeaf = 1;
		else {
			int cur = str[idx] - 'a';
			if (child[cur] == 0)
				child[cur] = new trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	bool problem3(string str, int idx = 0) {
		if (!idx)
			reverse(str.begin(), str.end());

		if (idx == (int)str.size())
			return true;	// all subword covered

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;	// such path don't exist

		return child[cur]->problem3(str, idx + 1);
	}

};

int main() {
	trie root;
	root.insert("abcd");
	root.insert("xyz");
	root.insert("abf");
	root.insert("xn");
	root.insert("ab");
	root.insert("bcd");

	cout << root.problem3("cd") << "\n";
	cout << root.problem3("cc") << "\n";

	return 0;
}
