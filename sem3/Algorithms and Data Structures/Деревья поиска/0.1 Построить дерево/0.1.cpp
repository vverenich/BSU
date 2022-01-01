#include<iostream>
#include<fstream>

class Node {
public:
	int key;
	Node *left = nullptr;
	Node *right = nullptr;
};

Node *addNode(int x, Node *node) {
	if (node == nullptr) {
		node = new Node;
		node->key = x;
		node->left = nullptr;
		node->right = nullptr;
	} else if (node->key > x) {
		node->left = addNode(x, node->left);
	} else if (node->key < x) {
		node->right = addNode(x, node->right);
	}
	return node;
};
void printTree(Node *node, std::ofstream& fout) {
	if (node != nullptr) {
		fout<<node->key<<"\n";
		printTree(node->left,fout);
		printTree(node->right,fout);
	}
}

void freeMemory(Node *node) {
	if (node != nullptr) {
		freeMemory(node->left);
		freeMemory(node->right);
		delete node;
	}
}

void prinToFile(std::ofstream &fout) {
	fout << 1;
}
int main() {
	std::ifstream fin("input.txt" );
	std::ofstream fout("output.txt");
	
	if (!fin.is_open()) {
		std::cout<<"File was not opened";
		return 0;
	}

	Node *root = nullptr;
	while (fin.peek() != EOF) {
		int a;
		fin >> a;
		root=addNode(a, root);
	}

	printTree(root,fout);
	fin.close();
	fout.close();

	freeMemory(root);

	prinToFile(fout);
	prinToFile(fout);
	
}