#include "Node.h"

std::shared_ptr<Node> Node::findNode(char c)
{
    if (lst.empty()) {
        return nullptr;
    }

    int l = 0, r = lst.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (lst[m]->letter == c)
            return lst[m];
        if (lst[m]->letter < c)
            l = m + 1;
        else
            r = m - 1;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Node>> &Node::getLst()
{
	return lst;
}

char Node::getLetter()
{
	return letter;
}

int Node::getID()
{
	return ID;
}

void Node::setID(int ID)
{
    this->ID = ID;
}
