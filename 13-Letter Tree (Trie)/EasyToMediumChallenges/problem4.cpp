#include<iostream>
#include<map>
#include<cstring>	// memset
using namespace std;

class trie {
private:
	map<char, trie*> child;
	bool isLeaf{ };

public:
	trie() {
		// map intialize it self 
	}

	void insert(string str, int idx = 0) {
		if (idx == (int)str.size())
			isLeaf = 1;
		else {
			char cur = str[idx];
			if (child.find(cur) == child.end())
				child[cur] = new trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	bool word_exist(string str, int idx = 0) {
		if (idx == (int)str.size())
			return isLeaf;	// there is a string marked here

		char cur = str[idx];
		if (child.find(cur) == child.end())
			return false;	// such path don't exist

		return child[cur]->word_exist(str, idx + 1);
	}

	bool prefix_exist(string str, int idx = 0) {
		if (idx == (int)str.size())
			return true;	// all subword covered

		char cur = str[idx];
		if (child.find(cur) == child.end())
			return false;	// such path don't exist

		return child[cur]->prefix_exist(str, idx + 1);
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

	cout << root.word_exist("xyz") << "\n";
	cout << root.word_exist("xy") << "\n";
	cout << root.prefix_exist("xy") << "\n";

	return 0;
}
