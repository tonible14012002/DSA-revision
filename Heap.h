#pragma once
#include <string>


class Heap
{
public:
	Heap();
	~Heap();
	void insert(int value);
	bool remove(int&);
	void printHeap();
	int getSize() { return this->size; }
	bool isEmpty() { return size == 0; }
	void buildHeap(int* arr, int size);
	void printHeapStructure();

private:
	void reheapUp(int child);
	void itReheapUp(int child);
	void itReheapDown(int child);
	void reheapDown(int child);
	void ensureCapacity(int);
	void clear();
	void printHeapStructure(const std::string& prefix, int node, bool isLeft);


private:
	int capacity;
	int size;
	int* elements;
};

