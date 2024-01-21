#include "RSA.h"

#include <cmath>

#include <QDebug>

// Функция для проверки, является ли число простым
bool RSA::isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Функция для поиска наибольшего общего делителя (НОД)
int RSA::gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Функция для генерации случайного простого числа
int RSA::generatePrime() {
    int prime;
    do {
        prime = rand() % 100 + 1; // Генерация случайного числа от 1 до 100
    } while (!isPrime(prime));
    return prime;
}

// Функция для генерации ключей (открытый и закрытый)
void RSA::generateKeys(int& publicKey, double& privateKey, int& modulus) {
    int p, q;
    // Генерация двух случайных простых чисел
    p = generatePrime();
    q = generatePrime();

    modulus = p * q; // Вычисление модуля

    int phi = (p - 1) * (q - 1); // Вычисление функции Эйлера

    //public key
    //e stands for encrypt
    int track;
    publicKey = 7;
    //for checking that 1 < e < phi(n) and gcd(e, phi(n)) = 1; i.e., e and phi(n) are coprime.
    while(publicKey < phi) {
        track = gcd(publicKey, phi);
        if(track==1)
            break;
        else
            publicKey++;
    }

    // private key
    double d1= 1.0 / publicKey;
    privateKey = fmod(d1, phi);

}

// Функция для шифрования сообщения с использованием открытого ключа
double RSA::encrypt(int message, int publicKey, int modulus) {
    double encryptedMessage = std::pow(message, publicKey);
    return encryptedMessage;
}

// Функция для расшифрования сообщения с использованием закрытого ключа
double RSA::decrypt(double encryptedMessage, double privateKey, int modulus) {
    double decryptedMessage = std::pow(encryptedMessage, privateKey);
    decryptedMessage = fmod(decryptedMessage, modulus);
    return decryptedMessage;
}
