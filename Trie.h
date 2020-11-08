#pragma once
#include "Node.h"
#include <string>
#include <stack>

class Trie
{
public:
	Trie() : root(std::make_shared<Node>(Node())) {}

	void insert(const std::string& word, int ID);
	std::vector<int> substringSearch(const std::string &str);
	bool empty();
private:
	std::vector<int> getSubTreeIDS(std::shared_ptr<Node> root);
	void sort(std::vector<std::shared_ptr<Node>> &lst);

	std::shared_ptr<Node> root;
};

