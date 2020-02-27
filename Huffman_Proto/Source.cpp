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
		for (int i = 0; i < input.size(); ++i) {
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
		//sortVector();
	}

	node* newNode(char input, int freq) {
		node* tempNode = new node();

		tempNode -> input_ = input;
		tempNode -> freq_ = freq;
		tempNode -> left = NULL;
		tempNode -> right = NULL;

		return tempNode;
	}

	std::vector<node*> nodeArr;
};

node* buildTree(std::vector<char> input, std::vector<int> freq) {
	nodeHeap nh(input, freq);

	node *left, *right, *top;

	while (!nh.isDone()) {
		left = nh.extractMin();
		right = nh.extractMin();
		top = nh.newNode('^', left->freq_ + right->freq_);

		top->left = left;
		top->right = right;

		nh.insertNode(top);
	}
	return nh.extractMin();
}

void displayCodes(node* root, std::vector<int> code, int top) {
	if (root->left) {
		code.push_back(0);
		displayCodes(root->left, code, top + 1);
	}
	if (root->right) {
		code.pop_back();
		code.push_back(1);
		displayCodes(root->right, code, top + 1);
	}
	if (!(root->right) && !(root->left)) {
		std::cout << root->input_ << ": ";
		std::for_each(code.begin(), code.end(), [](int n) { std::cout << n; });
		std::cout << std::endl;
		code.clear();
	}
}

int main() {

	std::vector<char> input = { 'a', 'b', 'c', 'd', 'e', 'f' };
	std::vector<int> freq = { 5, 9, 12, 13, 16, 45 };

	node* root = buildTree(input, freq);
	std::vector<int> code;
	int top = 0;

	displayCodes(root, code, top);

	system("pause");
	return 0;
}