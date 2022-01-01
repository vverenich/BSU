#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>


int main() {
	std::ofstream fout("output.txt");
	std::ifstream fin("input.txt");

	

	int n,k;
	fin >> n>>k;
	std::vector<long long>v(k);
	
	v[0] = 1;
	if (v.size() >= 2) {
		v[1] = 2;
	}
	for (int i{ 2 }; i < v.size(); ++i) {
		v[i] = (v[i - 1] + v[i - 2])% 1000000009;
	}


	long long casesK = v[k - 1]*v[k-1]+1;


	std::vector<long long> vector(n);
	vector[0] = 1;

	for (int i{ 1 }; i < n; ++i) {
		vector[i] = vector[i - 1] *( casesK% 1000000009) % 1000000009;
	}

	fout << vector[n - 1];
	
}