#include<iostream>
#include<vector>
#include<fstream>
#include<utility>
#include<stack>


int main() {
	std::ifstream fin("minpath.in.txt");
	std::ofstream fout("minpath.out.txt");
	const int I = 1000000000;
	int N, M;
	std::ios_base::sync_with_stdio(false);
	fin >> N >> M;
	int A, B;
	fin >> A >> B;

	std::vector<std::vector<std::pair<int, int>>> arcs(N + 1);

	int n1, n2, d;
	for (int i = 0; i < M; ++i) {
		fin >> n1 >> n2 >> d;
		arcs[n1].push_back(std::make_pair(n2, d));
	}

	std::vector<std::pair<bool, int>> checkedTops;
	for (int i = 0; i < N + 1; ++i) {
		checkedTops.push_back(std::make_pair(false, -1));
	}
	std::vector<int> distances;
	for (int i = 0; i < N + 1; ++i) {
		distances.push_back(I);
	}

	distances[A] = 0;
	checkedTops[A].first = true;

	int minTop = A;
	int minDistance = 0;

	while (minDistance < I && checkedTops[B].first == false) {
		int i = minTop;
		for (int j = 0; j < arcs[i].size(); ++j) {
			if (minDistance + arcs[i][j].second < distances[arcs[i][j].first]) {
				distances[arcs[i][j].first] = minDistance + arcs[i][j].second;
				checkedTops[arcs[i][j].first].second = i;
				std::cout << "fjjf ";
			}
		}
		checkedTops[minTop].first = true;
		minDistance = I;
		for (int j = 0; j < N + 1; ++j) {
			if (checkedTops[j].first == false && distances[j] < minDistance) {
				minTop = j;
				minDistance = distances[j];
			}
		}
	}

	if (distances[B] == I) {
		fout << "0";
	}
	else {
		fout << distances[B] << "\n";
		std::stack<int> tops;
		int i = B;
		tops.push(B);
		while (i != A) {
			tops.push(checkedTops[i].second);
			i = checkedTops[i].second;
		}

		fout << tops.top();
		tops.pop();
		while (!tops.empty()) {
			fout << " " << tops.top();
			tops.pop();
		}
	}
	return 0;
}