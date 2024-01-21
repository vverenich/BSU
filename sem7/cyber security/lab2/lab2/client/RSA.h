#ifndef RSA_H
#define RSA_H

#include <string>

namespace RSA {

    bool isPrime(int n);
    int gcd(int a, int b);
    int generatePrime();
    void generateKeys(int& publicKey, double& privateKey, int& modulus);
    double encrypt(int message, int publicKey, int modulus);
    double decrypt(double encryptedMessage, double privateKey, int modulus);

    std::string decrypt(const std::string& str, double privateKey, int modulus);
    std::string encrypt(const std::string& str, double publicKey, int modulus);

}

#endif // RSA_H
