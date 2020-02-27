#include <iostream>
#include <vector>
#include <algorithm>

struct node {

	char input_;
	int freq_;

	node *left, *right;
};

struct nodeHeap {

	nodeHeap(std::vector<char> input, std::vector<int> freq) {
		for (int i = 0; i < input.size() - 1; ++i) {
			nodeArr.push_back(newNode(input.at(i), freq.at(i)));
		}
	}

	node* extractMin() {
		std::vector<node*>::iterator minIt = std::min_element(nodeArr.begin(), nodeArr.end(), [](node* n1, node* n2) { return n1->freq_ < n2->freq_; });
		node* tempN = *minIt;
		nodeArr.erase(minIt);
		return tempN;
	}

	bool isDone() {
		return nodeArr.size() == 1;
	}

	void sortVector() {
		std::sort(nodeArr.begin(), nodeArr.end(), [](node* n1, node* n2) { return n1->freq_ < n2->freq_; });
	}

	void insertNode(node* n) {
		nodeArr.push_back(n);
		sortVector();
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

node* buildTree(std::vector<char> input, std::vector<int> freq) {
	nodeHeap nh(input, freq);

	node *left, *right, *top;

	while (!nh.isDone) {
		left = nh.extractMin();
		right = nh.extractMin();
		top = newNode('^', left->freq_ + right->freq_);

		top->left = left;
		top->right = right;

		nh.insertNode(top);
	}
	return nh.extractMin();
}

int main() {
}