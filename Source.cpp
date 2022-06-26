#include <iostream>
#include "AVLTree.h"
#include "BSTree.h"
#include "SlayTree.h"

template<typename T>
void printArray(T* arr, int size) {
	std::cout << "[";
	if (size)
		std::cout << arr[0];
	for (int i = 1; i < size; i++) {
		std::cout << ", " << arr[i];
	}
	std::cout << "]\n";
}

void reHeapDown(int* arr, int size, int parent) {
	int leftChild = parent * 2 + 1;
	int rightchild = parent * 2 + 2;
	if (leftChild < size) {
		int larger;
		if (rightchild < size && arr[rightchild] > arr[leftChild]) {
			larger = rightchild;
		}
		else
			larger = leftChild;
		if (arr[larger] > arr[parent]) {
			std::swap(arr[larger], arr[parent]);
			reHeapDown(arr, size, larger);
		}
	}
}

void remove(int* arr, int size) {
	if (size) {
		int dataOut = arr[0];
		arr[0] = arr[size - 1];
		reHeapDown(arr, size, 0);
		arr[size - 1] = dataOut;
	}
}

void heapSort(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		remove(arr, size-i);
		printArray(arr, size);
	}
}

int main() {
	AVLTree T;
	T.insert(2);
	T.insert(4);
	T.insert(1);
	T.insert(10);
	T.insert(4);
	T.insert(3);
	T.insert(26);
	T.insert(14);
	T.insert(98);
	T.insert(145);
	T.insert(43);
	T.printTreeStructure();
	T.printInorder();
	T.printPostOrder();
	std::cout << T.size();

}