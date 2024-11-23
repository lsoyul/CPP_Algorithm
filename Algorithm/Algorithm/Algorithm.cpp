#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "BinarySearchTree.h"

using namespace std;

// Binary Search Tree

int main()
{
	BinarySearchTree bst;
	bst.Insert(20);
	bst.Insert(10);
	bst.Insert(30);
	bst.Insert(25);
	bst.Insert(26);
	bst.Insert(40);
	bst.Insert(50);

	bst.Print();
}