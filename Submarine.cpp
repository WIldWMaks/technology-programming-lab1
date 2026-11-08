#include "Submarine.h"
#include "Input.h"
#include <iostream>
#include <climits>
#include <utility>
Submarine::Submarine() : Base("Submarine"), length_(0), width_(0), crew_(0), endurance_(0), speed_(0), weapons_(io::copy("")) {
    std::cout << "[Submarine] Конструктор без параметров: " << this << '\n';
}
Submarine::Submarine(double length, double width, int crew, double endurance, double speed, const char* weapons) : Base("Submarine"), length_(length), width_(width), crew_(crew), endurance_(endurance), speed_(speed), weapons_(io::copy(weapons)) {
    io::checkReal(length_);
    io::checkReal(width_);
    io::checkInt(crew_);
    io::checkReal(endurance_);
    io::checkReal(speed_);
    io::checkText(weapons_.get());
    std::cout << "[Submarine] Конструктор с параметрами: " << this << '\n';
}
Submarine::Submarine(const Submarine& other) : Base(other), length_(other.length_), width_(other.width_), crew_(other.crew_), endurance_(other.endurance_), speed_(other.speed_), weapons_(io::copy(other.weapons_.get())) {
    std::cout << "[Submarine] Конструктор копирования: " << &other << " -> " << this << '\n';
}
Submarine::~Submarine() { std::cout << "[Submarine] Деструктор: " << this << '\n'; }
void Submarine::swap(Submarine& other) noexcept {
    std::swap(length_,other.length_);
    std::swap(width_,other.width_);
    std::swap(crew_,other.crew_);
    std::swap(endurance_,other.endurance_);
    std::swap(speed_,other.speed_);
    std::swap(weapons_,other.weapons_);
}
Submarine& Submarine::operator=(const Submarine& other) {
    if (this!=&other) { Submarine temp(other); swap(temp); }
    return *this;
}
double Submarine::getLength() const { return length_; }
void Submarine::setLength(double value) {
    io::checkReal(value);
    length_=value;
}
double Submarine::getWidth() const { return width_; }
void Submarine::setWidth(double value) {
    io::checkReal(value);
    width_=value;
}
int Submarine::getCrew() const { return crew_; }
void Submarine::setCrew(int value) {
    io::checkInt(value);
    crew_=value;
}
double Submarine::getEndurance() const { return endurance_; }
void Submarine::setEndurance(double value) {
    io::checkReal(value);
    endurance_=value;
}
double Submarine::getSpeed() const { return speed_; }
void Submarine::setSpeed(double value) {
    io::checkReal(value);
    speed_=value;
}
const char* Submarine::getWeapons() const { return weapons_.get(); }
void Submarine::setWeapons(const char* value) {
    io::checkText(value);
    weapons_=io::copy(value);
}
int Submarine::type() const { return 1; }
Base* Submarine::clone() const { return new Submarine(*this); }
void Submarine::print(std::ostream& out) const {
    out << "Подводная лодка\n";
    out << "Длина, м: " << getLength() << '\n';
    out << "Ширина, м: " << getWidth() << '\n';
    out << "Экипаж, человек: " << getCrew() << '\n';
    out << "Непрерывное пребывание под водой, ч: " << getEndurance() << '\n';
    out << "Максимальная подводная скорость, узлы: " << getSpeed() << '\n';
    out << "Вооружение: " << getWeapons() << '\n';
}
void Submarine::read(std::istream& in,bool prompts) {
    auto new_length=io::real(in,prompts?"Длина, м: ":nullptr);
    auto new_width=io::real(in,prompts?"Ширина, м: ":nullptr);
    auto new_crew=io::integer(in,prompts?"Экипаж, человек: ":nullptr,1,INT_MAX);
    auto new_endurance=io::real(in,prompts?"Непрерывное пребывание под водой, ч: ":nullptr);
    auto new_speed=io::real(in,prompts?"Максимальная подводная скорость, узлы: ":nullptr);
    auto new_weapons=io::text(in,prompts?"Вооружение: ":nullptr);
    Submarine temp(new_length, new_width, new_crew, new_endurance, new_speed, new_weapons.get());
    *this=temp;
}
void Submarine::edit(std::istream& in) {
    std::cout << "1. Длина, м\n";
    std::cout << "2. Ширина, м\n";
    std::cout << "3. Экипаж, человек\n";
    std::cout << "4. Непрерывное пребывание под водой, ч\n";
    std::cout << "5. Максимальная подводная скорость, узлы\n";
    std::cout << "6. Вооружение\n";
    int field=io::integer(in,"Номер поля: ",1,6);
    switch(field) {
    case 1: { auto value=io::real(in,"Длина, м: "); setLength(value); break; }
    case 2: { auto value=io::real(in,"Ширина, м: "); setWidth(value); break; }
    case 3: { auto value=io::integer(in,"Экипаж, человек: ",1,INT_MAX); setCrew(value); break; }
    case 4: { auto value=io::real(in,"Непрерывное пребывание под водой, ч: "); setEndurance(value); break; }
    case 5: { auto value=io::real(in,"Максимальная подводная скорость, узлы: "); setSpeed(value); break; }
    case 6: { auto value=io::text(in,"Вооружение: "); setWeapons(value.get()); break; }
    }
}
void Submarine::write(std::ostream& out) const {
    out << length_ << '\n';
    out << width_ << '\n';
    out << crew_ << '\n';
    out << endurance_ << '\n';
    out << speed_ << '\n';
    out << weapons_.get() << '\n';
}
