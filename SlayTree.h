#pragma once
#include "BSTree.h"

class SlayTree : public BSTree
{
public:
	SlayTree() {};
	~SlayTree() {};

	void insert(int data) {
		if (root == NULL) {
			root =  new Node(data);
			return;
		}
		Node* parent = root;
		Node* child = root;
		Node* newNode = new Node(data);
		while (child) {
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
		newNode->pParent = parent;

		splay(newNode);
	}
	bool remove(int data) {
		return 1;
	}
protected:

	void splay(Node* p) {
		while (p->pParent) {
			if (p->pParent == root) //Node is root's child/
				if (p == p->pParent->pLeft)
					root = rightRotation(p->pParent);
				else
					root = leftRotation(p->pParent);
			else {
				//2 rotations;
				Node* parent = p->pParent;
				Node* grandParent = parent->pParent;
				if (parent->pLeft == p &&
					grandParent->pLeft == parent)
				{
					rightRotation(grandParent);
					rightRotation(parent);
				}
				else if (parent->pRight == p &&
					grandParent->pRight == parent)
				{	
					leftRotation(grandParent);
					leftRotation(parent);
				}
				else if (parent->pRight == p &&
					grandParent->pLeft == parent)
				{
					leftRotation(parent);
					rightRotation(grandParent);
				}
				else {
					rightRotation(parent);
					leftRotation(grandParent);
				}
			}
		}
	}
	Node* search(Node* p, int data) {
		if (p == NULL) return NULL;
		if (data < p->data) {
			return search(p->pLeft, data);
		}
		else if (data > p->data) {
			return search(p->pRight, data);
		}
		else {
			//found.
			splay(p);
			return root;
		}
	}
	Node* leftRotation(Node* p) {
		Node* rightTree = p->pRight;
		p->pRight = rightTree->pLeft;

		if (rightTree->pLeft) {
			rightTree->pLeft->pParent = p;
		}
		rightTree->pParent = p->pParent;

		if (p->pParent == NULL) {
			root = rightTree;
		}
		else if (p->pParent->pLeft == p) {
			p->pParent->pLeft = rightTree;
		}
		else
			p->pParent->pRight = rightTree;

		rightTree->pLeft = p;
		p->pParent = rightTree;

		return rightTree;
	}
	Node* rightRotation(Node* p) {
		Node* leftTree = p->pLeft;
		p->pLeft = leftTree->pRight;

		if (leftTree->pRight) {
			leftTree->pRight->pParent = p;
		}
		leftTree->pParent = p->pParent;

		if (p->pParent == NULL) {
			root = leftTree;
		}
		else if (p->pParent->pLeft == p) {
			p->pParent->pLeft = leftTree;
		}
		else
			p->pParent->pRight = leftTree;

		leftTree->pRight = p;
		p->pParent = leftTree;

		return leftTree;
	}
};

