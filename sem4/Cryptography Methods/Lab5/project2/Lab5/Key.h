#ifndef _KEY_H
#define _KEY_H

#include <utility>=

using publicKey_t = std::pair<long long, long long>;

class Key {
private:
	publicKey_t publicKey;
	long long privateKey;
public:
	Key(publicKey_t publicKey, long long privateKey);

	publicKey_t getPublicKey() const;

	long long getPrivateKey() const;
};

#endif

