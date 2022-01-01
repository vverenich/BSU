#include<iostream> 
#include<vector>
#include<fstream>
#include <stdio.h> 

struct element {
	int64_t left;
	int64_t right;
	int64_t node;
};


bool isBST(const std::vector<element> &parents) {
	for (size_t i{ 1 }; i < parents.size(); ++i) {
		if (parents[i].left > parents[i].node || parents[i].node >= parents[i].right) {
			return false;
		}
	}
	return true;
}

int main() {
	//std::ifstream fin("bst.in.txt");
	std::ofstream fout("bst.out");

	FILE *fp;

	fp = fopen("bst.in", "r");

	int n;
	//fin >> n;
	fscanf(fp, "%d", &n);
	//std::vector<int64_t> nodes(n);
	std::vector <element> parents(n);

	int m;
	//fin >> m;
	fscanf(fp, "%d", &m);
	//nodes[0] = m;
	parents[0].node = m;
	parents[0].left = INT64_MIN;
	parents[0].right = INT64_MAX;

	int p;
	char c;
	for (size_t i{ 1 }; i < n; ++i) {
		//fin >> m >> p >> c;
		fscanf(fp, "%d %d %c", &m, &p, &c);
		//nodes[i] = m;
		parents[i].node = m;
		if (c == 'R') {
			parents[i].left = parents[p - 1].node; // nodes[p - 1];
			parents[i].right = parents[p - 1].right;
		} else {
			parents[i].right = parents[p - 1].node; //nodes[p - 1];
			parents[i].left = parents[p - 1].left;
		}
	}

	if (isBST(parents)) {
		fout << "YES";
	} else {
		fout << "NO";
	}

	//fin.close();
	fout.close();

	return 0;
}