#include "Base.h"
#include <iostream>
Base::Base() { std::cout << "[Base] Конструктор без параметров: " << this << '\n'; }
Base::Base(const char* type) {
    std::cout << "[Base] Конструктор с параметром " << type << ": " << this << '\n';
}
Base::Base(const Base& other) {
    std::cout << "[Base] Копирование " << &other << " -> " << this << '\n';
}
Base::~Base() { std::cout << "[Base] Деструктор: " << this << '\n'; }
std::ostream& operator<<(std::ostream& out, const Base& ship) {
    ship.print(out); return out;
}
