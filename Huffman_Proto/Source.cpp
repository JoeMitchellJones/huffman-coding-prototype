#include <iostream>
#include <vector>
#include <algorithm>

struct node {

	char input_;
	int freq_;

	node *left, *right;
};

struct nodeHeap {
	node* extractMin() {
		std::vector<node*>::iterator minIt = std::min_element(nodeArr.begin(), nodeArr.end(), [](node* n1, node* n2) { return n1->freq_ < n2->freq_; });
		node* tempN = *minIt;
		nodeArr.erase(minIt);
		return tempN;
	}

	bool isDone() {
		return nodeArr.size() == 1;
	}

	std::vector<node*> nodeArr;
};

node* newNode(char input, int freq) {
	node* tempNode = new node();

	tempNode -> input_ = input;
	tempNode -> freq_ = freq;
	tempNode -> left = NULL;
	tempNode -> right = NULL;

	return tempNode;
}

void initVector(std::vector<node*> &v, std::vector<char> input, std::vector<int> freq) {
	for (int i = 0; i < input.size() - 1; ++i) {
		v.push_back(newNode(input.at(i), freq.at(i)));
	}
}

node* buildTree(std::vector<char> input, std::vector<int> freq) {

	node *left, *right, *top;
}

int main() {
}