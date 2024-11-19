#include<iostream>
#include<algorithm>
#include<vector>

template <class T>
class Repository {
private:
	T m_value;
public:
	Repository(T value) {
		m_value = value;
	}
	~Repository() {

	}
	void print() {
		std::cout << m_value << "\n";
	}
};
template<>
Repository<char *>::Repository(char *value) {
	int length
}
template <typename T>
class Repository<T *> {
private:
	T *m_value;
public:
	Repository(T *value) {
		m_value = new T(*value);
	}
	~Repository() {
		delete m_value;
	}
};

int main() {
	Repository<int> myint(6);
	myint.print();

	char v = '7';
	Repository<char *> myint{ &v };

}