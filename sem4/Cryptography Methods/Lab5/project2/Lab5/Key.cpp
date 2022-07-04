#include "Key.h"

Key::Key(publicKey_t publicKey, long long privateKey) {
	this->publicKey = publicKey;
	this->privateKey = privateKey;
}

publicKey_t Key::getPublicKey() const
{
	return publicKey;
}

long long Key::getPrivateKey() const {
	return privateKey;
}
