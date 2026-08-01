#include<iostream>
#include<vector>
#include<cstring>	// memset
using namespace std;

class Trie {
private:
	static const int MAX_CHAR = 26;
	Trie* child[MAX_CHAR];
	bool isLeaf{ };
public:
	Trie() {
		memset(child, 0, sizeof(child));
	}

	void insert(string str, int idx = 0) {
		if (idx == (int)str.size())
			isLeaf = 1;
		else {
			int cur = str[idx] - 'a';
			if (child[cur] == 0)
				child[cur] = new Trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	bool problem3(const string& str, int idx = 0, int changes_used = 0, Trie* cur = nullptr) {
		if (!cur) cur = this;

		if (idx == (int)str.size())
			return cur->isLeaf && changes_used == 1;

		int correct = str[idx] - 'a';

		for (int i = 0; i < MAX_CHAR; ++i) {
			if (!cur->child[i]) continue;

			int new_changes = changes_used + (i != correct ? 1 : 0);
			if (new_changes > 1) continue;

			if (cur->child[i]->problem3(str, idx + 1, new_changes, cur->child[i]))
				return true;
		}
		return false;
	}
};

int main() {
	Trie* tree = new Trie();
	tree->insert("hello");
	tree->insert("leetcode");

	cout << tree->problem3("hello") << "\n"; // 0
	cout << tree->problem3("xello") << "\n"; // 1
	cout << tree->problem3("xyllo") << "\n"; // 0

	return 0;
}
