#pragma once
/*
* File Name: BinaryTree.hpp
* Author: John Deslippe
* Date: November 27th, 2022
* Purpose: Define the Binary Tree datastructure & declares various functions to be called on a binary tree
*/
#include "BreastCancer.hpp"
class BinaryTree {
	 struct Node {
		unsigned data; //numerical value stored in node, used for comparisons
		std::string nodeName; //contains a string used to determine what data needs to be compared against the nodes data
		//Pointers to both children nodes
		Node* leftChild;
		Node* rightChild;
		
		//1arg constructor, intiliazes children nodes to null
		Node(const int& val, const std::string& name) : leftChild(nullptr), rightChild(nullptr) {
			this->data = val;
			this->nodeName = name;
		}
	};

	 Node* rootNode; //root node of the entire tree object

	// Node* find_parentNode(Node* start, const unsigned& value);
public:
	//default constructor for BinaryTree objects
	BinaryTree() : rootNode(nullptr) {}

	//getter method for rootNode attribute
	Node* getRoot() { return rootNode; }

	/*
	* Name: buildPrunedTreee
	* Purpose: converts a exist binary tree object into a pruned binary decision tree based off of requirements specified in document
	* Acceepts: nothing
	* Returns: nothing
	*/
	void buildPrunedTree();

	/*
	* Name: Perform
	* Purpose: Determine status of the dataset based on the binary decision tree generated by build pruned tree
	*/
	void perform(BreastCancer& dataSet, Node* CurrentNode);
};



