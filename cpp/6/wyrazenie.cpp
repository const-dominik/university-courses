#include "wyrazenie.hpp"

int wyrazenie::getPriority() {
    return 100;
}

bool wyrazenie::isLeft() {
    return true;
}