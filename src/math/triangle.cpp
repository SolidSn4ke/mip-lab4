#include "triangle.h"
#include <iostream>



// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    os << "{" << t.v0 << ", " << t.v1 << ", " << t.v2 << "}";
    return os;
}