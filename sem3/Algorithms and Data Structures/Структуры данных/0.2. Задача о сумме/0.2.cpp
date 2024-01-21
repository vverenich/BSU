#include<iostream>
#include<vector>
#include<string>

void add(long long  i, long long  x,long long  root, std::vector<long long> &A, std::vector<long long> &S) {
	A[i] += x;
	S[i / root] += x;
}

long long  findSum(long long  l, long long  r,long long  root,const std::vector<long long>& A, const std::vector<long long> &S) {
	long long  blockL = l / root;
	long long  blockR = r / root;


	if (blockL == blockR) {
		long long res{ 0 };
		for (long long  i{ l }; i < r; ++i) {
			res += A[i];
		}
		return res;
	}
	else {
		long long res{ 0 };
		for (long long  i = l; i <(blockL+1)*root; ++i) {
			res += A[i];
		}
		for (long long  i{ blockL + 1 }; i < blockR; ++i) {
			res += S[i];
		}
		for (long long  i{ blockR * root }; i < r; ++i) {
			res += A[i];
		}
		return res;
	}
}
int  main() {
	long long  N;
	std::cin >> N;
	std::vector<long long> A(N);


	long long  root = sqrt(N);
	long long  size;
	if (N % root == 0) {
		size = N / root;
	} else {
		size = N / root + 1;
	}
	std::vector<long long> S(size, 0);


	for (long long  i{ 0 }; i < N; ++i) {
		std::cin >> A[i];
		S[i / root] += A[i];
	}

	long long  q;
	std::cin >> q;

	std::string s;
	long long  a, b;
	for (long long  i{ 0 }; i < q; ++i) {
		std::cin >> s >> a >> b;
		if (s == "FindSum") {
			std::cout<<findSum(a, b,root,A, S)<<"\n";
		} else {
			add(a, b,root, A, S);
		}
	}
}