#ifndef MYCLASS_H2
#define MYCLASS_H2

#include "BottledDrink.h"

class SoftDrink : public BottledDrink {
public:
	virtual ~SoftDrink() = 0;
};

inline SoftDrink::~SoftDrink() {}

#endif