#include "Heap.h"
#include <iostream>
#include <queue>

Heap::Heap():elements(0) {
	clear();
}

Heap::~Heap() {
	delete[] elements;
}

void Heap::clear() {
	capacity = 10;
	size = 0;
	delete[] elements;
	elements = new int[capacity];
}

void Heap::ensureCapacity(int capacity) {
	if (this->capacity <= capacity) {
		capacity = (3 / 2) * capacity;
		int* newElements = new int[capacity];
		memmove(newElements, this->elements, this->size * sizeof(int));
		delete[] elements;
		elements = newElements;
		this->capacity = capacity;
	}
}

void Heap::reheapUp(int child) {
	if (child) {
		int parent = (child - 1) / 2;
		//std::cout << "child " << child << "\n";
		//std::cout << "parent " << parent << "\n";
		if (elements[child] > elements[parent]) {
			std::swap(elements[child], elements[parent]);
			//std::cout << "swaped\n";
			this->reheapUp(parent);
			//printHeap();
		}
	}
}

void Heap::reheapDown(int parent) {
	int leftChild = parent * 2 + 1;
	int rightChild = parent * 2 + 2;
	if (leftChild < size) {
		int largerChild;
		if (rightChild < size &&
			elements[rightChild] > elements[leftChild]
			)
		{
			largerChild = rightChild;
		}
		else
			largerChild = leftChild;
		if (elements[largerChild] > elements[parent]) {
			std::swap(elements[largerChild], elements[parent]);
			reheapDown(largerChild);
		}
	}
}

void Heap::insert(int value) {
	this->ensureCapacity(size+1);
	size++;
	elements[size-1] = value;
	reheapUp(size-1);
}

void Heap::printHeap() {
	std::cout << size << " [";
	if (size) {
		std::cout << elements[0];
		for (int i = 1; i < size; i++) {
			std::cout << ", " << elements[i];
		}
	}
	std::cout << "]\n";
}

bool Heap::remove(int& dataOut) {
	if (size) {
		dataOut = elements[0];
		elements[0] = elements[--size];
		reheapDown(0);
		return true;
	}
	return false;
}

void Heap::buildHeap(int* arr, int size) {
	this->clear();
	for (int i = 0; i < size; i++) {
		insert(arr[i]);
	}
}

void Heap::printHeapStructure(const std::string& prefix, int node, bool isLeft) {
	if (node < size)
	{
		std::cout << prefix;

		std::cout << (isLeft ? char(195) : char(192)) << char(196) << char(196);

		// print the value of the node
		std::cout << elements[node] << std::endl;

		// enter the next tree level - left and right branch
		printHeapStructure(prefix + (isLeft ? char(179) : ' ') + "   ", node * 2 + 1, true);
		printHeapStructure(prefix + (isLeft ? char(179) : ' ') + "   ", node * 2 + 2, false);
	}
};

void Heap::printHeapStructure() {

	this->printHeapStructure("", 0, false);
	std::cout << std::endl;
}