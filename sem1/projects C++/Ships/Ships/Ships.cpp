#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<queue>

int main() {
	std::ifstream fin("SHIPS.IN.txt");
	std::ofstream fout("SHIPS.OUT.txt");
	if (fin.is_open() == 0) {
		std::cout << "Error opening file.";
	}
	else if (fin.peek() == EOF) {
		return 0;
	}
	else {
		int N;
		fin >> N;
		std::vector<std::pair<bool, std::string>> port;
		for (int i = 0; i < N; ++i) {
			port.push_back(std::make_pair(true, "empty"));
		}
		std::queue<std::string> reid;

		int number;
		while (fin.peek() == EOF) {
			fin >> number;
			if (number == 1) {
				std::string shipName;
				getline(fin, shipName);
				
				while(i<N){
					if (port[i].first == true) {
						port[i].second = shipName;
						port[i].first = false;
						break;
					}
					++i;
				}+
			}
		}

	}
}

