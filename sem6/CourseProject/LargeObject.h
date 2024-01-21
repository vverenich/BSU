#ifndef LARGEOBJECT_H
#define LARGEOBJECT_H

enum class LargeObjectState {
    GOOD = 0,
    DAMAGED = 1,
    DESTROYED = 2,
    UNDER_REPAIR = 3,
    ENUM_SIZE = 4
};

class LargeObject {
  public:
    LargeObject();

    LargeObjectState m_State;
};

#endif // LARGEOBJECT_H
