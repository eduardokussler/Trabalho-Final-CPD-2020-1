#pragma once
#include <vector>
#include <memory>

class Node
{
public:
	Node(char letter, int ID) : lst(), letter(letter), ID(ID) {}
	Node(char letter): lst(), letter(letter), ID(0) {}
	Node() : lst(), letter('\0'), ID(0) {}

	std::shared_ptr<Node> findNode(char c);

	std::vector<std::shared_ptr<Node>> &getLst();
	char getLetter();
	int getID();

	void setID(int ID);
private:
	std::vector<std::shared_ptr<Node>> lst;
	char letter;
	int ID;
};

