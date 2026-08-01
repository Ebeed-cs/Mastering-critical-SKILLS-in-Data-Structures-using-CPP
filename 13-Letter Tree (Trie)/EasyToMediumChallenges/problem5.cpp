#include<iostream>
#include<map>
#include<vector>
#include<cstring>	// memset
using namespace std;

class trie {
private:
	map<string, trie*> child;
	bool isLeaf{ };

public:
	trie() {}

	void insert(vector<string>& path, int idx = 0) {
		if (idx == (int)path.size())
			isLeaf = 1;
		else {
			string cur = path[idx];
			if (child.find(cur) == child.end())
				child[cur] = new trie();
			child[cur]->insert(path, idx + 1);
		}
	}

	bool subpath_exist(const vector<string>& path, int idx = 0) {
		if (idx == (int)path.size())
			return true;

		string cur = path[idx];
		if (child.find(cur) == child.end())
			return false;	// such path don't exist

		return child[cur]->subpath_exist(path, idx + 1);
	}
};

int main() {
	trie tree;

	vector<string> path;

	path = { "home", "software", "eclipse" };
	tree.insert(path);

	path = { "home", "software", "eclipse", "bin" };
	tree.insert(path);

	path = { "home", "installed", "gnu" };
	tree.insert(path);

	path = { "user", "mostafa", "tmp" };
	tree.insert(path);

	path = { "user", "mostafa", "tmp" };
	cout << tree.subpath_exist(path) << "\n"; // 1

	path = { "user", "mostafa" };
	cout << tree.subpath_exist(path) << "\n"; // 1

	path = { "user", "mostafa", "private" };
	cout << tree.subpath_exist(path) << "\n"; // 0

	return 0;
}
