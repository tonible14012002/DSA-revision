#pragma once
#include <string>

template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

enum class BalanceFactor {
	LH = -1, EH, RH
};

class BSTree
{
protected:
	class Node;
	Node* root;
public:
	BSTree() :root(0) {};
	~BSTree() {
		clear(root);
	};
protected:
	 class Node {
	public:
		int data;
		Node* pLeft;
		Node* pRight;
		Node* pParent; //Used only in splay tree
		BalanceFactor balance;
	public:
		Node(int data) :
			data(data),
			pLeft(NULL), pRight(NULL), pParent(NULL),
			balance(BalanceFactor::EH) {};
	};
public:
	virtual void insert(int data);
	virtual bool contain(int data);
	virtual void printTreeStructure();
	virtual bool remove(int data);
	virtual void printTreeBFS();
	virtual void printInorder();
	virtual void printInorderR();
	virtual void printPreOrder();
	virtual void printPreOrderR();
	virtual void printPostOrder();
	virtual void printPostOrderR();
	virtual int height();
	int size();
protected:
	int size(Node*);
	void clear(Node*);
	virtual void printTreeStructure(const std::string& prefix, Node* node, bool isLeft);
	virtual Node* remove(Node* p, int data, bool& success);
	virtual Node* getInSucc(Node*);
	virtual int getHeight(Node* p);
	virtual Node* rightRotation(Node* p);
	virtual Node* leftRotation(Node* p);
};

