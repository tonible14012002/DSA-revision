#pragma once
#include "BSTree.h"


class AVLTree : public BSTree
{
public:
	void insert(int data) {
		bool taller = false;
		root = insertR(root, data, taller);
	}

	void printTreeStructure() {
		printTreeStructure("", root, false);
	}

protected:
	Node* insertR(Node* p, int data, bool& taller) {
		if (p == NULL) {
			p = new Node(data);
			taller = true;
			return p;
		}

		if (data < p->data) {
			p->pLeft = insertR(p->pLeft, data, taller);
			if (taller) {
				if (p->balance == BalanceFactor::RH) {
					taller = false;
					p->balance = BalanceFactor::EH;
				}
				else if (p->balance == BalanceFactor::EH) {
					p->balance = BalanceFactor::LH;
				}
				else {
					p = leftBalance(p);
					taller = false;
				}
			}
		}
		else {
			p->pRight = insertR(p->pRight, data, taller);
			if (taller) {
				if (p->balance == BalanceFactor::RH) {
					p = rightBalance(p);
					taller = false;
				}
				else if (p->balance == BalanceFactor::EH) {
					p->balance = BalanceFactor::RH;
				}
				else {
					taller = false;
					p->balance = BalanceFactor::EH;
				}
			}
		}
		return p;
	}
	
	Node* leftBalance(Node* p) {
		Node* leftTree = p->pLeft;
		if (leftTree->balance == BalanceFactor::LH) {
			leftTree->balance = BalanceFactor::EH;
			p->balance = BalanceFactor::EH;
			return rightRotation(p);
		}
		else {
			Node* rightTree = leftTree->pRight;
			if (rightTree->balance == BalanceFactor::LH) {
				leftTree->balance = BalanceFactor::EH;
				p->balance = BalanceFactor::RH;
			}
			else if (rightTree->balance == BalanceFactor::EH) {
				leftTree->balance = BalanceFactor::EH;
				p->balance = BalanceFactor::EH;
			}
			else {
				p->balance = BalanceFactor::EH;
				leftTree->balance = BalanceFactor::LH;
			}
			rightTree->balance = BalanceFactor::EH;
			p->pLeft = leftRotation(p->pLeft);
			return rightRotation(p);
		}
	}

	Node* rightBalance(Node* p) {
		Node* rightTree = p->pRight;
		if (rightTree->balance == BalanceFactor::RH) {
			rightTree->balance = BalanceFactor::EH;
			p->balance = BalanceFactor::EH;
			return leftRotation(p);
		}
		else {
			Node* leftTree = rightTree->pLeft;
			if (leftTree->balance == BalanceFactor::RH) {
				rightTree->balance = BalanceFactor::EH;
				p->balance = BalanceFactor::LH;
			}
			else if (leftTree->balance == BalanceFactor::EH) {
				rightTree->balance = BalanceFactor::EH;
				p->balance = BalanceFactor::EH;
			}
			else {
				p->balance = BalanceFactor::EH;
				rightTree->balance = BalanceFactor::RH;
			}
			leftTree->balance = BalanceFactor::EH;
			p->pRight = rightRotation(p->pRight);
			return leftRotation(p);
		}
	}
	
	void printTreeStructure(const std::string& prefix, Node* node, bool isRight) {
		if (node)
		{
			std::cout << prefix;

			std::cout << (isRight ? char(195) : char(192)) << char(196) << char(196);

			// print the value of the node
			std::cout << node->data << "." << as_integer(node->balance) << std::endl;

			// enter the next tree level - left and right branch
			printTreeStructure(prefix + (isRight ? char(179) : ' ') + "   ", node->pRight, true);
			printTreeStructure(prefix + (isRight ? char(179) : ' ') + "   ", node->pLeft, false);
		}
	};

};