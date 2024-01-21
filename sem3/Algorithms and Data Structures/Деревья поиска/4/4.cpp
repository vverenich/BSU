#pragma comment(linker, "/STACK:47185920")

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

class Node {
public:
	int key;
	int high{ -1 };
	int numberOfChildren{ 0 };
	Node *left = nullptr;
	Node *right = nullptr;
};
bool predicate(Node *node1, Node *node2) {
	return node1->key > node2->key;
}

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
void getNodesOfTheSameLevel(Node *node, int height, std::vector<Node *> &v, int level) {
	if (node->left == nullptr && node->right == nullptr) {
		return;//can be unsafe
	}
	if (height == level) {
		if (node->right == nullptr && node->left != nullptr) {
			v.push_back(node);
		} else if (node->left != nullptr && node->right != nullptr) {
			if (node->left->numberOfChildren > node->right->numberOfChildren)
				v.push_back(node);
		}
	}
	if (height < level) {
		if (node->left != nullptr) {
			getNodesOfTheSameLevel(node->left, height, v, level - 1);
		}
		if (node->right != nullptr) {
			getNodesOfTheSameLevel(node->right, height, v, level - 1);
		}
	}

	
}
int findMin(Node *node) {
	if (node->left != nullptr) {
		return findMin(node->left);
	}
	return node->key;
}
Node *deleteKey(int key, Node *node) {
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

int setHeight(Node *node) {
	if (node->high == -1) {
		if (node->left == nullptr && node->right == nullptr) {
			node->high = 0;
		} else if (node->left == nullptr && node->right != nullptr) {
			node->high = setHeight(node->right) + 1;
			node->numberOfChildren = node->right->numberOfChildren + 1;
		} else if (node->left != nullptr && node->right == nullptr) {
			node->high = setHeight(node->left) + 1;
			node->numberOfChildren = node->left->numberOfChildren + 1;
		} else {
			node->high = (setHeight(node->left) > setHeight(node->right) ?
				setHeight(node->left) : setHeight(node->right)) + 1;
			node->numberOfChildren = node->right->numberOfChildren +
				node->left->numberOfChildren + 2;
		}
	}
	return node->high;
}

void freeMemory(Node *node) {
	if (node != nullptr) {
		freeMemory(node->left);
		freeMemory(node->right);
		delete node;
	}
}

int main() {
	std::ifstream fin("in.txt");
	std::ofstream fout("out.txt");

	if (!fin.is_open()) {
		std::cout << "File was not opened";
		return 0;
	}

	Node *root = nullptr;

	while (fin.peek() != EOF) {
		int a;
		fin >> a;
		root = addNode(a, root);
	}

	root->high = setHeight(root);

	std::vector<Node *> particularNodes;
	getNodesOfTheSameLevel(root, root->high / 2, particularNodes, root->high);


	std::sort(particularNodes.begin(), particularNodes.end(), predicate);

	int size = particularNodes.size();
	if (size % 2 == 1) {
		root = deleteKey(particularNodes[size / 2]->key, root);
	}
	leftPreOrderTraversal(root, fout);

	fin.close();
	fout.close();

	freeMemory(root);
}
