#include<string>
#include<iostream>
#include<thread>
#include<mutex>

int SayClass::numberOfMessages = 20;
std::mutex mtx;

class SayClass {
private:
	std::string word;
	int numberOfRepeats;
	int delay;
public:
	static int numberOfMessages;
	SayClass(std::string str, int repeat, int del) {
		SetWord(str);
		SetNumberOfRepeats(repeat);
		SetDelay(del);
	}
	const std::string GetWord() {
		return word;
	}
	const int GetNumberOfRepeats() {
		return numberOfRepeats;
	}
	const int GetDelay() {
		return delay;
	}
	void SetWord(std::string w) {
		word = w;
	}
	void SetNumberOfRepeats(int num) {
		if (num < 0) {
			throw std::exception("Number of repeats can't be negative number.");
		}
		numberOfRepeats = num;
	}
	void SetDelay(int d) {
		if (d < 0) {
			throw std::exception("Delay value can't be negative number.");
		}
		delay = d;
	}
	void operator()() {
		for (int i = 0; i < GetNumberOfRepeats() && numberOfMessages != 0; ++i) {
			{
				std::lock_guard<std::mutex> guard(mtx);
				--numberOfMessages;
				std::cout << GetWord() << " ";
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(GetDelay()));
		}
	}
};


int main()
{
	SayClass SayPapa("papa", 8, 1000);
	SayClass SayMama("mama", 8, 1000);
	SayClass SaySon("son", 8, 1000);
	
	std::thread t1(SayMama);
	std::thread t2(SayPapa);
	std::thread t3(SaySon);
	
	t1.join();
	t2.join();
	t3.join();
}