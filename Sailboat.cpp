#include "Sailboat.h"
#include "Input.h"
#include <iostream>
#include <climits>
#include <utility>
Sailboat::Sailboat() : Base("Sailboat"), sailType_(io::copy("")), name_(io::copy("")), military_(false), length_(0), speed_(0), crew_(0) {
    std::cout << "[Sailboat] Конструктор без параметров: " << this << '\n';
}
Sailboat::Sailboat(const char* sailType, const char* name, bool military, double length, double speed, int crew) : Base("Sailboat"), sailType_(io::copy(sailType)), name_(io::copy(name)), military_(military), length_(length), speed_(speed), crew_(crew) {
    io::checkText(sailType_.get());
    io::checkText(name_.get());
    io::checkReal(length_);
    io::checkReal(speed_);
    io::checkInt(crew_);
    std::cout << "[Sailboat] Конструктор с параметрами: " << this << '\n';
}
Sailboat::Sailboat(const Sailboat& other) : Base(other), sailType_(io::copy(other.sailType_.get())), name_(io::copy(other.name_.get())), military_(other.military_), length_(other.length_), speed_(other.speed_), crew_(other.crew_) {
    std::cout << "[Sailboat] Конструктор копирования: " << &other << " -> " << this << '\n';
}
Sailboat::~Sailboat() { std::cout << "[Sailboat] Деструктор: " << this << '\n'; }
void Sailboat::swap(Sailboat& other) noexcept {
    std::swap(sailType_,other.sailType_);
    std::swap(name_,other.name_);
    std::swap(military_,other.military_);
    std::swap(length_,other.length_);
    std::swap(speed_,other.speed_);
    std::swap(crew_,other.crew_);
}
Sailboat& Sailboat::operator=(const Sailboat& other) {
    if (this!=&other) { Sailboat temp(other); swap(temp); }
    return *this;
}
const char* Sailboat::getSailType() const { return sailType_.get(); }
void Sailboat::setSailType(const char* value) {
    io::checkText(value);
    sailType_=io::copy(value);
}
const char* Sailboat::getName() const { return name_.get(); }
void Sailboat::setName(const char* value) {
    io::checkText(value);
    name_=io::copy(value);
}
bool Sailboat::getMilitary() const { return military_; }
void Sailboat::setMilitary(bool value) {
    military_=value;
}
double Sailboat::getLength() const { return length_; }
void Sailboat::setLength(double value) {
    io::checkReal(value);
    length_=value;
}
double Sailboat::getSpeed() const { return speed_; }
void Sailboat::setSpeed(double value) {
    io::checkReal(value);
    speed_=value;
}
int Sailboat::getCrew() const { return crew_; }
void Sailboat::setCrew(int value) {
    io::checkInt(value);
    crew_=value;
}
int Sailboat::type() const { return 2; }
Base* Sailboat::clone() const { return new Sailboat(*this); }
void Sailboat::print(std::ostream& out) const {
    out << "Парусник\n";
    out << "Тип парусника: " << getSailType() << '\n';
    out << "Название: " << getName() << '\n';
    out << "Военный (1) или мирный (0): " << (getMilitary()?"Военный":"Мирный") << '\n';
    out << "Длина корпуса, м: " << getLength() << '\n';
    out << "Скорость, узлы: " << getSpeed() << '\n';
    out << "Экипаж, человек: " << getCrew() << '\n';
}
void Sailboat::read(std::istream& in,bool prompts) {
    auto new_sailType=io::text(in,prompts?"Тип парусника: ":nullptr);
    auto new_name=io::text(in,prompts?"Название: ":nullptr);
    auto new_military=io::integer(in,prompts?"Военный (1) или мирный (0): ":nullptr,0,1);
    auto new_length=io::real(in,prompts?"Длина корпуса, м: ":nullptr);
    auto new_speed=io::real(in,prompts?"Скорость, узлы: ":nullptr);
    auto new_crew=io::integer(in,prompts?"Экипаж, человек: ":nullptr,1,INT_MAX);
    Sailboat temp(new_sailType.get(), new_name.get(), new_military!=0, new_length, new_speed, new_crew);
    *this=temp;
}
void Sailboat::edit(std::istream& in) {
    std::cout << "1. Тип парусника\n";
    std::cout << "2. Название\n";
    std::cout << "3. Военный (1) или мирный (0)\n";
    std::cout << "4. Длина корпуса, м\n";
    std::cout << "5. Скорость, узлы\n";
    std::cout << "6. Экипаж, человек\n";
    int field=io::integer(in,"Номер поля: ",1,6);
    switch(field) {
    case 1: { auto value=io::text(in,"Тип парусника: "); setSailType(value.get()); break; }
    case 2: { auto value=io::text(in,"Название: "); setName(value.get()); break; }
    case 3: { auto value=io::integer(in,"Военный (1) или мирный (0): ",0,1); setMilitary(value!=0); break; }
    case 4: { auto value=io::real(in,"Длина корпуса, м: "); setLength(value); break; }
    case 5: { auto value=io::real(in,"Скорость, узлы: "); setSpeed(value); break; }
    case 6: { auto value=io::integer(in,"Экипаж, человек: ",1,INT_MAX); setCrew(value); break; }
    }
}
void Sailboat::write(std::ostream& out) const {
    out << sailType_.get() << '\n';
    out << name_.get() << '\n';
    out << military_ << '\n';
    out << length_ << '\n';
    out << speed_ << '\n';
    out << crew_ << '\n';
}
