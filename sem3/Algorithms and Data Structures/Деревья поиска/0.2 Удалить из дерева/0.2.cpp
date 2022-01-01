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
void leftPreOrderTraversal(Node *node, std::ofstream &fout) {
	if (node != nullptr) {
		fout << node->key << "\n";
		leftPreOrderTraversal(node->left, fout);
		leftPreOrderTraversal(node->right, fout);
	}
}
int findMin(Node *node) {
	if (node->left != nullptr) {
		return findMin(node->left);
	}
	return node->key;
}
Node*  deleteKey(int key, Node *node) {
	if (node != nullptr) {
		if (node->key < key) {
			node->right = deleteKey(key, node->right);
		} else if (node->key > key) {
			node->left = deleteKey(key, node->left);
		} else {
			if (node->left == nullptr && node->right == nullptr) {
				delete node;
				node = nullptr;
			} else if (node->left == nullptr && node->right != nullptr) {
				Node *t = node->right;
				delete node;
				node = t;
			} else if (node->left != nullptr && node->right == nullptr) {
				Node *t = node->left;
				delete node;
				node = t;
			} else {
				int min = findMin(node->right);
				node->right = deleteKey(min, node->right);
				node->key = min;
			}
		}
	}
	return node;
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
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	if (!fin.is_open()) {
		std::cout << "File was not opened";
		return 0;
	}

	Node *root = nullptr;
	int keyToDelete;
	fin >> keyToDelete;

	while (fin.peek() != EOF) {
		int a;
		fin >> a;
		root = addNode(a, root);
	}

	root = deleteKey(keyToDelete, root);


	leftPreOrderTraversal(root, fout);
	
	fin.close();
	fout.close();

	freeMemory(root);
}