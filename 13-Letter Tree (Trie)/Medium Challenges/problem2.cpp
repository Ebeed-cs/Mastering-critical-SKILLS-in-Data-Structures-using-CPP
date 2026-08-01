#include<iostream>
#include<vector>
#include<cstring>	// memset
using namespace std;

class trie {
private:
	static const int MAX_CHAR = 26;
	trie* child[MAX_CHAR];
	bool isLeaf{ };

	trie* find_node(string str, trie* ptr = nullptr) {
		if (!ptr) ptr = this;
		for (int i = 0; i < (int)str.size(); ++i) {
			int cur = str[i] - 'a';
			if (cur < 0 || cur >= MAX_CHAR)
				return nullptr;
			if (!ptr->child[cur])
				return nullptr;
			ptr = ptr->child[cur];
		}
		return ptr;
	}


public:
	trie() {
		memset(child, 0, sizeof(child));
	}

	void insert(string str, int idx = 0) {
		if (idx == (int)str.size())
			isLeaf = 1;
		else {
			int cur = str[idx] - 'a';
			if (child[cur] == 0)
				child[cur] = new trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	void auto_complete(const string& str,
		vector<string>& res,
		trie* cur = nullptr,
		string prefix = "") {
		if (!cur) {
			res.clear();
			cur = find_node(str);
			if (!cur) return;
			prefix = str;
		}
		if (cur->isLeaf)
			res.push_back(prefix);
		for (int i = 0; i < MAX_CHAR; ++i)
			if (cur->child[i])
				cur->child[i]->auto_complete(str, res, cur->child[i], prefix + (char)(i + 'a'));
	}
};

int main() {
	trie tree;

	tree.insert("abcd");
	tree.insert("ab");
	tree.insert("abx");
	tree.insert("abyz");
	tree.insert("xyz");
	tree.insert("a");
	tree.insert("bcd");

	vector<string> res;
	string target_word = "ab";
	tree.auto_complete(target_word, res);
	for (int i = 0; i < (int)res.size(); ++i)
		cout << res[i] << "\n";

	cout << "____________________\n";

	target_word = "xyz";
	tree.auto_complete(target_word, res);
	for (int i = 0; i < (int)res.size(); ++i)
		cout << res[i] << "\n";

	return 0;
}
