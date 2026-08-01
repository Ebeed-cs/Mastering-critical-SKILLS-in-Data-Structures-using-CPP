#include<iostream>
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
		if (idx == (int)str.size())
			isLeaf = 1;
		else {
			int cur = str[idx] - 'a';
			if (child[cur] == 0)
				child[cur] = new trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	bool word_exist(string str, int idx = 0) {
		if (idx == (int)str.size())
			return isLeaf;	// there is a string marked here

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;	// such path don't exist

		return child[cur]->word_exist(str, idx + 1);
	}

	bool prefix_exist(string str, int idx = 0) {
		if (idx == (int)str.size())
			return true;	// all subword covered

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;	// such path don't exist

		return child[cur]->prefix_exist(str, idx + 1);
	}

	string problem2(const string& str, int idx = 0) {
		if (idx == (int)str.size())
			return str;
		int cur = str[idx] - 'a';
		if (!child[cur])
			return str;
		if (child[cur]->isLeaf)
			return str.substr(0, idx + 1);
		return child[cur]->problem2(str, idx + 1);
	}
};

int main() {
	trie root;

	root.insert("xyz");
	root.insert("xyzeA");
	root.insert("a");
	root.insert("bc");

	cout << root.problem2("we") << "\n"; // ...
	cout << root.problem2("x") << "\n";	// x
	cout << root.problem2("xyzabc") << "\n"; // xyz

	return 0;
}
