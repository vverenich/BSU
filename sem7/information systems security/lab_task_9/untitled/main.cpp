#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    std::ifstream file("C:/Users/VVerc/Downloads/hog/antiDHog.com", std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    unsigned char byte;
    size_t count{0};
    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        ++count;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << ' ';
    }

    std::cout << "\n\ncount: " << std::dec << count << "\n\n";

    file.close();
    return 0;
}
