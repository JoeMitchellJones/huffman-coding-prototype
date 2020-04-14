#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>

struct node {

	char input_;
	int freq_;

	node *left, *right;
};

struct nodeHeap {

	nodeHeap(std::map<char,int> &freq) {
		std::for_each(freq.begin(), freq.end(), [&](std::pair<char, int> p) { nodeArr.push_back(newNode(p.first, p.second)); });
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

node* buildTree(std::map<char,int> &freq) {
	nodeHeap nh(freq);

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

void displayCodes(node* root, std::vector<int> code, int top, std::map<char, std::string> &m) {
	if (root->left) {
		code.push_back(0);
		displayCodes(root->left, code, top + 1, m);
	}
	if (root->right) {
		code.pop_back();
		code.push_back(1);
		displayCodes(root->right, code, top + 1, m);
	}
	if (!(root->right) && !(root->left)) {
		std::string s = "";
		bool done = false;
		int count = 0;

		//std::cout << root->input_ << ": ";
		//std::for_each(code.rbegin(), code.rend(), [&](int n) { if (n == 0 && count+1 < code.size() && !done) { ++count; } else { done = true; }});
		//std::cout << count << " size: " << code.size();
		//code.erase(code.end() - count, code.end());

		std::for_each(code.begin(), code.end(), [&s](int n) { s += std::to_string(n); });
		//std::cout << std::endl;
		m.insert({ root->input_, s });
		code.clear();
	}
}

std::string decodeString(std::string input, node* root) {
	node* tempNode = root;
	std::string decodedString = "";

	for (int i = 0; i < input.size(); ++i) {
		if (input[i] == '0') {
			tempNode = tempNode->left;
		}
		else {
			tempNode = tempNode->right;
		}
		if (tempNode->left == NULL && tempNode->right == NULL) {
			decodedString += tempNode->input_;
			tempNode = root;
		}
	}
	return decodedString;
}

static std::vector<char> ReadAllBytes(std::string& filename) {
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();
	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
}

static std::map<char, int> GenerateFreq(std::vector<char> &v) {
	std::ofstream fdict("../../li.txt.dict");
	std::map<char, int> freq;

	std::for_each(v.begin(), v.end(), [&freq](char c) { freq[c]++; });
	std::for_each(freq.begin(), freq.end(), [&fdict](std::pair<char, int> p) { fdict << p.first << '\n' << p.second << '\n'; });
	return freq;
}

int main() {
	std::vector<node*> delV;

	std::string filePath = "../../loremipsum.txt";
	std::vector<char> input = ReadAllBytes(filePath);

	std::map<char, int> freq = GenerateFreq(input);
	//std::for_each(freq.begin(), freq.end(), [](std::pair<char, int> p) {std::cout << p.first << " " << p.second << std::endl; });

	//std::vector<char> input = { 'a', 'b', 'c', 'd', 'e', 'f' };
	//std::vector<int> freq = { 5, 9, 12, 13, 16, 45 };

	node* root = buildTree(freq);
	std::vector<int> code;
	int top = 0;

	std::map<char, std::string> m;
	displayCodes(root, code, top, m);

	//std::string encodedString = "";
	//std::cout << "BEGIN" << std::endl;
	//std::for_each(m.begin(), m.end(), [&encodedString](std::pair<char, std::string> p) { std::cout << p.first << ": " << p.second << std::endl; encodedString += p.second; encodedString += " "; });
	//std::cout << std::endl << "Encoded string: " << encodedString << std::endl;
	//std::string ds = decodeString(encodedString, root);
	//std::cout << "Decoded string: " << ds << std::endl;

	//std::for_each(vc.begin(), vc.end(), [](char c) {std::cout << c << " "; });
	//std::cout << std::endl;
	
	std::ofstream output;
	output.open("../../li.txt");
	std::for_each(input.begin(), input.end(), [&](char c) { output << m[c]; std::cout << c << ": " << m[c] << std::endl; });
	output.close();

	std::for_each(delV.begin(), delV.end(), [](node* n){ delete n; });

	system("pause");
	return 0;
}