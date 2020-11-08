#include "Trie.h"

void Trie::insert(const std::string& word, int ID)
{
	std::shared_ptr<Node> n(root);
	for (auto c : word) {
		std::shared_ptr<Node> temp = n->findNode(c);
		if (temp) {
			n = temp;
		} else {
			temp = std::make_shared<Node>(Node(c));
			n->getLst().push_back(temp);
			sort(n->getLst());
			n = temp;
		}
	}
	n->setID(ID);
}

std::vector<int> Trie::substringSearch(const std::string &str)
{
	std::shared_ptr<Node> n = root;
	for (auto c : str) {
		n = n->findNode(c);
		if (!n) {
			return std::vector<int>();
		}
	}
	return getSubTreeIDS(n);
}

bool Trie::empty()
{
	return root->getLst().empty();
}

std::vector<int> Trie::getSubTreeIDS(std::shared_ptr<Node> root)
{
	std::stack<std::shared_ptr<Node>> stack;
	std::vector<int> lstIDS;
	stack.push(root);

	while(!stack.empty()) {
		std::shared_ptr<Node> n = stack.top();
		stack.pop();
		if (n->getID()) {
			lstIDS.push_back(n->getID());
		}
		for (std::shared_ptr<Node> &child : n->getLst()) {
			stack.push(child);
		}
	}
	return lstIDS;
}

void Trie::sort(std::vector<std::shared_ptr<Node>>& lst)
{
	for (int last = lst.size() - 1, i = last - 1; i >= 0; i--) {
		if (lst[last]->getLetter() < lst[i]->getLetter()) {
			std::shared_ptr<Node> tmp = lst[last];
			lst[last] = lst[i];
			lst[i] = tmp;
			--last;
		}else {
			break;
		}
	}
}
