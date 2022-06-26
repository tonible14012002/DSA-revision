#include "BSTree.h"
#include <iostream>
#include <stack>
#include <queue>

void BSTree::clear(Node* root) {
	if (root) {
		clear(root->pLeft);
		clear(root->pRight);
		delete root;
	}
}

void BSTree::insert(int data) {
	if (root == nullptr) {
		root = new Node(data);
		return;
	}
	Node* parent = root;
	Node* child = root;
	Node* newNode = new Node(data);
	while (child){
		parent = child;
		if (data < child->data) {
			child = child->pLeft;
		}
		else
			child = child->pRight;
	}
	if (data < parent->data) {
		parent->pLeft = newNode;
	}
	else
		parent->pRight = newNode;
}

void BSTree::printTreeStructure(const std::string& prefix, Node* node, bool isRight) {
	if (node)
	{
		std::cout << prefix;

		std::cout << (isRight ? char(195) : char(192)) << char(196) << char(196);

		// print the value of the node
		std::cout << node->data << std::endl;

		// enter the next tree level - left and right branch
		printTreeStructure(prefix + (isRight ? char(179) : ' ') + "   ", node->pRight, true);
		printTreeStructure(prefix + (isRight ? char(179) : ' ') + "   ", node->pLeft, false);
	}
};

void BSTree::printTreeStructure() {
	this->printTreeStructure("", root, false);
}

bool BSTree::contain(int data) {
	if (root) {
		Node* cur = root;
		while (cur){
			if (data < cur->data)
				cur = cur->pLeft;
			else if (data > cur->data)
				cur = cur->pRight;
			else
				return true;
		}
		return false;
	}
	return false;
}

bool BSTree::remove(int data) {
	bool success = false;
	root = remove(root, data, success);
	return success;
}

BSTree::Node* BSTree::getInSucc(Node* p) {
	Node* inSucc = p->pLeft;
	if (inSucc){
		while (inSucc->pRight) {
			inSucc = inSucc->pRight;
		}
		return inSucc;
	}
	return NULL;
}

BSTree::Node* BSTree::remove(Node* p, int data, bool& success) {
	if (p == NULL) {
		success = false;
		return NULL;
	}
	if (data < p->data) {
		p->pLeft = remove(p->pLeft, data, success);
	}
	else if (data > p->data) {
		p->pRight = remove(p->pRight, data, success);
	}
	else {
		success = true;
		Node* toDelete = p;
		if (toDelete->pLeft == NULL) {
			p = p->pRight;
			delete toDelete;
		}
		else if (toDelete->pRight == NULL) {
			p = p->pLeft;
			delete toDelete;
		}
		else
		{
			Node* inSucc = getInSucc(toDelete);
			toDelete->data = inSucc->data;
			p->pLeft = remove(p->pLeft, inSucc->data, success);
		}
	}
	return p;
}

int BSTree::size() {
	return size(root);
}
int BSTree::size(Node* p) {
	if (p == NULL) return 0;
	return 1 + size(p->pLeft) + size(p->pRight);
}

void BSTree::printInorderR() {};

void BSTree::printPreOrderR(){}

void BSTree::printPostOrderR() {}

void BSTree::printPreOrder() {
	if (root) {
		std::stack<Node*> S;
		Node* cur = root;
		while (cur || !S.empty()) {
			if (cur){
				std::cout << cur->data << " ";
				S.push(cur);
				cur = cur->pLeft;
			}
			else {
				cur = S.top();
				S.pop();
				cur = cur->pRight;
			}
		}
		std::cout << std::endl;
	}
}

void BSTree::printInorder() {
	if (root) {
		std::stack<Node*> S;
		Node* cur = root;
		while (cur || !S.empty()) {
			if (cur) {
				S.push(cur);
				cur = cur->pLeft;
			}
			else {
				cur = S.top();
				std::cout << cur->data << " ";
				S.pop();
				cur = cur->pRight;
			}
		}
		std::cout << std::endl;
	}
}

void BSTree::printPostOrder() {
	if (root) {
		std::stack<Node*> S;
		int treeSize = size();
		int* stack = new int[treeSize];
		int stackP = -1;
		Node* cur = root;
		while (cur || !S.empty()) {
			if (cur) {
				stack[++stackP] = cur->data;
				S.push(cur);
				cur = cur->pRight;
			}
			else {
				cur = S.top();
				S.pop();
				cur = cur->pLeft;
			}
		}
		stackP = treeSize;
		while (stackP > 0) {
			int data = stack[--stackP];
			std::cout << data << " ";
		}
		std::cout << std::endl;
	}
}

void BSTree::printTreeBFS() {
	if (root) {
		Node* cur = root;
		std::queue<Node*> Q;
		Q.push(cur);
		while (!Q.empty()) {
			cur = Q.front();
			Q.pop();
			std::cout << cur->data << " ";
			if (cur->pLeft)
				Q.push(cur->pLeft);
			if (cur->pRight)
				Q.push(cur->pRight);
		}
		std::cout << std::endl;
	}

}

int BSTree::height() {
	return getHeight(root);
}

int BSTree::getHeight(Node* p) {
	if (p == NULL) {
		return -1;
	}
	int leftHeight = getHeight(p->pLeft);
	int rightHeight = getHeight(p->pRight);
	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

BSTree::Node* BSTree::leftRotation(Node* p) {
	Node* rightTree = p->pRight;
	p->pRight = rightTree->pLeft;
	rightTree->pLeft = p;
	return rightTree;
}

BSTree::Node* BSTree::rightRotation(Node* p) {
	Node* leftTree = p->pLeft;
	p->pLeft = leftTree->pRight;
	leftTree->pRight = p;
	return leftTree;
}

