/*
* File Name: BinaryTree.cpp
* Author: John Deslippe
* Date: November 27th, 2022
* Purpose: provideds the definitions for the functiosn declared in BinaryTree.hpp
*/

#include "BinaryTree.hpp"

void BinaryTree::buildPrunedTree() {
	Node* newNode = new Node(2, "Uniform Cell Size");
	rootNode = newNode;
	rootNode->leftChild = new Node(3, "Bare Nuclei");
	rootNode->rightChild = new Node(2, "Uniform Cell Shape");

	//building left side of decision tree
	Node* currentNode = rootNode->leftChild;
	currentNode->leftChild = new Node(2, "Benign");
	currentNode->rightChild = new Node(3, "Clump Thickness");

	currentNode = currentNode->rightChild;
	currentNode->leftChild = new Node(2, "Benign");
	currentNode->rightChild = new Node(2, "Bland Chromatin");

	currentNode = currentNode->rightChild;
	currentNode->rightChild = new Node(4, "Malignant");
	currentNode->leftChild = new Node(3, "Marginal Adhesion");

	currentNode = currentNode->leftChild;
	currentNode->leftChild = new Node(4, "Malignant");
	currentNode->rightChild = new Node(2, "Benign");

	//building right side of decision tree
	currentNode = rootNode->rightChild;
	currentNode->leftChild = new Node(5, "Clump Thickness");
	currentNode->rightChild = new Node(4, "Uniform Cell Size");

	currentNode = currentNode->leftChild;
	currentNode->leftChild = new Node(2, "Benign");
	currentNode->rightChild = new Node(4, "Malignant");

	currentNode = rootNode->rightChild->rightChild;
	currentNode->leftChild = new Node(2, "Bare Nuclei");
	currentNode->rightChild = new Node(4, "Malignant");

	currentNode = currentNode->leftChild;
	Node* tempResume = currentNode; //variable to store a restart point in order to traverse the other branch at thise node

	currentNode->leftChild = new Node(3, "Marginal Adhesion");
	currentNode->rightChild = new Node(6, "Clump Thickness");

	currentNode = currentNode->leftChild;
	currentNode->leftChild = new Node(2, "Benign");
	currentNode->rightChild = new Node(4, "Malignant");

	//return to resume point
	currentNode = tempResume; //currently pointing to bare nuclei 2
	currentNode = currentNode->rightChild; //now at clump thickness 6

	currentNode->leftChild = new Node(3, "Uniform Cell Size");
	currentNode->rightChild = new Node(4, "Malignant");

	currentNode = currentNode->leftChild;
	currentNode->leftChild = new Node(4, "Malignant");
	currentNode->rightChild = new Node(5, "Marginal Adhesion");

	currentNode = currentNode->rightChild;
	currentNode->leftChild = new Node(2, "Benign");
	currentNode->rightChild = new Node(4, "Malignant");
}

void BinaryTree::perform(BreastCancer& dataSet, Node* currentNode) {
	//anchor, if the name of the node is one of the results we're looking for, then we have reached the end of the tree
	if(currentNode->nodeName == "Malignant" || currentNode->nodeName == "Benign"){
		dataSet.cancerClass = currentNode->data;
	}

	//use the names stored in the node to determine what value in the data set to compare it to and recursively call this function until we reach the anchor
	if (currentNode->nodeName == "Uniform Cell Size") {
		if (dataSet.uniformCellSize <= currentNode->data)
			BinaryTree::perform(dataSet, currentNode->leftChild);
		else
			BinaryTree::perform(dataSet, currentNode->rightChild);
	}
	else if (currentNode->nodeName == "Bare Nuclei") {
		if (dataSet.bareNuclei <= currentNode->data)
			BinaryTree::perform(dataSet, currentNode->leftChild);
		else
			BinaryTree::perform(dataSet, currentNode->rightChild);
	}
	else if (currentNode->nodeName == "Uniform Cell Shape") {
		if (dataSet.uniformCellShape <= currentNode->data)
			BinaryTree::perform(dataSet, currentNode->leftChild);
		else
			BinaryTree::perform(dataSet, currentNode->rightChild);
	}
	else if (currentNode->nodeName == "Clump Thickness") {
		if (dataSet.clumpThickness <= currentNode->data)
			BinaryTree::perform(dataSet, currentNode->leftChild);
		else
			BinaryTree::perform(dataSet, currentNode->rightChild);
	}
	else if (currentNode->nodeName == "Bland Chromatin") {
		if (dataSet.blandChromatin <= currentNode->data)
			BinaryTree::perform(dataSet, currentNode->leftChild);
		else
			BinaryTree::perform(dataSet, currentNode->rightChild);
	}
	else if (currentNode->nodeName == "Marginal Adhesion") {
		if (dataSet.marginalAdhesion <= currentNode->data)
			BinaryTree::perform(dataSet, currentNode->leftChild);
		else
			BinaryTree::perform(dataSet, currentNode->rightChild);
	}
	
}